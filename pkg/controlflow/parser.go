package controlflow

import (
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
	"go/ast"

	"analyzer/pkg/service"
	"analyzer/pkg/utils"
)

func ParseServiceMethodCFG(node *service.ServiceNode, method *service.ParsedFuncDecl) {
	var visited = make(map[int32]bool)
	for _, parsedBlock := range method.ParsedCfg.GetParsedBlocks() {
		visitBasicBlock(node, method, parsedBlock, visited)
	}
	logger.Logger.Debugln()
}

func visitBasicBlock(node *service.ServiceNode, parsedFuncDecl *service.ParsedFuncDecl, parsedBlock *types.ParsedBlock, visited map[int32]bool) {
	if visited[parsedBlock.GetIndex()] {
		return
	}
	visited[parsedBlock.GetIndex()] = true
	for _, blockNode := range parsedBlock.GetNodes() {
		// variable declaration and assignments
		stmts, found := getStmtsIfInlineGoRoutine(blockNode)
		if found {
			for _, stmt := range stmts {
				saveDeclsAndAssigns(node, parsedBlock, stmt)
			}
		} else {
			saveDeclsAndAssigns(node, parsedBlock, blockNode)
		}
		// service, function, and database calls
		saveCalls(node, blockNode, parsedBlock, parsedFuncDecl)
	}

	for _, succ := range parsedBlock.GetSuccs() {
		parsedSucc := parsedFuncDecl.ParsedCfg.GetParsedBlockAtIndex(succ.Index)
		parsedSucc.CopyVarsFromPredecessor(parsedBlock)
		visitBasicBlock(node, parsedFuncDecl, parsedSucc, visited)
	}
}

func getStmtsIfInlineGoRoutine(node ast.Node) ([]ast.Node, bool) {
	var stmts []ast.Node
	var found bool = false
	if goStmt, ok := node.(*ast.GoStmt); ok {
		if funcLit, ok := goStmt.Call.Fun.(*ast.FuncLit); ok {
			for _, stmt := range funcLit.Body.List {
				stmts = append(stmts, stmt)
				found = true
			}
		}
	}
	return stmts, found
}

func saveDeclsAndAssigns(serviceNode *service.ServiceNode, parsedBlock *types.ParsedBlock, node ast.Node) {
	vars, ok := types.IsVarDeclOrAssign(serviceNode.File, parsedBlock.Vars, node)
	if ok {
		logger.Logger.Debugf("adding variables %v to block", vars)
		parsedBlock.AddVariables(vars)
	}
}

// hasFuncCall
// check if we found an ast node representing a database or service function call
//
// note that function calls can be embedded into:
//  1. ExprStmt 	 - simple function call
//  2. AssignStmt - assignment like errors from the return values of the function
//  3. ParenExpr  - e.g. when used as a bool value in an if statement (assumes it is inside a parentheses)
//     in this case, the unfolded node from ParenExpr is a CallExpr
func saveCalls(node *service.ServiceNode, blockNode ast.Node, parsedBlock *types.ParsedBlock, parsedFuncDecl *service.ParsedFuncDecl) bool {
	switch n := blockNode.(type) {
	case *ast.ExprStmt:
		return saveCalls(node, n.X, parsedBlock, parsedFuncDecl)
	case *ast.AssignStmt:
		found := false
		for _, rvalue := range n.Rhs {
			found = saveCalls(node, rvalue, parsedBlock, parsedFuncDecl)
		}
		return found
	case *ast.ParenExpr:
		return saveCalls(node, n.X, parsedBlock, parsedFuncDecl)
	case *ast.CallExpr:
		return saveCallIfValid(node, n, parsedBlock, parsedFuncDecl)
	case *ast.IncDecStmt:
		return saveCalls(node, n.X, parsedBlock, parsedFuncDecl)
	case *ast.CompositeLit:
		for _, elt := range n.Elts {
			saveCalls(node, elt, parsedBlock, parsedFuncDecl)
		}
	case *ast.KeyValueExpr:
		saveCalls(node, n.Key, parsedBlock, parsedFuncDecl)
		saveCalls(node, n.Value, parsedBlock, parsedFuncDecl)
	case *ast.DeferStmt:
		return saveCalls(node, n.Call.Fun, parsedBlock, parsedFuncDecl)
	case *ast.SelectorExpr:
		return saveCalls(node, n.X, parsedBlock, parsedFuncDecl)
	// ------------
	// Go Routines
	// ------------
	case *ast.GoStmt:
		stmts, found := getStmtsIfInlineGoRoutine(blockNode)
		if found {
			for _, stmt := range stmts {
				saveCalls(node, stmt, parsedBlock, parsedFuncDecl)
			}
		}
	// -------------------
	// Declaring Variables
	// ------------------
	case *ast.DeclStmt:
		for _, spec := range n.Decl.(*ast.GenDecl).Specs {
			saveCalls(node, spec, parsedBlock, parsedFuncDecl)
		}
	// ----------------------
	// Nodes with expressions
	// ----------------------
	case *ast.UnaryExpr: // e.g. <-forever
		saveCalls(node, n.X, parsedBlock, parsedFuncDecl)
	case *ast.BinaryExpr: // e.g. if err != nil
		saveCalls(node, n.X, parsedBlock, parsedFuncDecl)
		saveCalls(node, n.Y, parsedBlock, parsedFuncDecl)
	case *ast.ReturnStmt:
		for _, r := range n.Results {
			saveCalls(node, r, parsedBlock, parsedFuncDecl)
		}
	case *ast.ValueSpec:
		for _, v := range n.Values {
			saveCalls(node, v, parsedBlock, parsedFuncDecl)
		}
	// ---------
	// Remaining
	// ---------
	case *ast.Ident:
	case *ast.TypeAssertExpr:
	case *ast.BasicLit: // e.g. integers (1), strings ("foo"), etc
	case *ast.IfStmt:
	default:
		logger.Logger.Fatalf("unknown type in saveCalls for type %s: %v", utils.GetType(n), n)
	}

	return false
}

func hasCurrentServiceRecvIdent(selectorExpr *ast.SelectorExpr, expectedRecvIdent *ast.Ident) (bool, *ast.Ident) {
	if serviceRecvIdent, ok := selectorExpr.X.(*ast.Ident); ok {
		if serviceRecvIdent.Name == expectedRecvIdent.Name {
			return true, serviceRecvIdent
		}
	}
	return false, nil
}

func getFuncCallIfSelectedServiceField(node ast.Node, expectedRecvIdent *ast.Ident) (ok bool, funcCall *ast.CallExpr, methodIdent *ast.Ident, fieldIdent *ast.Ident, serviceRecvIdent *ast.Ident) {
	// e.g. f.queue.Push
	//    ^ident2 ^ident ^method
	// e.g. f.storageService.StorePost
	//      ^ident2  ^ident    ^method
	if funcCall, ok := node.(*ast.CallExpr); ok {
		if methodSel, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if fieldSel, ok := methodSel.X.(*ast.SelectorExpr); ok {
				if ok, serviceRecvIdent := hasCurrentServiceRecvIdent(fieldSel, expectedRecvIdent); ok {
					return true, funcCall, methodSel.Sel, fieldSel.Sel, serviceRecvIdent
				}
			} else if ok, serviceRecvIdent := hasCurrentServiceRecvIdent(methodSel, expectedRecvIdent); ok {
				return true, funcCall, methodSel.Sel, nil, serviceRecvIdent
			}
		}
	}
	return false, nil, nil, nil, nil
}

func saveFuncCallIfValid(node *service.ServiceNode, callExpr *ast.CallExpr, parsedFuncDecl *service.ParsedFuncDecl) service.Call {
	ok, funcCall, methodIdent, fieldIdent, serviceRecvIdent := getFuncCallIfSelectedServiceField(callExpr, parsedFuncDecl.Recv)
	if !ok {
		return nil
	}
	if fieldIdent != nil {
		// if the targeted variable corresponds to a service field
		if field, ok := node.Fields[fieldIdent.Name]; ok {
			// store function call either as service call or database call
			// if the field corresponds to a service field
			if serviceField, ok := field.(*types.ServiceField); ok {
				// 1. extract the service field from the current service
				// 2. get the target node service for the type
				// 3. add the targeted method of the other service for the current call expression
				targetServiceType := serviceField.GetTypeName()
				targetServiceNode := node.Services[targetServiceType]
				targetMethod := targetServiceNode.ExposedMethods[methodIdent.Name]
				svcParsedCallExpr := &service.ServiceParsedCallExpr{
					ParsedCallExpr: service.ParsedCallExpr{
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
				parsedFuncDecl.Calls = append(parsedFuncDecl.Calls, svcParsedCallExpr)
				logger.Logger.Warnf("[CFG] found new service call %s", svcParsedCallExpr.Name)
				return svcParsedCallExpr
			}
			// if the field corresponds to a database field
			if databaseField, ok := field.(*types.DatabaseField); ok {
				// 1. extract the service field from the current service
				// 2. get the target database node
				// 3. add the target method for the current call expression
				targetDatabaseType := databaseField.GetTypeName()
				dbParsedCallExpr := &service.DatabaseParsedCallExpr{
					ParsedCallExpr: service.ParsedCallExpr{
						Ast:         funcCall,
						Receiver:    serviceRecvIdent.Name,
						TargetField: fieldIdent.Name,
						Name:        methodIdent.Name,
						Pos:         funcCall.Pos(),
						Method:      frameworks.GetBackendMethod(fmt.Sprintf("%s.%s", targetDatabaseType, methodIdent.Name)),
					},
					CallerTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
					DbInstance:     databaseField.DbInstance,
				}
				parsedFuncDecl.Calls = append(parsedFuncDecl.Calls, dbParsedCallExpr)
				logger.Logger.Warnf("[CFG] found new database call %s", dbParsedCallExpr.Name)
				return dbParsedCallExpr
			}
		}
	} else if funcDecl, ok := node.InternalMethods[methodIdent.Name]; ok {
		internalCall := &service.InternalTempParsedCallExpr{
			ParsedCallExpr: service.ParsedCallExpr{
				Ast:      funcCall,
				Receiver: serviceRecvIdent.Name,
				Name:     methodIdent.Name,
				Method:   funcDecl,
				Pos:      funcCall.Pos(),
			},
			ServiceTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
		}
		parsedFuncDecl.Calls = append(parsedFuncDecl.Calls, internalCall)
		logger.Logger.Warnf("[CFG] found new internal call %s", internalCall.Name)
		return internalCall
	}
	return nil
}

func saveCallIfValid(serviceNode *service.ServiceNode, callExpr *ast.CallExpr, parsedBlock *types.ParsedBlock, parsedFuncDecl *service.ParsedFuncDecl) bool {
	parsedCall := saveFuncCallIfValid(serviceNode, callExpr, parsedFuncDecl)
	if parsedCall == nil {
		logger.Logger.Warnf("invalid call %s", callExpr.Fun)
		return false
	}
	for i, arg := range callExpr.Args {
		param := types.GetOrCreateVariable(serviceNode.File, parsedBlock.Vars, arg, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetVariableInfo().Type.(*types.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetVariableInfo().Type.String())
		}
		parsedCall.AddParam(param)
	}
	logger.Logger.Infof("[CFG] found call %s", parsedCall.String())
	return true
}
