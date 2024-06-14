package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"go/ast"
	"go/token"

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

func getParsedCallAtPosition(parsedFuncDecl *service.ParsedFuncDecl, pos token.Pos) (service.Call, bool) {
	for _, call := range parsedFuncDecl.Calls {
		if call.IsAtPos(pos) {
			return call, true
		}
	}
	return nil, false
}

func saveCallIfValid(serviceNode *service.ServiceNode, node *ast.CallExpr, parsedBlock *types.ParsedBlock, parsedFuncDecl *service.ParsedFuncDecl) bool {
	parsedCall, ok := getParsedCallAtPosition(parsedFuncDecl, node.Pos())
	if !ok {
		return false
	}
	for i, arg := range node.Args {
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
