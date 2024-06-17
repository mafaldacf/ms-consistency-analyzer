package controlflow

import (
	"go/ast"
	"go/token"
	gotypes "go/types"
	"strconv"
	"strings"

	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
)

func getOrCreateVariable(service *service.Service, method *types.ParsedMethod, block *types.Block, expr ast.Expr, assign bool) (variable types.Variable) {

	switch e := expr.(type) {
	case *ast.CallExpr:
		tupleVar := &types.TupleVariable{}
		//FIXME: this is kinda hard coded and must be automated
		goTypeInfo := service.GetPackage().GetTypeInfo(e)
		call, deps, saved := parseAndSaveCallIfValid(service, method, block, e)
		logger.Logger.Warnf("GET OR CREATE FOR EXPR %v WITH TYPE %s", expr, utils.GetType(expr))
		if call != nil && saved {
			logger.Logger.Warnf("(1) GET OR CREATE FOR EXPR %v WITH TYPE %s", expr, utils.GetType(expr))
			for i, rt := range call.GetMethod().GetReturns() {
				newVar := createVariableFromType(service, "", rt.GetType())
				//FIXMEEEEEEE
				if len(deps) > 0 {
					newCompVar := &types.CompositeVariable{
						VariableInfo: &types.VariableInfo{
							Name: newVar.String(),
							Type: newVar.GetVariableInfo().Type,
							Id:   types.VARIABLE_UNASSIGNED_ID,
						},
						Params: []types.Variable{deps[i]},
					}
					block.AddVariable(newCompVar)
					tupleVar.Variables = append(tupleVar.Variables, newCompVar)
					call.AddReturn(newCompVar)
				} else {
					block.AddVariable(newVar)
					call.AddReturn(newVar)
					tupleVar.Variables = append(tupleVar.Variables, newVar)
				}
			}
		} else if signatureGoType, ok := service.File.Package.GetTypeInfo(e.Fun).(*gotypes.Signature); ok && call == nil {
			logger.Logger.Warnf("(2) GET OR CREATE FOR EXPR %v WITH TYPE %s", expr, utils.GetType(expr))
			tupleType := service.File.Package.GenerateUnderlyingTypesFromGoType(signatureGoType.Results())
			for i, rt := range tupleType.(*types.TupleType).Types {
				newVar := createVariableFromType(service, "", rt)
				logger.Logger.Infof("IN SIGNAATURE!!! %s (DEPS = %v)", newVar.String(), deps)
				//FIXMEEEEEEE
				if len(deps) > 0 {
					newCompVar := &types.CompositeVariable{
						VariableInfo: &types.VariableInfo{
							Name: newVar.String(),
							Type: newVar.GetVariableInfo().Type,
							Id:   types.VARIABLE_UNASSIGNED_ID,
						},
						Params: []types.Variable{deps[i]},
					}
					block.AddVariable(newCompVar)
					tupleVar.Variables = append(tupleVar.Variables, newCompVar)
				} else {
					block.AddVariable(newVar)
					tupleVar.Variables = append(tupleVar.Variables, newVar)
				}
			}
		} else if call != nil {
			logger.Logger.Warnf("(3) GET OR CREATE FOR EXPR %v WITH TYPE %s", expr, utils.GetType(expr))
			//callStr := computeFunctionCallName(e.Fun) + "(...)"
			// FIXME: THIS IS VEEEEEEERRYYYYYY HARD CODE AND MUUUUUUSSST BE AUTOMATED
			if goTupleType, ok := goTypeInfo.(*gotypes.Tuple); ok {
				for i := 0; i < goTupleType.Len(); i++ {
					//goType := goTupleType.At(i)
					//newType, ok := service.File.Package.GetImportedTypeFromPath(goType.String())
					newType := &types.GenericType{
						Name: goTupleType.String(),
					}
					genericVariable := &types.CompositeVariable{
						VariableInfo: &types.VariableInfo{
							Type: newType,
							Id:   types.VARIABLE_INLINE_ID,
						},
					}
					for _, arg := range e.Args {
						argVar := getOrCreateVariable(service, method, block, arg, false)
						genericVariable.Params = append(genericVariable.Params, argVar)
					}
					tupleVar.Variables = append(tupleVar.Variables, genericVariable)
				}
			} else {
				newType := &types.GenericType{
					Name: goTupleType.String(),
				}
				genericVariable := &types.CompositeVariable{
					VariableInfo: &types.VariableInfo{
						Type: newType,
						Id:   types.VARIABLE_INLINE_ID,
					},
				}
				for _, arg := range e.Args {
					argVar := getOrCreateVariable(service, method, block, arg, false)
					genericVariable.Params = append(genericVariable.Params, argVar)
				}
				tupleVar.Variables = append(tupleVar.Variables, genericVariable)
				logger.Logger.Debugf("SKIPPING!!! %v", utils.GetType(goTypeInfo))
			}
		} else {
			logger.Logger.Fatalf("FIXME: unable to parse call (%v) %s", call, utils.GetType(service.File.Package.GetTypeInfo(e.Fun)))
		}
		variable = tupleVar
	case *ast.BasicLit:
		basicType := &types.BasicType{
			Name:  strings.ToLower(e.Kind.String()),
			Value: e.Value,
		}
		variable = &types.BasicVariable{
			VariableInfo: &types.VariableInfo{
				Type: basicType,
				Id:   types.VARIABLE_INLINE_ID,
			},
		}
	case *ast.Ident:
		variable = block.GetLastestVariable(e.Name)
		// if its not a variable in the block then it can be either
		// 1. a declared variable in the package
		// 2. a ident from a import (which is dealt with in the switch case for the selectorExpr)
		if variable == nil {
			variable = service.File.Package.DeclaredVariables[e.Name]
			if variable == nil {
				logger.Logger.Warnf("variable '%s' not found in package %s with declared variables list: %v", e.Name, service.File.Package.Name, service.File.Package.DeclaredVariables)
			}
		}
		return variable
	case *ast.SelectorExpr:
		variable = getOrCreateVariable(service, method, block, e.X, assign)
		// if it was not found, maybe it can be the alias for an import
		if variable == nil {
			newType := service.File.ComputeTypeForExpr(e)
			variable = getOrCreateVariableFromType("", newType)
		}

		switch v := variable.(type) {
		case *types.GenericVariable:
			// continue
		case *types.StructVariable:
			structName := e.Sel.Name
			field, exists := v.Fields[structName]
			if !exists {
				fieldType, ok := v.GetStructType().FieldTypes[structName]
				if !ok {
					logger.Logger.Fatalf("invalid field name %s in structure variable %s with fields types %v", structName, v.String(), v.GetStructType().FieldTypes)
				}
				field = getOrCreateVariableFromType(structName, fieldType)
				logger.Logger.Warnf("[FIXME] added new variable %s for field %s in structure variable %s (fields = %v)", variable.String(), structName, v.String(), v.Fields)
				v.Fields[structName] = field
			}
			return field
			//variable = v
		default:
			logger.Logger.Warnf("FIXME: could not find variable for selector %s", variable)
		}
		/* newType := ComputeType(e, file)
		logger.Logger.Fatalf("GOT NEW TYPE %v", newType) */
	// FIXME: ACTUALLY THE TYPE OF A STRUCT SHOULD REFERENCE A USER TYPE THAT WAS PREVIOUSLY DEFINED
	case *ast.CompositeLit:
		//FIX THIS!!!
		if ident, ok := e.Type.(*ast.Ident); ok {
			if namedType, found := service.File.Package.GetNamedType(ident.Name); found {
				logger.Logger.Warnf("GOT NAEMD TYPE INCOMPOSITE %s", namedType.String())
				if userType, ok := namedType.(*types.UserType); ok {
					if _, ok := userType.UserType.(*types.StructType); ok {
						structVariable := &types.StructVariable{
							VariableInfo: &types.VariableInfo{
								Type: userType,
								Id:   types.VARIABLE_INLINE_ID,
							},
							Fields: make(map[string]types.Variable),
						}
						for _, elt := range e.Elts {
							keyvalue := elt.(*ast.KeyValueExpr)
							key := keyvalue.Key.(*ast.Ident)
							eltVar := getOrCreateVariable(service, method, block, keyvalue.Value, false)
							logger.Logger.Warnf("GOT ELT VAR!!! %s", eltVar.String())
							if tupleVar, ok := eltVar.(*types.TupleVariable); ok && len(tupleVar.Variables) == 1 {
								eltVar = tupleVar.Variables[0]
							}
							if eltVar.GetVariableInfo().Name == "" {
								eltVar.GetVariableInfo().SetName(key.Name)
							}
							structVariable.AddFieldIfNotExists(key.Name, eltVar)
						}
						variable = structVariable
					}
				}
			}
		} else if arrayTypeAst, ok := e.Type.(*ast.ArrayType); ok {
			arrayType := &types.ArrayType{
				ElementsType: service.File.ComputeTypeForExpr(arrayTypeAst.Elt),
			}
			variable = &types.ArrayVariable{
				VariableInfo: &types.VariableInfo{
					Type: arrayType,
					Id:   types.VARIABLE_INLINE_ID,
				},
			}
			for _, elt := range e.Elts {
				eltVar := getOrCreateVariable(service, method, block, elt, false)
				variable.(*types.ArrayVariable).AddElement(eltVar)
			}
		} else if selectorExpr, ok := e.Type.(*ast.SelectorExpr); ok {
			logger.Logger.Warnf("got selector %v (expr type = %s)", selectorExpr, utils.GetType(selectorExpr.X))
			variable = getOrCreateVariable(service, method, block, selectorExpr, assign)
		} else {
			logger.Logger.Fatalf("nil variable for composite lit (e.Type = %s): %v", utils.GetType(e.Type), e)
		}
	case *ast.TypeAssertExpr:
		variable = getOrCreateVariable(service, method, block, e.X, assign)
	case *ast.IndexExpr:
		variable = getOrCreateVariable(service, method, block, e.X, assign)
		if variable == nil {
			logger.Logger.Fatalf("nil variable for index expr: %v (e.X type = %s)", e, utils.GetType(e.X))
		}
		if arrayVar, ok := variable.(*types.ArrayVariable); ok {
			variable = arrayVar.Elements[computeArrayIndex(e.Index)]
		}
		if mapVar, ok := variable.(*types.MapVariable); ok {
			key := getOrCreateVariable(service, method, block, e.Index, false)
			variable, ok = mapVar.KeyValues[key]
			if !ok {
				logger.Logger.Warnf("got map %v with unassigned value for key %s", mapVar.String(), key.String())
				variable = mapVar
			}
		}
	case *ast.UnaryExpr:
		if e.Op == token.AND { // e.g. &post
			variable = getOrCreateVariable(service, method, block, e.X, assign)
			addrType := &types.AddressType{
				AddressOf: variable.GetVariableInfo().Type,
			}
			variable = &types.AddressVariable{
				AddressOf: variable,
				VariableInfo: &types.VariableInfo{
					Type: addrType,
					Id:   types.VARIABLE_INLINE_ID,
					Name: variable.GetVariableInfo().Name,
				},
			}
		} else if e.Op == token.MUL { // e.g. *post
			variable = getOrCreateVariable(service, method, block, e.X, assign)
			addrType := &types.AddressType{
				AddressOf: variable.GetVariableInfo().Type,
			}
			variable = &types.PointerVariable{
				PointerTo: variable,
				VariableInfo: &types.VariableInfo{
					Type: addrType,
					Id:   types.VARIABLE_INLINE_ID,
					Name: variable.GetVariableInfo().Name,
				},
			}

		} else {
			variable = getOrCreateVariable(service, method, block, e.X, assign)
		}
	default:
		logger.Logger.Fatalf("unknown type in GetOrCreateVariable for type %s: %v", utils.GetType(e), e)
	}
	if variable == nil {
		logger.Logger.Warnf("FIXME: nil variable for %s: %v", utils.GetType(expr), expr)
	}
	return variable
}

func computeArrayIndex(expr ast.Expr) int {
	switch e := expr.(type) {
	case *ast.BasicLit:
		index, err := strconv.Atoi(e.Value)
		if err != nil {
			logger.Logger.Fatalf("error converting index %s: %s", e.Value, err.Error())
		}
		return index
	}
	logger.Logger.Fatalf("could not compute index for expr %s (type = %s)", expr, utils.GetType(expr))
	return 0
}

func getOrCreateVariableFromType(name string, t types.Type) types.Variable {
	info := &types.VariableInfo{
		Name: name,
		Type: t,
	}
	if name == "" {
		info.Id = types.VARIABLE_INLINE_ID
	} else {
		info.Id = types.VARIABLE_UNASSIGNED_ID
	}
	switch e := t.(type) {
	case *types.BasicType:
		return &types.BasicVariable{VariableInfo: info}
	case *types.ChanType:
		return &types.ChanVariable{VariableInfo: info}
	case *types.MapType:
		return &types.MapVariable{VariableInfo: info}
	case *types.InterfaceType:
		return &types.InterfaceVariable{VariableInfo: info}
	case *types.ArrayType:
		return &types.ArrayVariable{VariableInfo: info}
	case *types.StructType:
		// if we are here due to a recursive call (e.g. from UserType)
		// then we want to make sure we are not reseting the map
		if e.FieldTypes == nil {
			e.FieldTypes = make(map[string]types.Type)
		}
		return &types.StructVariable{
			VariableInfo: info,
			Fields:       make(map[string]types.Variable),
		}
	case *types.UserType:
		if e.UserType != nil {
			variable := getOrCreateVariableFromType(name, e.UserType)
			variable.GetVariableInfo().Type = e
			return variable
		}
		// e.g. context.Context is nil
		return &types.GenericVariable{VariableInfo: info}
	}
	logger.Logger.Warnf("FIXME: could not create variable from type %v", t)
	return nil
}

func createVariableFromType(service *service.Service, name string, t types.Type) types.Variable {
	info := &types.VariableInfo{
		Name: name,
		Type: t,
		Id:   types.VARIABLE_UNASSIGNED_ID,
	}

	switch e := t.(type) {
	case *types.UserType:
		if e.UserType != nil {
			return createVariableFromType(service, name, e.UserType)
		}
		logger.Logger.Warnf("user type %s with nil underlying type", e.String())
		return &types.GenericVariable{VariableInfo: info}
	case *types.ChanType:
		return &types.ChanVariable{VariableInfo: info}
	case *types.BasicType:
		return &types.BasicVariable{VariableInfo: info}
	case *types.InterfaceType:
		return &types.InterfaceVariable{VariableInfo: info}
	case *types.ArrayType:
		return &types.ArrayVariable{VariableInfo: info}
	case *types.StructType:
		return &types.StructVariable{VariableInfo: info, Fields: make(map[string]types.Variable)}
	case *types.MapType:
		return &types.MapVariable{VariableInfo: info, KeyValues: make(map[types.Variable]types.Variable, 0)}
	case *blueprint.BackendType:
		if e.IsNoSQLComponent() {
			logger.Logger.Infof("created variable for NoSQL collection %s", e.NoSQLComponent.String())
			if e.IsNoSQLCollection() {
				return &blueprint.NoSQLCollectionVariable{VariableInfo: info}
			} else if e.IsNoSQLCursor() {
				return &blueprint.NoSQLCursorVariable{VariableInfo: info}
			}
		}
		logger.Logger.Fatalf("unexpected blueprint backend type %s (type = %s)", e.String(), utils.GetType(e))
	}
	logger.Logger.Fatalf("could not create variable %s for type %s", name, t)
	return nil
}
