package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
	"go/ast"
	"go/token"
	"slices"

	"analyzer/pkg/service"
	"analyzer/pkg/utils"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
)

func ParseServiceMethodCFG(method *service.ParsedFuncDecl) {
	visitBasicBlockDeclAndAssigns(method)
	visitBasicBlockFuncCalls(method)
}

func visitBasicBlockDeclAndAssigns(method *service.ParsedFuncDecl) {
	var visited = make(map[int32]bool)
	for _, parsedBlock := range method.ParsedCfg.GetParsedBlocks() {
		visitBasicBlockDeclAndAssignsRecursor(method.ParsedCfg, parsedBlock, visited)
	}
	logger.Logger.Debugln()
}

func getStmtsIfGoRoutine(node ast.Node) []ast.Node {
	var stmts []ast.Node
	found := false
	if goStmt, ok := node.(*ast.GoStmt); ok {
		if funcLit, ok := goStmt.Call.Fun.(*ast.FuncLit); ok {
			for _, stmt := range funcLit.Body.List {
				stmts = append(stmts, stmt)
				found = true
			}
		}
	}
	if !found {
		stmts = append(stmts, node)
	}
	return stmts
}

func visitBasicBlockDeclAndAssignsRecursor(parsedCfg *types.ParsedCFG, parsedBlock *types.ParsedBlock, visited map[int32]bool) {
	if !visited[parsedBlock.GetIndex()] {
		visited[parsedBlock.GetIndex()] = true
	} else {
		return
	}
	for _, node := range parsedBlock.GetNodes() {
		// if it is a go routine it will contain many stmts
		for _, stmt := range getStmtsIfGoRoutine(node) {
			ok, varType, lvalues, deps := isVarDeclOrAssign(stmt)
			if ok {
				for _, lvalue := range lvalues {
					var usedVars []*types.Variable
					for _, dep := range deps {
						for _, v := range parsedBlock.GetVariables() {
							if dep == v.Name {
								// remove duplicates e.g.
								// message := Message{
								//	ReqID:     Int64ToString(post.ReqID),
								//	PostID:    Int64ToString(post.PostID),
								//}
								// uses twice the variable 'post'
								if !slices.Contains(usedVars, v) {
									usedVars = append(usedVars, v)
								}
								break
							}
						}
					}
					newVar := &types.Variable{
						Type: &gocode.UserType{
							Package: parsedCfg.Package,
							Name:    varType, //FIXME, this needs to be type not name
						},
						Id:     types.VARIABLE_UNASSIGNED_ID,
						Lineno: stmt.Pos(),
						Name:   lvalue,
						Deps:   usedVars,
					}
					parsedBlock.AddVariable(newVar)
				}
			}
		}
	}

	for _, child := range parsedBlock.GetSuccs() {
		visitBasicBlockDeclAndAssignsRecursor(parsedCfg, parsedCfg.GetParsedBlockAtIndex(child.Index), visited)
	}
}

func visitBasicBlockFuncCalls(parsedFuncDecl *service.ParsedFuncDecl) {
	var visited = make(map[int32]bool)
	for i, parsedBlock := range parsedFuncDecl.ParsedCfg.ParsedBlocks {
		logger.Logger.Debugf("[CFG] visiting block #%d func calls for cfg %s", i, parsedFuncDecl.ParsedCfg.FullMethod)
		visitBasicBlockFuncCallsRecursor(parsedBlock, parsedFuncDecl, visited)
	}
	logger.Logger.Debugln()
}

func visitBasicBlockFuncCallsRecursor(parsedBlock *types.ParsedBlock, parsedFuncDecl *service.ParsedFuncDecl, visited map[int32]bool) {
	if visited[parsedBlock.GetIndex()] {
		return
	}
	visited[parsedBlock.GetIndex()] = true
	for _, node := range parsedBlock.GetNodes() {
		findCallsInBlock(node, parsedBlock, parsedFuncDecl)
	}
	for _, block := range parsedBlock.GetSuccs() {
		visitBasicBlockFuncCallsRecursor(parsedFuncDecl.ParsedCfg.GetParsedBlockAtIndex(block.Index), parsedFuncDecl, visited)
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
func findCallsInBlock(node ast.Node, parsedBlock *types.ParsedBlock, parsedFuncDecl *service.ParsedFuncDecl) bool {
	logger.Logger.Debugf("\t\tfinding calls for block %s (node type = %s)", parsedBlock, utils.GetType(node))
	switch n := node.(type) {
	case *ast.ExprStmt:
		return findCallsInBlock(n.X, parsedBlock, parsedFuncDecl)
	case *ast.AssignStmt:
		found := false
		for _, rvalue := range n.Rhs {
			found = findCallsInBlock(rvalue, parsedBlock, parsedFuncDecl)
		}
		return found
	case *ast.ParenExpr:
		return findCallsInBlock(n.X, parsedBlock, parsedFuncDecl)
	case *ast.CallExpr:
		return validateCallAndAddParams(n, parsedBlock, parsedFuncDecl)
	case *ast.IncDecStmt:
		return findCallsInBlock(n.X, parsedBlock, parsedFuncDecl)
	case *ast.CompositeLit:
		for _, elt := range n.Elts {
			findCallsInBlock(elt, parsedBlock, parsedFuncDecl)
		}
	case *ast.KeyValueExpr:
		findCallsInBlock(n.Key, parsedBlock, parsedFuncDecl)
		findCallsInBlock(n.Value, parsedBlock, parsedFuncDecl)
	case *ast.DeferStmt:
		return findCallsInBlock(n.Call.Fun, parsedBlock, parsedFuncDecl)
	case *ast.SelectorExpr:
		return findCallsInBlock(n.X, parsedBlock, parsedFuncDecl)
	// ------------
	// Go Routines
	// ------------
	case *ast.GoStmt:
		for _, stmt := range getStmtsIfGoRoutine(node) {
			findCallsInBlock(stmt, parsedBlock, parsedFuncDecl)
		}
	// -------------------
	// Declaring Variables
	// ------------------
	case *ast.DeclStmt:
		for _, spec := range n.Decl.(*ast.GenDecl).Specs {
			findCallsInBlock(spec, parsedBlock, parsedFuncDecl)
		}
	// ------
	// Others
	// ------
	case *ast.ValueSpec:
	case *ast.ReturnStmt:
	case *ast.BinaryExpr: // e.g. if err != nil
	case *ast.Ident:
	case *ast.TypeAssertExpr:
	default:
		logger.Logger.Warnf("unknown type in findCallsInBlock: %s", utils.GetType(n))
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

func validateCallAndAddParams(node *ast.CallExpr, parsedBlock *types.ParsedBlock, parsedFuncDecl *service.ParsedFuncDecl) bool {
	parsedCall, ok := getParsedCallAtPosition(parsedFuncDecl, node.Pos())
	if !ok {
		return false
	}

	logger.Logger.Debugf("[VISITOR] (1) finding parsed call %s with args %v", parsedCall.GetName(), node.Args)
	// gather all args used in the CallExpr
	for _, arg := range node.Args {
		var param *types.Variable

		//FIXME: CREATE HELPER FUNCTION TO COVER MORE CASES BESIDES SELECTOR
		// e.g. we can have multiple nested selectors: dummy.post.ReqID
		switch t := arg.(type) {
		case *ast.Ident:
			if ok, v := getVariableInBlock(parsedBlock, t.Name); ok {
				param = v
			}
			// e.g. &post
		case *ast.UnaryExpr:
			if ident, ok := t.X.(*ast.Ident); ok {
				name := fmt.Sprintf("&%s", ident.Name)
				if ok, v := getVariableInBlock(parsedBlock, ident.Name); ok {
					param = &types.Variable{
						Type: &gocode.Pointer{
							PointerTo: v.Type,
						},
						Id:   types.VARIABLE_INLINE_ID,
						Name: name,
						Deps: []*types.Variable{v},
					}
				}
			}
			// FIXTHIS: can have mannyyyyyyyyyyyyyyy types!! maybe we need a recursive function here

		// e.g. post.ReqID
		//       ^ ident ^ selector
		case *ast.SelectorExpr:
			if ident, ok := t.X.(*ast.Ident); ok {
				name := fmt.Sprintf("%s.%s", ident.Name, t.Sel.Name)
				if ok, v := getVariableInBlock(parsedBlock, ident.Name); ok {
					param = &types.Variable{
						Type: v.Type,
						Id:   types.VARIABLE_INLINE_ID, // inline
						Name: name,
						Deps: []*types.Variable{v},
					}
				}
			}
		}
		if param != nil {
			parsedCall.AddParam(param)
		}
	}
	logger.Logger.Debugf("[VISITOR] (2) found parsed call %s with parsed params = %v", parsedCall.GetName(), parsedCall.GetParams())
	return true
}

func getVariableInBlock(parsedBlock *types.ParsedBlock, name string) (bool, *types.Variable) {
	for i := len(parsedBlock.Vars) - 1; i >= 0; i-- {
		v := parsedBlock.Vars[i]
		if name == v.Name {
			return true, v
		}
	}
	return false, nil
}

func isVarDeclOrAssign(node ast.Node) (bool, string, []string, []string) {
	var lvalues []string
	var rvalues []string
	var varType string
	var found bool
	switch n := node.(type) {
	case *ast.ValueSpec:
		for _, name := range n.Names {
			lvalues = append(lvalues, name.Name)
		}
		if ident, ok := n.Type.(*ast.Ident); ok {
			varType = ident.Name
		}
		found = true
	case *ast.AssignStmt:
		for _, lvalue := range n.Lhs {
			if ident, ok := lvalue.(*ast.Ident); ok {
				lvalues = append(lvalues, ident.Name)
			}
		}
		for _, rvalue := range n.Rhs {
			var deps []string
			varType, deps = utils.TransverseExprIdentifiers(rvalue)
			rvalues = append(rvalues, deps...)
		}
		found = true
	case *ast.DeclStmt:
		for _, spec := range n.Decl.(*ast.GenDecl).Specs {
			f, vt, lvs, rvs := isVarDeclOrAssign(spec)
			if f {
				found = true
			}
			varType = vt
			lvalues = append(lvalues, lvs...)
			rvalues = append(rvalues, rvs...)
		}
	case *ast.ExprStmt: // ignore expressions from function calls
	case *ast.ReturnStmt: // ignore return statements
	case *ast.BinaryExpr: // ignore e.g. if err != nil

	default:
		logger.Logger.Warnf("unknown type in isVarDeclOrAssign %s", utils.GetType(node))
	}
	return found, varType, lvalues, rvalues
}
