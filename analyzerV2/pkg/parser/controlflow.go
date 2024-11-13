package controlflow

import (
	"go/ast"
	/* "go/token"
	gotypes "go/types" */

	"analyzer/pkg/app/app"
	"analyzer/pkg/app/services"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/objects"
	"analyzer/pkg/utils"
)

func ParseServiceConstructors(app *app.App) {
	//TODO
}

func ParseRPCMethods(app *app.App) {
	for _, service := range app.Services {
		for _, method := range service.Methods() {
			if service.Name() == "ProductService" && method.Name() == "CreateProduct" {
				logger.Logger.Infof("[PARSER] [%s] visiting remote method (%s)", service.Name(), method.Name())
				parseBlock(service, method, method.ControlFlow().EntryBlock())
			}
		}
	}
}

func parseBlock(service *services.Service, method *types.Method, block *types.Block) {
	if block.Visited() {
		return
	}

	// block.Block().Stmt can be type:
	// - *ast.BlockStmt:
	// - *ast.ForStmt:
	// - *ast.ReturnStmt:

	var deferStmts []*ast.DeferStmt
	block.SetVisited()
	for _, node := range block.BlockNodes() {
		deferStmts = append(deferStmts, parseNode(service, method, block, node)...)
	}

	for _, deferStmt := range deferStmts {
		parseNode(service, method, block, deferStmt.Call)
	}

	// FIXME: skip going again for loop
	if block.BlockIsIfThen() {
		return
	}

	for _, succ := range block.Succs() {
		succ.SetVars(block.Vars())
		parseBlock(service, method, succ)
	}
}

func parseNode(service *services.Service, method *types.Method, block *types.Block, node ast.Node) []*ast.DeferStmt {
	logger.Logger.Warnf("[PARSER] [%s] visiting block (%d) node: %s", service.Name(), block.Index(), node)
	var deferStmts []*ast.DeferStmt
	logger.Logger.Debugf("[CFG - PARSE EXPR] (%s) visiting node (%v)", utils.GetType(node), node)
	switch e := node.(type) {
	// ------------
	// Go Routines
	// ------------
	case *ast.GoStmt:
	// ----------------------------
	// Declarations and Assignments
	// ----------------------------
	case *ast.DeclStmt: // e.g. foobar := "foobar"
		for _, spec := range e.Decl.(*ast.GenDecl).Specs {
			parseNode(service, method, block, spec)
		}
	case *ast.ValueSpec: // e.g. var foobar OR var foobar = "foobar"
	case *ast.AssignStmt: // e.g. for i := 0
	// -----------------------------------
	// Calls and Parenthesized Expressions
	// -----------------------------------
	case *ast.CallExpr:
	case *ast.ParenExpr:
	// -----------------
	// Other Expressions
	// -----------------
	case *ast.ExprStmt:
		parseNode(service, method, block, e.X)
	case *ast.UnaryExpr: // e.g. <-forever
	// -------
	// Returns
	// -------
	case *ast.ReturnStmt:
		/* var out objects.Variable
		for _, expr := range e.Results {
			v, _ := lookupVariableFromExpr(service, method, block, expr)
			out = append(out, v)
		}
		block.SetOut(out) */
	// -------------
	// If Statements
	// -------------
	case *ast.IfStmt: // FIXME: we should not needs this! we are only encountering this because we are fully parsing the GoStmt
	case *ast.BinaryExpr: // FIXME: same... e.g. if err != nil
	case *ast.Ident: // FIXME: same... e.g. if flag ...
	case *ast.SelectorExpr: // FIXME: same...

	// ---------
	// For Loops
	// ---------
	case *ast.IncDecStmt: // e.g. increment in ForPost block (e.g. i++)

	// ----------------
	// Other Statements
	// ----------------
	case *ast.DeferStmt:
		deferStmts = append(deferStmts, e)

	// ----------------
	// Ignore Remaining
	// ----------------
	default:
		logger.Logger.Fatalf("[PARSER] [%s.%s] unknown type in parseExpressions: %s", service.Name(), method.Name(), utils.GetType(node))
	}
	return deferStmts
}

func lookupVariableFromExpr(service *services.Service, method *types.Method, block *types.Block, expr ast.Expr) objects.Object {
	logger.Logger.Debugf("[LOOKUP] [%s] lookup variable for expression (%s): %v", service.Name(), utils.GetType(expr), expr)
	/* switch e := expr.(type) {
	case *ast.Ident:
		variable = lookupVariableFromIdentIfExists(service, block, e)
		if variable != nil {
			return variable, nil
		}

		packageType = lookupImportedPackageFromIdent(service, e)
		if packageType != nil {
			return nil, packageType
		}
		logger.Logger.Fatalf("[CFG - LOOKUP VAR] unexpected nil variable (or package) with type (%s) for expr (%v)", utils.GetType(expr), expr)
		return nil, nil
	} */
	return nil
}

/* func lookupVariableFromExpr(service *services.Service, method *types.Method, block *types.Block, expr ast.Expr) objects.Variable {
	logger.Logger.Debugf("[LOOKUP] (%s) visiting expression (%v)", utils.GetType(expr), expr)

    var variable objects.Variable
	switch e := expr.(type) {
    case *ast.Ident:
		variable = lookupVariableFromIdentIfExists(service, block, e)
		if variable != nil {
			return variable, nil
		}

		packageType = lookupImportedPackageFromIdent(service, e)
		if packageType != nil {
			return nil, packageType
		}
		logger.Logger.Fatalf("[CFG - LOOKUP VAR] unexpected nil variable (or package) with type (%s) for expr (%v)", utils.GetType(expr), expr)
		return nil, nil

	case *ast.CallExpr:
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
	case *ast.SelectorExpr:
		variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
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

			variable = importedPkg.GetDeclaredVariableOrConst(e.Sel)
			return variable, nil
		}
		if tupleVariable, ok := variable.(*variables.TupleVariable); ok {
			if tupleVariable.NumVariables() == 1 {
				variable = tupleVariable.GetVariableAt(0)
			} else {
				logger.Logger.Fatalf("[CFG - LOOKUP VAR] unexpected number (%d) of variables in tuple: %s", tupleVariable.NumVariables(), tupleVariable.String())
			}
		}

		field := lookupFieldForVariable(variable, e.Sel.Name, inAssignment)
		return field, nil

	case *ast.KeyValueExpr:
		if key, ok := e.Key.(*ast.Ident); ok {
			variable, _ = lookupVariableFromAstExpr(service, method, block, e.Value, nil, false)
			fieldVariable := &variables.FieldVariable{
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
			variable.GetVariableInfo().SetParent(variable, fieldVariable)
			logger.Logger.Debugf("KEY VALUE EXPR - RETURNING VARIABLE WITH TYPE (%s): %s", utils.GetType(variable), variable.String())
			return fieldVariable, nil
		}
		logger.Logger.Fatalf("[CFG - LOOKUP VAR] unsupported key type (%s) for expr: %v", utils.GetType(e.Key), e.Key)

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
		logger.Logger.Debugf("INSIDE COMPOSITE LIT FOR e.Type (%v), and e.Elts (%v)", e.Type, e.Elts)
		if e.Type == nil {
			structVariable := &variables.StructVariable{
				VariableInfo: &variables.VariableInfo{
					Type: &gotypes.StructType{},
					Id:   variables.VARIABLE_INLINE_ID,
				},
				Fields: make(map[string]variables.Variable),
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, nil, false)
				logger.Logger.Debugf("--------- [%s.%s] FOUND ELT VAR (%s) FOR COMPOSITE LIT (%v)", service.GetName(), method.GetName(), eltVar.String(), e)
				variables.WrapToFieldVariable(eltVar, structVariable, true)
			}
			return structVariable, nil
		}

		eType := lookup.ComputeTypeForAstExpr(service.GetFile(), e.Type)
		eType, eTypeOrUserType := gotypes.UnwrapUserType(eType)

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
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, nil, false)
				variables.WrapToFieldVariable(eltVar, structVariable, false)
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
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, nil, false)
				arrayVariable.AddElement(eltVar)
				eltVar.GetVariableInfo().SetParent(eltVar, arrayVariable)
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
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, nil, false)
				sliceVariable.AddElement(eltVar)
				eltVar.GetVariableInfo().SetParent(eltVar, sliceVariable)
			}
			return sliceVariable, nil
		default:
			logger.Logger.Warnf("[CFG - LOOKUP VAR] [%s.%s] unsupported type for eType (%s): %s", service.GetName(), method.GetName(), utils.GetType(eType), eType.String())
		}
		if selectorExpr, ok := e.Type.(*ast.SelectorExpr); ok {
			logger.Logger.Debugf("[CFG - LOOKUP VAR] [%s.%s] lookup up selector (%v.%v)", service.GetName(), method.GetName(), selectorExpr.X, selectorExpr.Sel)
			logger.Logger.Fatalf("[CFG - LOOKUP VAR] [%s.%s] lookup up selector (%v.%v)", service.GetName(), method.GetName(), selectorExpr.X, selectorExpr.Sel)
			variable, packageType = lookupVariableFromAstExpr(service, method, block, selectorExpr, nil, inAssignment)
			if variable == nil {
				logger.Logger.Fatalf("[CFG - LOOKUP VAR] unexpected nil variable for expr (%s): %v", utils.GetType(e.Type), e.Type)
			}
			for _, elt := range e.Elts {
				eltVar, _ := lookupVariableFromAstExpr(service, method, block, elt, nil, false)
				if sliceVariable, ok := variable.(*variables.SliceVariable); ok {
					sliceVariable.AddElement(eltVar)
				} else if arrayVariable, ok := variable.(*variables.ArrayVariable); ok {
					arrayVariable.AddElement(eltVar)
				} else {
					logger.Logger.Fatalf("[CFG - LOOKUP VAR] unknown type for composite lit (%s)", utils.GetType(variable))
				}
			}
			logger.Logger.Debugf("[CFG - LOOKUP VAR] LOOKUP HERE!!! got selector (%s): %s", utils.GetType(variable), variable.String())
		} else {
			logger.Logger.Fatalf("[CFG - LOOKUP VAR] nil variable for composite lit (e.Type = %s): %v", utils.GetType(e.Type), e)
		}
	case *ast.TypeAssertExpr:
		variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
		assertedType := lookup.ComputeTypeForAstExpr(service.File, e.Type)
		if interfaceVariable, ok := variable.(*variables.InterfaceVariable); ok {
			// FIXME: it is creating two duplicates:
			// (i) InterfaceVariable during lookup with e.g. BasicType after UpgradeToAssertedType
			// (ii) The e.g. BasicVariable after UpgradeFromPreviousInterface with e.g. the BasicType
			//interfaceVariable.UpgradeToAssertedType(assertedType)
			newVariable := lookup.CreateVariableFromType(variable.GetVariableInfo().GetName(), assertedType)
			newVariable.UpgradeFromPreviousInterface(interfaceVariable)
			block.AddVariable(newVariable)
			logger.Logger.Warnf("[FIXME - ASSERT!!!!] CREATED NEW VARIABLE (%s): %s", variables.VariableTypeName(newVariable), newVariable.String())
			return newVariable, nil
		} else {
			logger.Logger.Fatalf("[CFG - LOOKUP VAR] unexpected type (%s) for variable (%s)", utils.GetType(variable), variable.String())
		}
	case *ast.IndexExpr:
		variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
		if variable == nil {
			logger.Logger.Fatalf("[CFG - LOOKUP VAR] nil variable for index expr: %v (e.X type = %s)", e, utils.GetType(e.X))
		}
		if arrayVar, ok := variable.(*variables.ArrayVariable); ok {
			variable = arrayVar.GetElementAtIfExists(computeArrayIndex(e.Index))
			if variable == nil {
				variable = lookup.CreateVariableFromType("", arrayVar.GetArrayType().ElementsType)
				logger.Logger.Warnf("CREATED VARIABLE FROM NIL ARRAY ELEMENT %s | %s", variable.String(), arrayVar.String())
			}
		}
		if mapVar, ok := variable.(*variables.MapVariable); ok {
			key, _ := lookupVariableFromAstExpr(service, method, block, e.Index, nil, false)
			variable, ok = mapVar.KeyValues[key]
			if !ok {
				t := mapVar.GetMapType().GetValueType()
				variable = lookup.CreateVariableFromType(key.GetType().GetBasicValue(), t)
				mapVar.AddKeyValuePair(key, variable)
				logger.Logger.Warnf("[CFG - LOOKUP VAR] got map %v with unassigned value for key %s \n\t\t\t\t\t\t\t => created new variable for key named (%s): %s", mapVar.String(), key.String(), key.GetType().GetBasicValue(), variable.String())
			}
		}
	case *ast.UnaryExpr:
		if e.Op == token.AND { // e.g. &post
			// creates a pointer to the variable
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
			ptrType := &gotypes.PointerType{
				PointerTo: variable.GetType(),
			}
			ptrVariable := &variables.PointerVariable{
				PointerTo: variable,
				VariableInfo: &variables.VariableInfo{
					Type: ptrType,
					Id:   variables.VARIABLE_INLINE_ID,
					Name: variable.GetVariableInfo().Name,
				},
			}
			variable.GetVariableInfo().SetParent(variable, ptrVariable)
			return ptrVariable, packageType
		} else if e.Op == token.MUL { // e.g. *post
			// dereferences the pointer and gets the value of the variable
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
			if ptrVariable, ok := variable.(*variables.PointerVariable); ok {
				return ptrVariable.PointerTo, packageType
			}
			logger.Logger.Fatalf("[LOOKUP] [%s] unexpected variable (%s) for unary token '*': %s", service.GetName(), utils.GetType(variable), variable.LongString())

		} else {
			logger.Logger.Fatalf("unknown token %v for unary expr %v", e.Op, e)
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
		}
	case *ast.BinaryExpr:
		if e.Op == token.ADD || e.Op == token.MUL || e.Op == token.SUB {
			variable_x, t_x := lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
			addrType_x := &gotypes.AddressType{
				AddressOf: variable_x.GetType(),
			}
			address_variable_x := &variables.AddressVariable{
				AddressOf: variable_x,
				VariableInfo: &variables.VariableInfo{
					Type: addrType_x,
					Id:   variables.VARIABLE_INLINE_ID,
					Name: variable_x.GetVariableInfo().Name,
				},
			}
			variable_x.GetVariableInfo().SetParent(variable_x, address_variable_x)

			variable_y, t_y := lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
			addrType_y := &gotypes.AddressType{
				AddressOf: variable_y.GetType(),
			}
			address_variable_y := &variables.AddressVariable{
				AddressOf: variable_y,
				VariableInfo: &variables.VariableInfo{
					Type: addrType_y,
					Id:   variables.VARIABLE_INLINE_ID,
					Name: variable_x.GetVariableInfo().Name,
				},
			}
			variable_y.GetVariableInfo().SetParent(variable_y, address_variable_y)

			if !t_x.IsSameType(t_y) {
				logger.Logger.Fatalf("x expr (%v) and y expr (%v) differ types (%v vs %v)", e.X, e.Y, t_x, t_y)
			}
			packageType = t_x
			variable = address_variable_x
			logger.Logger.Warnf("FIXMEEEEEEE!!!!!!!!")
		} else {
			logger.Logger.Fatalf("unknown token %v for binary expr %v", e.Op, e)
			variable, packageType = lookupVariableFromAstExpr(service, method, block, e.X, nil, inAssignment)
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
		variable, _ := lookupVariableFromAstExpr(service, method, block, e.X, nil, false)
		variable.GetVariableInfo().Id = variables.VARIABLE_INLINE_ID
		return variable, nil
	case *ast.FuncLit:
		return &variables.FuncVariable{
			VariableInfo: &variables.VariableInfo{
				Id: variables.VARIABLE_INLINE_ID,
				Type: &gotypes.FuncTypeType{
					Body: e.Body,
					Params: e.Type.Params,
				},
			},
		}, nil
	default:
		logger.Logger.Fatalf("[CFG - LOOKUP VAR] cannot lookup unknown type (%s) for variable (%v)", utils.GetType(e), e)
	}
	if variable == nil && packageType == nil {
		logger.Logger.Fatalf("[CFG - LOOKUP VAR] unexpected nil variable (or package) with type (%s) for expr (%v)", utils.GetType(expr), expr)
	}
	return variable, nil
} */
