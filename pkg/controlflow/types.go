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
		if parsedCall := saveFuncCallIfValid(service, method, block, e); parsedCall != nil {
			logger.Logger.Warnf("GOT PARSED CALL %s \n\t\t\t\tMETHOD: %s", parsedCall.String(), parsedCall.GetMethod())
			for _, rt := range parsedCall.GetMethod().GetReturns() {
				newVar := createVariableFromType("", rt.GetType())
				block.AddVariable(newVar)
				tupleVar.Variables = append(tupleVar.Variables, newVar)
			}
		} else {
			logger.Logger.Warnf("GOT UNKNOWN CALL %v", e.Fun)
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
			logger.Logger.Debugf("GOT SELECTOR FOR %s", e.Sel.Name)
			structName := e.Sel.Name
			field, exists := v.Fields[structName]
			if !exists {
				fieldType, ok := v.GetStructType().FieldTypes[structName]
				if !ok {
					logger.Logger.Fatalf("invalid field name %s in structure variable %s with fields types %v", structName, v.String(), v.GetStructType().FieldTypes)
				}
				field = getOrCreateVariableFromType(structName, fieldType)
			}
			v.Fields[structName] = field
			logger.Logger.Warnf("added new variable %s for field %s in structure variable %s", variable.String(), structName, v.String())
			return variable
			//variable = v
		default:
			logger.Logger.Fatalf("could not find variable for selector %s with type %s", variable.String(), utils.GetType(variable))
		}
		/* newType := ComputeType(e, file)
		logger.Logger.Fatalf("GOT NEW TYPE %v", newType) */
	// FIXME: ACTUALLY THE TYPE OF A STRUCT SHOULD REFERENCE A USER TYPE THAT WAS PREVIOUSLY DEFINED
	case *ast.CompositeLit:
		if ident, ok := e.Type.(*ast.Ident); ok {
			if namedType, found := service.File.Package.GetNamedType(ident.Name); found {
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
		logger.Logger.Fatalf("nil variable for %s: %v", utils.GetType(expr), expr)
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
	logger.Logger.Fatalf("could not create variable from type %v", t)
	return nil
}

func createVariableFromType(name string, t types.Type) types.Variable {
	switch e := t.(type) {
	case *types.UserType, *types.BasicType, *types.ChanType, *types.InterfaceType:
		return &types.CompositeVariable{
			VariableInfo: &types.VariableInfo{
				Name: name,
				Type: e,
				Id:   types.VARIABLE_UNASSIGNED_ID,
			},
		}
	case *types.StructType:
		e.FieldTypes = make(map[string]types.Type)
		return &types.StructVariable{
			VariableInfo: &types.VariableInfo{
				Name: name,
				Type: e,
				Id:   types.VARIABLE_UNASSIGNED_ID,
			},
			Fields: make(map[string]types.Variable),
		}
	case *types.MapType:
		return &types.MapVariable{
			VariableInfo: &types.VariableInfo{
				Name: name,
				Type: e,
				Id:   types.VARIABLE_UNASSIGNED_ID,
			},
			KeyValues: make(map[types.Variable]types.Variable, 0),
		}
	case *types.ArrayType:
		return &types.ArrayVariable{
			VariableInfo: &types.VariableInfo{
				Name: name,
				Type: e,
				Id:   types.VARIABLE_UNASSIGNED_ID,
			},
		}
	case *blueprint.BackendType:
		if e.IsNoSQLComponent() {
			return &blueprint.NoSQLCollectionVariable{
				VariableInfo: &types.VariableInfo{
					Name: name,
					Type: e,
					Id:   types.VARIABLE_UNASSIGNED_ID,
				},
			}
		}
		logger.Logger.Fatalf("unexpected blueprint backend type %s", e.String())
	}
	logger.Logger.Fatalf("could not create variable %s for type %s", name, t)
	return nil
}
