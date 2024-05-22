package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
	"go/ast"
	"go/token"
	"slices"
	"strings"

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
				saveDeclsAndAssigns(parsedFuncDecl.ParsedCfg, parsedBlock, stmt)
			}
		} else {
			saveDeclsAndAssigns(parsedFuncDecl.ParsedCfg, parsedBlock, blockNode)
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

func saveDeclsAndAssigns(parsedCfg *types.ParsedCFG, parsedBlock *types.ParsedBlock, node ast.Node) {
	ok, varType, lvalues, deps := isVarDeclOrAssign(node)
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
				Type: &types.User{
					Package: parsedCfg.Package,
					Name:    varType, //FIXME, this needs to be type not name
				},
				Id:   types.VARIABLE_UNASSIGNED_ID,
				Name: lvalue,
				Deps: usedVars,
			}
			parsedBlock.AddVariable(newVar)
		}
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
		return saveCallIfValid(n, parsedBlock, parsedFuncDecl)
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
		logger.Logger.Warnf("FOUND GO STMT in saveCalls: %v", n.Call)
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
	default:
		logger.Logger.Warnf("unknown type in saveCalls: %s", utils.GetType(n))
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

func saveCallIfValid(node *ast.CallExpr, parsedBlock *types.ParsedBlock, parsedFuncDecl *service.ParsedFuncDecl) bool {
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
						Type: &types.Pointer{
							PointerTo: v.Type,
						},
						Id:   types.VARIABLE_INLINE_ID,
						Name: name,
						Deps: []*types.Variable{v},
					}
				}
			}
		case *ast.BasicLit:
			param = &types.Variable{
				Type: &types.Basic{
					Name: "string",
				},
				Id:   types.VARIABLE_INLINE_ID,
				Name: strings.Trim(t.Value, "\""),
			}

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
		default:
			logger.Logger.Warnf("unknown type in saveCallIfValid %s", utils.GetType(t))
		}

		if param != nil {
			parsedCall.AddParam(param)
		}
	}
	logger.Logger.Infof("[CFG] found call %s", parsedCall.String())
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
