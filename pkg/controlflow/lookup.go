package controlflow

import (
	"go/ast"
	"go/token"
	"strconv"
	"strings"

	"analyzer/pkg/logger"
	"analyzer/pkg/lookup"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

func computeArrayIndex(expr ast.Expr) int {
	switch e := expr.(type) {
	case *ast.BasicLit:
		index, err := strconv.Atoi(e.Value)
		if err != nil {
			logger.Logger.Fatalf("error converting index (%s): %s", e.Value, err.Error())
		}
		return index
	}
	logger.Logger.Fatalf("could not compute index for expr (%s) with type (%s)", expr, utils.GetType(expr))
	return 0
}

func lookupVariableFromIdentIfExists(service *service.Service, block *types.Block, ident *ast.Ident) variables.Variable {
	variable := block.GetLastestVariableIfExists(ident.Name)
	if variable != nil {
		return variable
	}
	// if its not a variable in the block then it can be either
	// 1. a declared variable in the package
	// 2. a ident from a import (which is dealt with in the switch case for the selectorExpr)
	variable = service.GetPackage().GetDeclaredVariableIfExists(ident.Name)
	if variable != nil {
		return variable
	}
	return nil
}

func lookupImportedPackageFromIdent(service *service.Service, ident *ast.Ident) *gotypes.PackageType {
	if impt := service.GetFile().GetImport(ident.Name); impt != nil {
		t := &gotypes.PackageType{
			Alias: ident.Name,
			Name: impt.PackageName,
			Path: impt.PackagePath,
		}
		return t
	}
	return nil
}

func lookupVariableFromAstExpr(service *service.Service, method *types.ParsedMethod, block *types.Block, expr ast.Expr, assign bool) (variable variables.Variable, packageType *gotypes.PackageType) {
	logger.Logger.Debugf("[CFG LOOKUP EXPR] visiting expression (%v) with type (%s)", expr, utils.GetType(expr))
	switch e := expr.(type) {
	case *ast.CallExpr:
		variable = parseAndSaveCall(service, method, block, e)
	case *ast.BasicLit:
		basicType := &gotypes.BasicType{
			Name:  strings.ToLower(e.Kind.String()),
			Value: e.Value,
		}
		variable = &variables.BasicVariable{
			VariableInfo: &variables.VariableInfo{
				Type: basicType,
				Id:   variables.VARIABLE_INLINE_ID,
			},
		}
	case *ast.Ident:
		variable = lookupVariableFromIdentIfExists(service, block, e)
		logger.Logger.Warnf("HEREEE: %v", block.VarsString())
		if variable != nil {
			return variable, nil
		}
		if utils.IsBuiltInType(e.Name) {
			if utils.IsBuiltInFunc(e.Name) {
				logger.Logger.Warnf("FIXME: IDENTIFIED BUILT IN FUNC FOR (%s)", e.Name)
				return nil, nil
			}
		}

		packageType = lookupImportedPackageFromIdent(service, e)
		if packageType != nil {
			return nil, packageType
		}
		logger.Logger.Fatalf("[CFG LOOKUP] unexpected nil variable (or package) with type (%s) for expr (%v)", utils.GetType(expr), expr)
		return nil, nil
	case *ast.SelectorExpr:
		variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
		if packageType != nil {
			importedPkg := service.GetPackage().GetImportedPackage(packageType.Path)
			if importedPkg.IsExternalPackage() {
				t := lookup.LookupTypesForGoTypes(service.GetPackage(), service.GetPackage().GetTypeInfo(e.Sel))
				variable = lookup.CreateVariableFromType("", t)
				return variable, nil
			}
			declaredType := importedPkg.GetDeclaredTypeIfExists(e.Sel)
			if declaredType != nil {
				variable = lookup.CreateVariableFromType("", declaredType)
				return variable, nil
			}

			variable = importedPkg.GetDeclaredVariable(e.Sel)
			return variable, nil
		}
		if tupleVariable, ok := variable.(*variables.TupleVariable); ok {
			if tupleVariable.NumVariables() == 1 {
				variable = tupleVariable.GetVariableAt(0)
			} else {
				logger.Logger.Fatalf("[CFG LOOKUP] unexpected number (%d) of variables in tuple: %s", tupleVariable.NumVariables(), tupleVariable.String())
			}
		}

		if ptrVariable, ok := variable.(*variables.PointerVariable); ok {
			variable = ptrVariable.PointerTo
		}

		switch v := variable.(type) {
		case *variables.GenericVariable:
			logger.Logger.Fatalf("[CFG LOOKUP] ignoring generic variable (%s)", v.String())
		case *variables.StructVariable:
			fieldName := e.Sel.Name
			field, exists := v.Fields[fieldName]
			if !exists {
				v.GetStructType().GetFieldTypeByName(fieldName)
				fieldType := v.GetStructType().GetFieldTypeByName(fieldName)
				field = lookup.CreateVariableFromType(fieldName, fieldType)
				v.Fields[fieldName] = field
				logger.Logger.Warnf("[REVIEW] added new variable (%s) for field (%s) in structure variable (%s) -- fields: %v", field.String(), fieldName, variable.String(), v.Fields)
			}
			return field, nil
		default:
			logger.Logger.Fatalf("[CFG LOOKUP] unknown variable (%s) with type (%s) for selector (%s)", variable.String(), utils.GetType(variable), e)
		}
	case *ast.CompositeLit:
		//FIX THIS!!!
		if ident, ok := e.Type.(*ast.Ident); ok {
			if namedType, found := service.GetPackage().GetNamedType(ident.Name); found {
				//logger.Logger.Debugf("[CFG LOOKUP] GOT NAMED TYPE INCOMPOSITE %s", namedType.String())
				if userType, ok := namedType.(*gotypes.UserType); ok {
					//FIXME: if its an embedded struct then we never enter here!!
					if structType, ok := userType.UserType.(*gotypes.StructType); ok {
						structVariable := &variables.StructVariable{
							VariableInfo: &variables.VariableInfo{
								Type: userType,
								Id:   variables.VARIABLE_INLINE_ID,
							},
							Fields: make(map[string]variables.Variable),
						}
						for _, elt := range e.Elts {
							keyvalue := elt.(*ast.KeyValueExpr)
							key := keyvalue.Key.(*ast.Ident)
							eltVar, _ := lookupVariableFromAstExpr(service, method, block, keyvalue.Value, false)

							if tupleVar, ok := eltVar.(*variables.TupleVariable); ok && len(tupleVar.Variables) == 1 {
								eltVar = tupleVar.Variables[0]
							}
							//logger.Logger.Debugf("[CFG LOOKUP] GOT ELT VAR %s (%s)", eltVar.String(), utils.GetType(eltVar))

							fieldType := structType.GetFieldTypeByName(key.Name)

							fieldVar := &variables.FieldVariable{
								VariableInfo: &variables.VariableInfo{
									Name: key.Name,
									Type: fieldType,
									Id:   variables.VARIABLE_INLINE_ID,
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
				ElementsType: lookup.ComputeTypeForAstExpr(service.File, arrayTypeAst.Elt),
			}
			variable = &variables.ArrayVariable{
				VariableInfo: &variables.VariableInfo{
					Type: arrayType,
					Id:   variables.VARIABLE_INLINE_ID,
				},
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, false)
				variable.(*variables.ArrayVariable).AddElement(eltVar)
			}
		} else if selectorExpr, ok := e.Type.(*ast.SelectorExpr); ok {
			//logger.Logger.Warnf("[CFG LOOKUP] got selector %v (expr type = %s)", selectorExpr, utils.GetType(selectorExpr.X))
			variable, packageType = lookupVariableFromAstExpr(service, method, block, selectorExpr, assign)
		} else {
			logger.Logger.Fatalf("[CFG LOOKUP] nil variable for composite lit (e.Type = %s): %v", utils.GetType(e.Type), e)
		}
	case *ast.TypeAssertExpr:
		variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
	case *ast.IndexExpr:
		variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
		if variable == nil {
			logger.Logger.Fatalf("[CFG LOOKUP] nil variable for index expr: %v (e.X type = %s)", e, utils.GetType(e.X))
		}
		if arrayVar, ok := variable.(*variables.ArrayVariable); ok {
			variable = arrayVar.GetElementAtIfExists(computeArrayIndex(e.Index))
			if variable == nil {
				variable = lookup.CreateVariableFromType("", arrayVar.GetArrayType().ElementsType)
				logger.Logger.Warnf("CREATED VARIABLE FROM NIL ARRAY ELEMENT %s | %s", variable.String(), arrayVar.String())
			}
		}
		if mapVar, ok := variable.(*variables.MapVariable); ok {
			key, _ := lookupVariableFromAstExpr(service, method, block, e.Index, false)
			variable, ok = mapVar.KeyValues[key]
			if !ok {
				logger.Logger.Warnf("[CFG LOOKUP] got map %v with unassigned value for key %s", mapVar.String(), key.String())
				variable = mapVar
			}
		}
	case *ast.UnaryExpr:
		if e.Op == token.AND { // e.g. &post
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
			addrType := &gotypes.AddressType{
				AddressOf: variable.GetType(),
			}
			variable = &variables.AddressVariable{
				AddressOf: variable,
				VariableInfo: &variables.VariableInfo{
					Type: addrType,
					Id:   variables.VARIABLE_INLINE_ID,
					Name: variable.GetVariableInfo().Name,
				},
			}
		} else if e.Op == token.MUL { // e.g. *post
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
			addrType := &gotypes.AddressType{
				AddressOf: variable.GetType(),
			}
			variable = &variables.PointerVariable{
				PointerTo: variable,
				VariableInfo: &variables.VariableInfo{
					Type: addrType,
					Id:   variables.VARIABLE_INLINE_ID,
					Name: variable.GetVariableInfo().Name,
				},
			}

		} else {
			logger.Logger.Fatalf("unknown token %v for unary expr %v", e.Op, e)
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
		}
	case *ast.BinaryExpr:
		if e.Op == token.ADD || e.Op == token.MUL {
			variable_x, t_x := lookupVariableFromAstExpr(service, method, block, e.X, assign)
			addrType_x := &gotypes.AddressType{
				AddressOf: variable_x.GetType(),
			}
			variable_x = &variables.AddressVariable{
				AddressOf: variable_x,
				VariableInfo: &variables.VariableInfo{
					Type: addrType_x,
					Id:   variables.VARIABLE_INLINE_ID,
					Name: variable_x.GetVariableInfo().Name,
				},
			}
			variable_y, t_y := lookupVariableFromAstExpr(service, method, block, e.X, assign)
			addrType_y := &gotypes.AddressType{
				AddressOf: variable_y.GetType(),
			}
			variable_y = &variables.AddressVariable{
				AddressOf: variable_y,
				VariableInfo: &variables.VariableInfo{
					Type: addrType_y,
					Id:   variables.VARIABLE_INLINE_ID,
					Name: variable_x.GetVariableInfo().Name,
				},
			}
			if !t_x.IsSameType(t_y) {
				logger.Logger.Fatalf("x expr (%v) and y expr (%v) differ types (%v vs %v)", e.X, e.Y, t_x, t_y)
			}
			packageType = t_x
			variable = variable_x
			logger.Logger.Warnf("FIXMEEEEEEE!!!!!!!!")
		} else {
			logger.Logger.Fatalf("unknown token %v for binary expr %v", e.Op, e)
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
		}
	case *ast.MapType: //e.g. make(map[string]PriceConfig)
		keyType := lookup.ComputeTypeForAstExpr(service.File, e.Key)
		valueType := lookup.ComputeTypeForAstExpr(service.File, e.Value)
		variable = &variables.MapVariable{
			KeyValues: make(map[variables.Variable]variables.Variable, 0),
			VariableInfo: &variables.VariableInfo{
				Type: &gotypes.MapType{
					KeyType: keyType,
					ValueType: valueType,
				},
				Id:   variables.VARIABLE_UNASSIGNED_ID,
			},
		}
	default:
		logger.Logger.Fatalf("[CFG LOOKUP] cannot lookup unknown type (%s) for variable (%v)", utils.GetType(e), e)
	}
	if variable == nil && packageType == nil {
		logger.Logger.Fatalf("[CFG LOOKUP] unexpected nil variable (or package) with type (%s) for expr (%v)", utils.GetType(expr), expr)
	}
	return variable, nil
}
