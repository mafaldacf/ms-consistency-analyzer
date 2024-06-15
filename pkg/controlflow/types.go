package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	"go/ast"
	"go/token"
	"strconv"
	"strings"
	gotypes "go/types"
)

func parseExpressions(service *service.ServiceNode, method *service.ParsedFuncDecl, block *types.ParsedBlock, node ast.Node)  {
	switch e := node.(type) {
	// ------------
	// Go Routines
	// ------------
	case *ast.GoStmt:
		parseExpressions(service, method, block, e.Call.Fun)
	case *ast.FuncLit:
		for _, stmt := range e.Body.List {
			parseExpressions(service, method, block, stmt)
		}
	// ----------------------------
	// Declarations and Assignments
	// ----------------------------
	case *ast.DeclStmt:
		for _, spec := range e.Decl.(*ast.GenDecl).Specs {
			parseExpressions(service, method, block, spec)
		}
	case *ast.ValueSpec:
		// FIXME
		for _, v := range e.Values {
			saveCalls(service, method, block, v)
		}
		t := types.ComputeType(e.Type, service.File)
		for _, ident := range e.Names {
			decl := types.CreateTypeVariable(ident.Name, t)
			block.AddVariable(decl)
		}
	case *ast.AssignStmt:
		//FIXME: assignments can be from func calls
		/* for _, rvalue := range e.Rhs {
			logger.Logger.Info("IN ASSIGNMENT FOR SAVING CALL")
			saveCalls(service, method, block, rvalue)
		} */
		for _, rvalue := range e.Rhs {
			logger.Logger.Debugf("IN ASSIGNMENT FOR CREATING VARIABLE (type = %s)", utils.GetType(rvalue))
			variable := getOrCreateVariable(service, method, block, rvalue, true)

			if tupleVariable, ok := variable.(*types.TupleVariable); ok {
				if len(e.Lhs) != len(tupleVariable.Variables) {
					logger.Logger.Fatalf("number of left values (%d) does not match length of tuple variables (%d) for assignment %v", len(e.Lhs), len(tupleVariable.Variables), e)
				}
				for i, lvalue := range e.Lhs {
					variable = tupleVariable.Variables[i]
					variable.GetVariableInfo().SetName(lvalue.(*ast.Ident).Name)
					variable.GetVariableInfo().SetUnassigned()
					block.AddVariable(variable)
				}
			} else {
				for _, lvalue := range e.Lhs {
					// copy rh since there can be more lhs than rhs
					variableCopy := variable.DeepCopy()
					variableCopy.GetVariableInfo().SetName(lvalue.(*ast.Ident).Name)
					variableCopy.GetVariableInfo().SetUnassigned()
					block.AddVariable(variableCopy)
				}
			}
		}
	// -----------------------------
	// Expressions for new Variables
	// -----------------------------
	case *ast.KeyValueExpr: // e.g. from structure declarations
		parseExpressions(service, method, block, e.Key)
		parseExpressions(service, method, block, e.Value)
	case *ast.SelectorExpr:
		parseExpressions(service, method, block, e.X)
	case *ast.CompositeLit:
		// e.g. creating a structure where a field is obtained from a function call
		logger.Logger.Debugf("FFFOOOOUNNDDD COMPOSITE LITE %v", e.Elts)
		for _, elt := range e.Elts {
			parseExpressions(service, method, block, elt)
		}
	// -----------------------------------
	// Calls and Parenthesized Expressions
	// -----------------------------------
	case *ast.CallExpr:
		// a call expr can also happen upon a structure assignment
		// e.g. post := Post { ... }
		saveCallIfValid(service, method, block, e)
	case *ast.ParenExpr:
		// e.g. when used as a bool value in an if statement (assumes it is inside a parentheses)
		// in this case, the unfolded node from ParenExpr is a CallExpr
		parseExpressions(service, method, block, e.X)
	// -----------------
	// Other Expressions
	// -----------------
	case *ast.ExprStmt:
		parseExpressions(service, method, block, e.X)
	case *ast.UnaryExpr: // e.g. <-forever
		parseExpressions(service, method, block, e.X)
	case *ast.BinaryExpr: // e.g. if err != nil
		parseExpressions(service, method, block, e.X)
		parseExpressions(service, method, block, e.Y)
	// ----------------
	// Other Statements
	// ----------------
	case *ast.IncDecStmt: // e.g. decrement in loop
		parseExpressions(service, method, block, e.X)
	case *ast.ReturnStmt:
		for _, r := range e.Results {
			parseExpressions(service, method, block, r)
		}
	case *ast.DeferStmt:
		parseExpressions(service, method, block, e.Call.Fun)
	// ----------------
	// Ignore Remaining
	// ----------------
	// following types can only happen within "loose" expressions with no assignments
	case *ast.Ident: // e.g. err in err != nil
	case *ast.TypeAssertExpr:
	case *ast.BasicLit: // e.g. integers (1), strings ("foo"), etc
	case *ast.IfStmt:

	default:
		logger.Logger.Fatalf("unknown type in parseExpressions for type %s: %v", utils.GetType(node), node)
	}
}

func createVariableFromCallExpr(service *service.ServiceNode, method *service.ParsedFuncDecl, block *types.ParsedBlock, callExpr *ast.CallExpr) service.Call {
	logger.Logger.Debugf(">>>>>GOT GO TYPE: %v", utils.GetType(service.GetPackage().GetTypeInfo(callExpr)))
	parsedCall := saveFuncCallIfValid(service, method, callExpr)
	if parsedCall == nil {
		return nil
	}
	for i, arg := range callExpr.Args {
		param := getOrCreateVariable(service, method, block, arg, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetVariableInfo().Type.(*types.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetVariableInfo().Type.String())
		}
		parsedCall.AddParam(param)
	}
	logger.Logger.Infof("[CFG] found call %s", parsedCall.String())
	return parsedCall
}

func getOrCreateVariable(service *service.ServiceNode, method *service.ParsedFuncDecl, block *types.ParsedBlock, expr ast.Expr, assign bool) (variable types.Variable) {
	switch e := expr.(type) {
	case *ast.CallExpr:
		tupleVar := &types.TupleVariable{}
		//FIXME: this is kinda hard coded and must be automated
		goTypeInfo := service.GetPackage().GetTypeInfo(e)
		if parsedCall := createVariableFromCallExpr(service, method, block, e); parsedCall != nil {
			logger.Logger.Warnf("GOT PARSED CALL %s WITH METHOD %s", parsedCall.String(), parsedCall.GetMethod())
			for _, rt := range parsedCall.GetMethod().GetReturns() {
				tupleVar.Variables = append(tupleVar.Variables, types.CreateTypeVariable("", rt.GetType()))
			}
		} else {
			//callStr := computeFunctionCallName(e.Fun) + "(...)"
			// FIXME: THIS IS VEEEEEEERRYYYYYY HARD CODE AND MUUUUUUSSST BE AUTOMATED
			if goTupleType, ok := goTypeInfo.(*gotypes.Tuple); ok {
				for i := 0; i < goTupleType.Len(); i ++ {
					//goType := goTupleType.At(i)
					//newType, ok := service.File.Package.GetImportedTypeFromPath(goType.String())
					newType := &types.GenericType{
						Name: goTupleType.String(),
					}
					genericVariable := &types.CompositeVariable{
						VariableInfo: &types.VariableInfo{
							Type: newType,
							Id: types.VARIABLE_INLINE_ID,
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
						Id: types.VARIABLE_INLINE_ID,
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
			newType := types.ComputeType(e, service.File)
			variable = types.GetOrCreateVariableFromType("", newType)
		}

		switch v := variable.(type) {
		case *types.GenericVariable:
			// continue
		case *types.StructVariable:
			logger.Logger.Debugf("GOT SELECTOR FOR %s", e.Sel.Name)
			variable = v.GetOrCreateField(e.Sel.Name)
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
				ElementsType: types.ComputeType(arrayTypeAst.Elt, service.File),
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

func createCompositeVariable(typeName string) *types.CompositeVariable {
	return &types.CompositeVariable{
		VariableInfo: &types.VariableInfo{
			Type: &types.GenericType{
				Name: typeName,
			},
			Id: types.VARIABLE_INLINE_ID,
		},
	}
}

func computeFunctionCallName(expr ast.Expr) string {
	switch e := expr.(type) {
	case *ast.Ident:
		return e.Name
	case *ast.SelectorExpr:
		return computeFunctionCallName(e.X) + "." + e.Sel.Name
	}
	logger.Logger.Fatalf("could not compute function call name for expr %s (type = %s)", expr, utils.GetType(expr))
	return ""
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
