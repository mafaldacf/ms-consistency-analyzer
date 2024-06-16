package controlflow

import (
	"go/ast"

	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
)

func ParseServiceMethodCFG(node *service.Service, method *types.ParsedMethod) {
	var visited = make(map[int32]bool)
	for _, block := range method.ParsedCfg.GetParsedBlocks() {
		visitBasicBlock(node, method, block, visited)
	}
	logger.Logger.Debugln()
}

func visitBasicBlock(node *service.Service, method *types.ParsedMethod, block *types.Block, visited map[int32]bool) {
	if visited[block.GetIndex()] {
		return
	}
	visited[block.GetIndex()] = true
	for _, blockNode := range block.GetNodes() {
		parseExpressions(node, method, block, blockNode)
	}

	for _, succ := range block.GetSuccs() {
		parsedSucc := method.ParsedCfg.GetParsedBlockAtIndex(succ.Index)
		parsedSucc.CopyVarsFromPredecessor(block)
		visitBasicBlock(node, method, parsedSucc, visited)
	}
}

func parseExpressions(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) {
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
		t := service.File.ComputeTypeForExpr(e.Type)
		for _, ident := range e.Names {
			decl := createVariableFromType(ident.Name, t)
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
		saveFuncCallIfValid(service, method, block, e)
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

func saveCalls(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) {
	logger.Logger.Infof("---------- %v", utils.GetType(node))
	switch e := node.(type) {
	case *ast.CallExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD CALL EXPR %v", e)
		saveFuncCallIfValid(service, method, block, e)
	case *ast.CompositeLit:
		// e.g. creating a structure where a field is obtained from a function call
		logger.Logger.Infof("FFFOOOOUNNDDD COMPOSITE LITE %v", e)
		for _, elt := range e.Elts {
			saveCalls(service, method, block, elt)
		}
	case *ast.KeyValueExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD KEYYY VALLUEEEEE EXPR %v", e)
		saveCalls(service, method, block, e.Key)
		saveCalls(service, method, block, e.Value)
	case *ast.SelectorExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD SELECTOR EXPR %v", e)
		saveCalls(service, method, block, e.X)
	case *ast.Ident:
		logger.Logger.Infof("FFFOOOOUNNDDD IDENT %v", e)
	case *ast.TypeAssertExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD TYPE ASSERT EXPR %v", e)
	case *ast.BasicLit: // e.g. integers (1), strings ("foo"), etc
		logger.Logger.Infof("FFFOOOOUNNDDD BASIC LIT %v", e)
	default:
		logger.Logger.Fatalf("unknown type in saveCalls for type %s: %v", utils.GetType(e), e)
	}
}

func getReceiverIfValid(selectorExpr *ast.SelectorExpr, methodRecvIdent *ast.Ident, block *types.Block) (*ast.Ident, types.Variable, bool) {
	if recvIdent, ok := selectorExpr.X.(*ast.Ident); ok {
		// current method receiver
		if recvIdent.Name == methodRecvIdent.Name {
			return recvIdent, nil, true
		}
		// an NoSQL collection from a previous field
		if variable := block.GetLastestVariable(recvIdent.Name); variable != nil {
			return recvIdent, variable, true
		}
	}
	return nil, nil, false
}

func getCallIfSelectedField(node ast.Node, methodRecvIdent *ast.Ident, block *types.Block) (funcCall *ast.CallExpr, methodIdent *ast.Ident, fieldIdent *ast.Ident, serviceRecvIdent *ast.Ident, variable types.Variable, ok bool) {
	if funcCall, ok := node.(*ast.CallExpr); ok {
		// e.g. f.queue.Push
		//    ^ident2 ^ident ^method
		// e.g. f.storageService.StorePost
		//      ^ident2  ^ident    ^method
		if methodSel, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if fieldSel, ok := methodSel.X.(*ast.SelectorExpr); ok {
				if recvIdent, _, ok := getReceiverIfValid(fieldSel, methodRecvIdent, block); ok && recvIdent != nil {
					return funcCall, methodSel.Sel, fieldSel.Sel, recvIdent, nil, true
				}
			} else if recvIdent, variable, ok := getReceiverIfValid(methodSel, methodRecvIdent, block); ok {
				return funcCall, methodSel.Sel, nil, recvIdent, variable, true
			}
		}
	}
	return nil, nil, nil, nil, nil, false
}

func saveFuncCallParams(service *service.Service, method *types.ParsedMethod, block *types.Block, parsedCall types.Call, args []ast.Expr) {
	for i, arg := range args {
		param := getOrCreateVariable(service, method, block, arg, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetVariableInfo().Type.(*types.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetVariableInfo().Type.String())
		}
		parsedCall.AddParam(param)
	}
	logger.Logger.Infof("[CFG] added params to func call %s", parsedCall.String())
}

func saveFuncCallIfValid(node *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) types.Call {
	funcCall, methodIdent, fieldIdent, serviceRecvIdent, variable, ok := getCallIfSelectedField(callExpr, method.Recv, block)
	if !ok {
		return nil
	}
	if fieldIdent != nil {
		// if the targeted variable corresponds to a service field
		if field, ok := node.Fields[fieldIdent.Name]; ok {
			if serviceField, ok := field.(*types.ServiceField); ok {
				// store function call either as service call or database call
				// if the field corresponds to a service field
				// 1. extract the service field from the current service
				// 2. get the target node service for the type
				// 3. add the targeted method of the other service for the current call expression
				targetServiceType := serviceField.GetTypeName()
				targetServiceNode := node.Services[targetServiceType]
				targetMethod := targetServiceNode.ExposedMethods[methodIdent.Name]
				parsedCall := &types.ParsedServiceCall{
					ParsedCall: types.ParsedCall{
						Ast:         funcCall,
						Receiver:    serviceRecvIdent.Name,
						TargetField: fieldIdent.Name,
						Name:        methodIdent.Name,
						Pos:         funcCall.Pos(),
						Method:      targetMethod,
					},
					CallerTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
					CalleeTypeName: serviceField.GetType(),
				}
				saveFuncCallParams(node, method, block, parsedCall, callExpr.Args)
				method.Calls = append(method.Calls, parsedCall)
				logger.Logger.Infof("[CFG] found new service call %s", parsedCall.Name)
				return parsedCall
			} else if databaseField, ok := field.(*types.DatabaseField); ok {
				// if the field corresponds to a database field
				// 1. extract the service field from the current service
				// 2. get the target database node
				// 3. add the target method for the current call expression
				blueprintType := databaseField.FieldInfo.Type.(*blueprint.BackendType)
				blueprintMethod := blueprintType.GetMethod(methodIdent.Name)
				parsedCall := &types.ParsedDatabaseCall{
					ParsedCall: types.ParsedCall{
						Ast:         funcCall,
						Receiver:    serviceRecvIdent.Name,
						TargetField: fieldIdent.Name,
						Name:        methodIdent.Name,
						Pos:         funcCall.Pos(),
						Method:      blueprintMethod,
					},
					CallerTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
					DbInstance:     databaseField.DbInstance,
				}
				saveFuncCallParams(node, method, block, parsedCall, callExpr.Args)

				// maybe user is just getting the collection
				if blueprintType.IsNoSQLDatabase() && blueprintMethod.IsNoSQLGetCollectionCall() {
					blueprintMethod.SetNoSQLDatabaseCollection(
						parsedCall.Params[1].GetVariableInfo().Type.GetBasicValue(),
						parsedCall.Params[2].GetVariableInfo().Type.GetBasicValue(),
						databaseField.DbInstance,
					)
					logger.Logger.Infof("[CFG] found blueprint backend call NoSQLDatabase.GetCollection() %s", parsedCall.Name)
				} else {
					method.Calls = append(method.Calls, parsedCall)
					logger.Logger.Infof("[CFG] found new database call %s", parsedCall.Name)
				}
				return parsedCall
			} else {
				logger.Logger.Fatalf("[CFG] unknown call %v for field %s with type %s", callExpr.Fun, field.String(), utils.GetType(field))
			}
		}
	} else if variable != nil {
		if collectionVariable, ok := variable.(*blueprint.NoSQLCollectionVariable); ok {
			blueprintType := collectionVariable.VariableInfo.Type.(*blueprint.BackendType)
			blueprintMethod := blueprintType.GetMethod(methodIdent.Name)
			parsedCall := &types.ParsedDatabaseCall{
				ParsedCall: types.ParsedCall{
					Ast:         funcCall,
					Receiver:    serviceRecvIdent.Name,
					TargetField: collectionVariable.VariableInfo.GetName(),
					Name:        methodIdent.Name,
					Pos:         funcCall.Pos(),
					Method:      blueprintMethod,
				},
				CallerTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
				DbInstance:     blueprintType.DbInstance,
			}
			saveFuncCallParams(node, method, block, parsedCall, callExpr.Args)
			method.Calls = append(method.Calls, parsedCall)
			logger.Logger.Infof("[CFG] found new database call for NoSQL collection %s", parsedCall.Name)
		}
	}
	if funcDecl, ok := node.InternalMethods[methodIdent.Name]; ok {
		parsedCall := &types.ParsedInternalCall{
			ParsedCall: types.ParsedCall{
				Ast:      funcCall,
				Receiver: serviceRecvIdent.Name,
				Name:     methodIdent.Name,
				Method:   funcDecl,
				Pos:      funcCall.Pos(),
			},
			ServiceTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
		}
		saveFuncCallParams(node, method, block, parsedCall, callExpr.Args)
		method.Calls = append(method.Calls, parsedCall)
		logger.Logger.Infof("[CFG] found new internal call %s", parsedCall.Name)
		return parsedCall
	}

	logger.Logger.Warnf("[CFG] cannot save unknown call %v", callExpr.Fun)
	return nil
}
