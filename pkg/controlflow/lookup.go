package controlflow

import (
	"go/ast"
	"go/token"
	golangtypes "go/types"
	"strconv"
	"strings"

	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

func lookupVariableFromAstExpr(service *service.Service, method *types.ParsedMethod, block *types.Block, expr ast.Expr, assign bool) (variable types.Variable) {
	logger.Logger.Debugf("VISITING EXPR %v (%s)", expr, utils.GetType(expr))
	switch e := expr.(type) {
	case *ast.CallExpr:
		tupleVar := &types.TupleVariable{}
		//FIXME: this is kinda hard coded and must be automated
		goTypeInfo := service.GetPackage().GetTypeInfo(e)
		call, deps, saved := parseAndSaveCallIfValid(service, method, block, e)
		logger.Logger.Warnf("GET OR CREATE FOR EXPR %v WITH TYPE %s, DEPS: %v", expr, utils.GetType(expr), deps)
		if call != nil && saved {
			logger.Logger.Warnf("(1) GET OR CREATE FOR EXPR %v WITH TYPE %s", expr, utils.GetType(expr))
			for i, rt := range call.GetMethod().GetReturns() {
				newVar := CreateVariableFromType(service, "", rt.GetType())
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
					tupleVar.Variables = append(tupleVar.Variables, newCompVar)
					block.AddVariable(newCompVar)
					call.AddReturn(newCompVar)
				} else {
					call.AddReturn(newVar)
					block.AddVariable(newVar)
					tupleVar.Variables = append(tupleVar.Variables, newVar)
				}
			}
		} else if signatureGoType, ok := service.File.Package.GetTypeInfo(e.Fun).(*golangtypes.Signature); ok && call == nil {
			logger.Logger.Warnf("(2) GET OR CREATE FOR EXPR %v WITH TYPE %s", expr, utils.GetType(expr))
			tupleType := service.File.Package.ComputeTypesForGoTypes(signatureGoType.Results())
			for _, rt := range tupleType.(*gotypes.TupleType).Types {
				newVar := CreateVariableFromType(service, "", rt)
				logger.Logger.Infof("IN SIGNAATURE!!! %s (%s) (DEPS = %v)", newVar.String(), utils.GetType(newVar), deps)
				//FIXMEEEEEEE
				if len(deps) > 0 {
					newCompVar := &types.CompositeVariable{
						VariableInfo: &types.VariableInfo{
							Type: newVar.GetVariableInfo().Type,
							Id:   types.VARIABLE_UNASSIGNED_ID,
						},
						Params: deps,
					}
					tupleVar.Variables = append(tupleVar.Variables, newCompVar)
					block.AddVariable(newCompVar)
				} else {
					tupleVar.Variables = append(tupleVar.Variables, newVar)
					block.AddVariable(newVar)
				}
			}
		} else if call != nil {
			logger.Logger.Warnf("(3) GET OR CREATE FOR EXPR %v WITH TYPE %s", expr, utils.GetType(expr))
			//callStr := computeFunctionCallName(e.Fun) + "(...)"
			// FIXME: THIS IS VEEEEEEERRYYYYYY HARD CODE AND MUUUUUUSSST BE AUTOMATED
			if goTupleType, ok := goTypeInfo.(*golangtypes.Tuple); ok {
				for i := 0; i < goTupleType.Len(); i++ {
					//goVar := goTupleType.At(i)
					//newType := service.File.Package.ComputeTypesForGoTypes(goVar.Type())
					genericVariable := &types.CompositeVariable{
						VariableInfo: &types.VariableInfo{
							Type: &gotypes.GenericType{
								Name: goTupleType.String(),
							},
							Id: types.VARIABLE_INLINE_ID,
						},
					}
					for _, arg := range e.Args {
						argVar := lookupVariableFromAstExpr(service, method, block, arg, false)
						genericVariable.Params = append(genericVariable.Params, argVar)
					}
					tupleVar.Variables = append(tupleVar.Variables, genericVariable)
					block.AddVariable(genericVariable)
				}
			} else {
				genericVariable := &types.CompositeVariable{
					VariableInfo: &types.VariableInfo{
						Type: &gotypes.GenericType{
							Name: goTupleType.String(),
						},
						Id: types.VARIABLE_INLINE_ID,
					},
				}
				for _, arg := range e.Args {
					argVar := lookupVariableFromAstExpr(service, method, block, arg, false)
					genericVariable.Params = append(genericVariable.Params, argVar)
				}
				tupleVar.Variables = append(tupleVar.Variables, genericVariable)
				block.AddVariable(genericVariable)
				logger.Logger.Debugf("SKIPPING!!! %v", utils.GetType(goTypeInfo))
			}
		} else {
			logger.Logger.Fatalf("FIXME: unable to parse call (%v) %s", call, utils.GetType(service.File.Package.GetTypeInfo(e.Fun)))
		}
		variable = tupleVar
	case *ast.BasicLit:
		basicType := &gotypes.BasicType{
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
		variable = lookupVariableFromAstExpr(service, method, block, e.X, assign)
		// if it was not found, maybe it can be the alias for an import
		if variable == nil {
			newType := service.File.ComputeTypeForAstExpr(e)
			variable = lookupVariableFromType("", newType)
		}

		switch v := variable.(type) {
		case *types.GenericVariable:
			// continue
		case *types.StructVariable:
			fieldName := e.Sel.Name
			field, exists := v.Fields[fieldName]
			if !exists {
				v.GetStructType().GetFieldTypeByName(fieldName)
				fieldType := v.GetStructType().GetFieldTypeByName(fieldName)
				field = lookupVariableFromType(fieldName, fieldType)
				logger.Logger.Warnf("[REVIEW] added new variable %s for field %s in structure variable %s (fields = %v)", variable.String(), fieldName, v.String(), v.Fields)
				v.Fields[fieldName] = field
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
				if userType, ok := namedType.(*gotypes.UserType); ok {
					//FIXME: if its an embedded struct then we never enter here!!
					if structType, ok := userType.UserType.(*gotypes.StructType); ok {
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
							eltVar := lookupVariableFromAstExpr(service, method, block, keyvalue.Value, false)

							if tupleVar, ok := eltVar.(*types.TupleVariable); ok && len(tupleVar.Variables) == 1 {
								eltVar = tupleVar.Variables[0]
							}
							logger.Logger.Warnf("GOT ELT VAR!!! %s (%s)", eltVar.String(), utils.GetType(eltVar))

							fieldType := structType.GetFieldTypeByName(key.Name)

							fieldVar := &types.FieldVariable{
								VariableInfo: &types.VariableInfo{
									Name: key.Name,
									Type: fieldType,
									Id:   types.VARIABLE_INLINE_ID,
								},
								Underlying: eltVar,
							}
							structVariable.AddFieldVariableIfNotExists(key.Name, fieldVar)
						}
						variable = structVariable
					}
				}
			}
		} else if arrayTypeAst, ok := e.Type.(*ast.ArrayType); ok {
			arrayType := &gotypes.ArrayType{
				ElementsType: service.File.ComputeTypeForAstExpr(arrayTypeAst.Elt),
			}
			variable = &types.ArrayVariable{
				VariableInfo: &types.VariableInfo{
					Type: arrayType,
					Id:   types.VARIABLE_INLINE_ID,
				},
			}
			for _, elt := range e.Elts {
				eltVar := lookupVariableFromAstExpr(service, method, block, elt, false)
				variable.(*types.ArrayVariable).AddElement(eltVar)
			}
		} else if selectorExpr, ok := e.Type.(*ast.SelectorExpr); ok {
			logger.Logger.Warnf("got selector %v (expr type = %s)", selectorExpr, utils.GetType(selectorExpr.X))
			variable = lookupVariableFromAstExpr(service, method, block, selectorExpr, assign)
		} else {
			logger.Logger.Fatalf("nil variable for composite lit (e.Type = %s): %v", utils.GetType(e.Type), e)
		}
	case *ast.TypeAssertExpr:
		variable = lookupVariableFromAstExpr(service, method, block, e.X, assign)
	case *ast.IndexExpr:
		variable = lookupVariableFromAstExpr(service, method, block, e.X, assign)
		if variable == nil {
			logger.Logger.Fatalf("nil variable for index expr: %v (e.X type = %s)", e, utils.GetType(e.X))
		}
		if arrayVar, ok := variable.(*types.ArrayVariable); ok {
			variable = arrayVar.Elements[computeArrayIndex(e.Index)]
		}
		if mapVar, ok := variable.(*types.MapVariable); ok {
			key := lookupVariableFromAstExpr(service, method, block, e.Index, false)
			variable, ok = mapVar.KeyValues[key]
			if !ok {
				logger.Logger.Warnf("got map %v with unassigned value for key %s", mapVar.String(), key.String())
				variable = mapVar
			}
		}
	case *ast.UnaryExpr:
		if e.Op == token.AND { // e.g. &post
			variable = lookupVariableFromAstExpr(service, method, block, e.X, assign)
			addrType := &gotypes.AddressType{
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
			variable = lookupVariableFromAstExpr(service, method, block, e.X, assign)
			addrType := &gotypes.AddressType{
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
			variable = lookupVariableFromAstExpr(service, method, block, e.X, assign)
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

func lookupVariableFromType(name string, t gotypes.Type) types.Variable {
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
	case *gotypes.BasicType:
		return &types.BasicVariable{VariableInfo: info}
	case *gotypes.ChanType:
		return &types.ChanVariable{VariableInfo: info}
	case *gotypes.MapType:
		return &types.MapVariable{VariableInfo: info}
	case *gotypes.InterfaceType:
		return &types.InterfaceVariable{VariableInfo: info}
	case *gotypes.ArrayType:
		return &types.ArrayVariable{VariableInfo: info}
	case *gotypes.StructType:
		return &types.StructVariable{
			VariableInfo: info,
			Fields:       make(map[string]types.Variable),
		}
	case *gotypes.FieldType:
		info.Name = e.FieldName
		return &types.FieldVariable{
			VariableInfo: info,
			Underlying:   lookupVariableFromType(name, e.SubType),
		}
	case *gotypes.UserType:
		if e.UserType != nil {
			v := lookupVariableFromType(name, e.UserType)
			v.GetVariableInfo().Type = e
			return v
		}
		// e.g. context.Context is nil
		return &types.GenericVariable{VariableInfo: info}
	}
	logger.Logger.Warnf("FIXME: could not create variable from type %v", t)
	return nil
}

func CreateVariableFromType(service *service.Service, name string, t gotypes.Type) types.Variable {
	info := &types.VariableInfo{
		Name: name,
		Type: t,
		Id:   types.VARIABLE_UNASSIGNED_ID,
	}

	switch e := t.(type) {
	case *gotypes.UserType:
		if e.UserType != nil {
			return CreateVariableFromType(service, name, e.UserType)
		}
		logger.Logger.Warnf("user type %s with nil underlying type", e.String())
		return &types.GenericVariable{VariableInfo: info}
	case *gotypes.ChanType:
		return &types.ChanVariable{VariableInfo: info}
	case *gotypes.BasicType:
		return &types.BasicVariable{VariableInfo: info}
	case *gotypes.InterfaceType:
		return &types.InterfaceVariable{VariableInfo: info}
	case *gotypes.ArrayType:
		return &types.ArrayVariable{VariableInfo: info}
	case *gotypes.StructType:
		return &types.StructVariable{VariableInfo: info, Fields: make(map[string]types.Variable)}
	case *gotypes.MapType:
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
