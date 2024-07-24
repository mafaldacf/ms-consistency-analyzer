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
	logger.Logger.Debugf("[CFG LOOKUP IDENT] (%s) looking up variable for ident (%s)", service.GetName(), ident.Name)
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
			Name:  impt.PackageName,
			Path:  impt.PackagePath,
		}
		return t
	}
	return nil
}

func wrapToFieldVariable(variable variables.Variable) *variables.FieldVariable {
	if fieldVariable, ok := variable.(*variables.FieldVariable); ok { // already field variable
		return fieldVariable
	}
	return &variables.FieldVariable{
		VariableInfo: &variables.VariableInfo{
			Type: &gotypes.FieldType{
				WrappedType: variable.GetType(),
			},
			Id: variables.VARIABLE_INLINE_ID,
		},
		WrappedVariable: variable,
	}
}

func unwrapTupleIfSingleElement(variable variables.Variable) variables.Variable {
	if tupleVar, ok := variable.(*variables.TupleVariable); ok && len(tupleVar.Variables) == 1 {
		return tupleVar.Variables[0]
	}
	return variable
}

// unwrapIfUserType returns the most inner unwrapped type along with the most inner user type
// if no user type is found, then it returns the current type twice
func unwrapIfUserType(t gotypes.Type) (gotypes.Type, gotypes.Type) {
	if userType, ok := t.(*gotypes.UserType); ok {
		unwrappedType, t := unwrapIfUserType(userType.UserType)
		// always return the inned user type
		// if we found a wrapped value, we return the current user type (which is the most inner one)
		if _, ok := t.(*gotypes.UserType); !ok {
			t = userType
		}
		return unwrappedType, t
	}
	return t, t
}

func lookupVariableFromAstExpr(service *service.Service, method *types.ParsedMethod, block *types.Block, expr ast.Expr, assign bool) (variable variables.Variable, packageType *gotypes.PackageType) {
	logger.Logger.Debugf("[CFG LOOKUP EXPR] (%s) visiting expression (%v)", utils.GetType(expr), expr)
	switch e := expr.(type) {
	case *ast.CallExpr:
		variable = parseAndSaveCall(service, method, block, e)
		variable = unwrapTupleIfSingleElement(variable)
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
		if variable != nil {
			return variable, nil
		}
		if utils.IsBuiltInGoTypeOrFunc(e.Name) {
			if utils.IsBuiltInGoFunc(e.Name) {
				logger.Logger.Warnf("FIXME: IDENTIFIED BUILT IN FUNC FOR (%s)", e.Name)
				return nil, nil
			}
		}
		if utils.IsBuiltInConstValue(e.Name) {
			typeName := utils.GetBuiltInConstTypeName(e.Name)
			basicType := &gotypes.BasicType{
				Name:  typeName,
				Value: e.Name,
			}
			variable = &variables.BasicVariable{
				VariableInfo: &variables.VariableInfo{
					Type: basicType,
					Id:   variables.VARIABLE_INLINE_ID,
				},
			}
			return variable, nil
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
				// note that variable can be either inline and thus we need to compute if type not found
				// in case of declarations with assignments, we don't reach this function
				// e.g. inline "bson.D{{"id", payment.ID}}" in coll.FindOne(ctx, bson.D{{"id", payment.ID}})
				t := lookup.LookupAndComputeTypesForGoTypes(service.GetPackage(), service.GetPackage().GetTypeInfo(e.Sel))
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

	case *ast.KeyValueExpr:
		if key, ok := e.Key.(*ast.Ident); ok {
			variable, _ = lookupVariableFromAstExpr(service, method, block, e.Value, false)
			variable = &variables.FieldVariable{
				VariableInfo: &variables.VariableInfo{
					Name: key.Name,
					Type: &gotypes.FieldType{
						WrappedType: variable.GetType(),
						FieldName:   key.Name,
					},
					Id: variables.VARIABLE_INLINE_ID,
				},
				WrappedVariable: variable,
			}
			logger.Logger.Debugf("KEY VALUE EXPR - RETURNING VARIABLE WITH TYPE (%s): %s", utils.GetType(variable), variable.String())
			return variable, nil
		}
		logger.Logger.Fatalf("[CFG LOOKUP] unsupported key type (%s) for expr: %v", utils.GetType(e.Key), e.Key)

	// examples:
	// (1) 	- expression:
	// 			query := bson.D{{Key: "postid", Value: postID}}
	// 		- composite lit 1 (e.Type is well defined):
	// 			 bson.D{{Key: "postid", Value: postID}}
	// 		- composite lit 2 (e.Type is nil):
	// 			{Key: "postid", Value: postID}
	// (2) 	- expression:
	// 			query := bson.D{{"index", 0}}
	// 		- composite lit 1 (e.Type is well defined):
	// 			 bson.D{{"index", 0}}
	// 		- composite lit 2 (e.Type is nil and e.Elts are unkeyed):
	// 			{"index", 0}
	// (3)  - expression:
	// 			mentions := []string{"alice", "bob"}
	// 		- composite lit:
	// 			[]string{"alice", "bob"}
	case *ast.CompositeLit:
		if e.Type == nil {
			structVariable := &variables.StructVariable{
				VariableInfo: &variables.VariableInfo{
					Type: &gotypes.StructType{},
					Id:   variables.VARIABLE_INLINE_ID,
				},
				Fields: make(map[string]variables.Variable),
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, false)
				logger.Logger.Debugf("[%s.%s] FOUND ELT VAR (%s) FOR COMPOSITE LIT (%v)", service.GetName(), method.GetName(), eltVar.String(), e)
				fieldVariable := wrapToFieldVariable(eltVar)
				structVariable.AddFieldVariableAndType(fieldVariable)
			}
			return structVariable, nil
		}

		eType := lookup.ComputeTypeForAstExpr(service.GetFile(), e.Type)
		eType, eTypeOrUserType := unwrapIfUserType(eType)

		switch eType.(type) {
		case *gotypes.StructType:
			structVariable := &variables.StructVariable{
				VariableInfo: &variables.VariableInfo{
					Type: eTypeOrUserType,
					Id:   variables.VARIABLE_INLINE_ID,
				},
				Fields: make(map[string]variables.Variable),
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, false)
				fieldVariable := wrapToFieldVariable(eltVar)
				structVariable.AddFieldVariable(fieldVariable)
			}
			return structVariable, nil
		case *gotypes.ArrayType:
			arrayVariable := &variables.ArrayVariable{
				VariableInfo: &variables.VariableInfo{
					Type: eTypeOrUserType,
					Id:   variables.VARIABLE_INLINE_ID,
				},
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, false)
				arrayVariable.AddElement(eltVar)
			}
			return arrayVariable, nil
		case *gotypes.SliceType:
			sliceVariable := &variables.SliceVariable{
				VariableInfo: &variables.VariableInfo{
					Type: eTypeOrUserType,
					Id:   variables.VARIABLE_INLINE_ID,
				},
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, false)
				sliceVariable.AddElement(eltVar)
			}
			return sliceVariable, nil
		default:
			logger.Logger.Warnf("[CFG LOOKUP] [%s.%s] unsupported type for eType (%s): %s", service.GetName(), method.GetName(), utils.GetType(eType), eType.String())
		}
		if selectorExpr, ok := e.Type.(*ast.SelectorExpr); ok {
			logger.Logger.Debugf("[CFG LOOKUP] [%s.%s] lookup up selector (%v.%v)", service.GetName(), method.GetName(), selectorExpr.X, selectorExpr.Sel)
			logger.Logger.Fatalf("[CFG LOOKUP] [%s.%s] lookup up selector (%v.%v)", service.GetName(), method.GetName(), selectorExpr.X, selectorExpr.Sel)
			variable, packageType = lookupVariableFromAstExpr(service, method, block, selectorExpr, assign)
			if variable == nil {
				logger.Logger.Fatalf("[CFG LOOKUP] unexpected nil variable for expr (%s): %v", utils.GetType(e.Type), e.Type)
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, false)
				if sliceVariable, ok := variable.(*variables.SliceVariable); ok {
					sliceVariable.AddElement(eltVar)
				} else if arrayVariable, ok := variable.(*variables.ArrayVariable); ok {
					arrayVariable.AddElement(eltVar)
				} else {
					logger.Logger.Fatalf("[CFG LOOKUP] unknown type for composite lit (%s)", utils.GetType(variable))
				}
			}
			logger.Logger.Debugf("[CFG LOOKUP] LOOKUP HERE!!! got selector (%s): %s", utils.GetType(variable), variable.String())
		} else {
			logger.Logger.Fatalf("[CFG LOOKUP] nil variable for composite lit (e.Type = %s): %v", utils.GetType(e.Type), e)
		}
	case *ast.TypeAssertExpr:
		variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, assign)
		assertedType := lookup.ComputeTypeForAstExpr(service.File, e.Type)
		if interfaceVariable, ok := variable.(*variables.InterfaceVariable); ok {
			interfaceVariable.UpgradeToAssertedType(assertedType)
			newVariable := lookup.CreateVariableFromType(variable.GetVariableInfo().GetName(), variable.GetType())
			newVariable.UpgradeFromPreviousInterface(interfaceVariable)
		} else {
			logger.Logger.Fatalf("[CFG LOOKUP] unexpected type (%s) for variable (%s)", utils.GetType(variable), variable.String())
		}
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
				t := mapVar.GetMapType().GetValueType()
				variable = lookup.CreateVariableFromType(key.GetType().GetBasicValue(), t)
				mapVar.AddKeyValuePair(key, variable)
				logger.Logger.Warnf("[CFG LOOKUP] got map %v with unassigned value for key %s \n\t\t\t\t\t\t\t => created new variable for key named (%s): %s", mapVar.String(), key.String(), key.GetType().GetBasicValue(), variable.String())
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
		if e.Op == token.ADD || e.Op == token.MUL || e.Op == token.SUB {
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
					KeyType:   keyType,
					ValueType: valueType,
				},
				Id: variables.VARIABLE_UNASSIGNED_ID,
			},
		}
	case *ast.ParenExpr: // e.g. "(weight - cp.InitialWeight)" in: price += (weight - cp.InitialWeight) * cp.WithinPrice
		variable, _ := lookupVariableFromAstExpr(service, method, block, e.X, false)
		variable.GetVariableInfo().Id = variables.VARIABLE_INLINE_ID
		return variable, nil
	default:
		logger.Logger.Fatalf("[CFG LOOKUP] cannot lookup unknown type (%s) for variable (%v)", utils.GetType(e), e)
	}
	if variable == nil && packageType == nil {
		logger.Logger.Fatalf("[CFG LOOKUP] unexpected nil variable (or package) with type (%s) for expr (%v)", utils.GetType(expr), expr)
	}
	return variable, nil
}
