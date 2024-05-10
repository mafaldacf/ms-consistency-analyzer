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
	"golang.org/x/tools/go/cfg"
)

func ParseServiceMethodCFG(parsedCfg *types.ParsedCFG, method *service.ParsedFuncDecl) {
	visitBasicBlockDeclAndAssigns(parsedCfg)
	visitBasicBlockFuncCalls(parsedCfg, method)
	visitCalls(method.DatabaseCalls)
	visitCalls(method.ServiceCalls)
}

func visitCalls(parsedCalls map[token.Pos]*service.ParsedCallExpr) {
	for pos, call := range parsedCalls {
		logger.Logger.Debugf("call %s.%s [%d]\n", call.TargetField, call.Name, pos)
		logger.Logger.Debug("> deps: ")
		for _, dep := range call.Params {
			r := visitDeps(dep)
			logger.Logger.Debugf("\t%s [%d], %s", dep.Name, dep.Lineno, r)
		}
	}
	logger.Logger.Debugln()
}

func visitDeps(v *types.Variable) string {
	s := ""
	for _, dep := range v.Deps {
		visitDeps(dep)
		return s + fmt.Sprintf("-> %s [%d] ", dep.Name, dep.Lineno)
	}
	return ""
}

func visitBasicBlockDeclAndAssigns(parsedCfg *types.ParsedCFG) {
	var visited = make(map[int32]bool)
	for _, block := range parsedCfg.Cfg.Blocks {
		visitBasicBlockDeclAndAssignsRecursor(parsedCfg, block, visited)
	}
	logger.Logger.Debugln()
}

func getStmtsIfGoRoutine(node ast.Node) []ast.Node {
	var stmts []ast.Node
	found := false
	if goStmt, ok := node.(*ast.GoStmt); ok {
		if funcLit, ok := goStmt.Call.Fun.(*ast.FuncLit); ok {
			for _, stmt := range funcLit.Body.List{
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

func visitBasicBlockDeclAndAssignsRecursor(parsedCfg *types.ParsedCFG, block *cfg.Block, visited map[int32]bool) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	for _, node := range block.Nodes {
		// if it is a go routine it will contain many stmts
		for _, stmt := range getStmtsIfGoRoutine(node) {
			ok, varType, lvalues, deps := isVarDeclOrAssign(stmt)
			if ok {
				for _, lvalue := range lvalues {
					var usedVars []*types.Variable
					for _, dep := range deps {
						for _, v := range parsedCfg.Vars {
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
					parsedCfg.Vars = append(parsedCfg.Vars, newVar)
				}
			}
		}
	}

	for _, child := range block.Succs {
		visitBasicBlockDeclAndAssignsRecursor(parsedCfg, child, visited)
	}
}

func visitBasicBlockFuncCalls(parsedCfg *types.ParsedCFG, parsedFuncDecl *service.ParsedFuncDecl) {
	var visited = make(map[int32]bool)
	for i, block := range parsedCfg.Cfg.Blocks {
		logger.Logger.Debugf("[CFG] visiting block #%d func calls for cfg %s", i, parsedCfg.FullMethod)
		visitBasicBlockFuncCallsRecursor(block, parsedCfg, parsedFuncDecl, visited)
	}
	logger.Logger.Debugln()
}

func visitBasicBlockFuncCallsRecursor(block *cfg.Block, parsedCfg *types.ParsedCFG, parsedFuncDecl *service.ParsedFuncDecl, visited map[int32]bool) {
	if visited[block.Index] {
		return
	}

	visited[block.Index] = true
	for _, node := range block.Nodes {
		processParsedCalls(node, parsedCfg, parsedFuncDecl)
	}
	for _, child := range block.Succs {
		visitBasicBlockFuncCallsRecursor(child, parsedCfg, parsedFuncDecl, visited)
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
func processParsedCalls(node ast.Node, parsedCfg *types.ParsedCFG, parsedFuncDecl *service.ParsedFuncDecl) bool {
	logger.Logger.Debugf("\t\tprocessing parsed calls for parsed cfg of %s (node type = %s)", parsedCfg.FullMethod, utils.GetType(node))
	switch n := node.(type) {
	case *ast.ExprStmt:
		return processParsedCalls(n.X, parsedCfg, parsedFuncDecl)
	case *ast.AssignStmt:
		found := false
		for _, rvalue := range n.Rhs {
			found = processParsedCalls(rvalue, parsedCfg, parsedFuncDecl)
		}
		return found
	case *ast.ParenExpr:
		return processParsedCalls(n.X, parsedCfg, parsedFuncDecl)
	case *ast.CallExpr:
		return findParsedCallsAndAddParams(n, parsedCfg, parsedFuncDecl)
	case *ast.IncDecStmt:
		return processParsedCalls(n.X, parsedCfg, parsedFuncDecl)
	case *ast.CompositeLit:
		for _, elt := range n.Elts{
			processParsedCalls(elt, parsedCfg, parsedFuncDecl)
		}
	case *ast.KeyValueExpr:
		processParsedCalls(n.Key, parsedCfg, parsedFuncDecl)
		processParsedCalls(n.Value, parsedCfg, parsedFuncDecl)
	case *ast.DeferStmt:
		return processParsedCalls(n.Call.Fun, parsedCfg, parsedFuncDecl)
	case *ast.SelectorExpr:
		return processParsedCalls(n.X, parsedCfg, parsedFuncDecl)
	// ------------
	// Go Routines
	// ------------
	case *ast.GoStmt:
		for _, stmt := range getStmtsIfGoRoutine(node) {
			processParsedCalls(stmt, parsedCfg, parsedFuncDecl)
		}
	// -------------------
	// Declaring Variables
	// ------------------
	case *ast.DeclStmt:
		for _, spec := range n.Decl.(*ast.GenDecl).Specs {
			processParsedCalls(spec, parsedCfg, parsedFuncDecl)
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
		logger.Logger.Warnf("unknown type in hasFuncCall: %s", utils.GetType(n))
	}

	return false
}

// hasServiceOrDatabaseCall
// 1. check if it is a database call or service call
// 2. if so, we fetch the arguments and compare against the CFG variables
func findParsedCallsAndAddParams(node *ast.CallExpr, parsedCfg *types.ParsedCFG, parsedFuncDecl *service.ParsedFuncDecl) bool {
	logger.Logger.Debugf("\t\t\t\t finding parsed calls and params for parsed cfg of %s", parsedCfg.FullMethod)
	var parsedCall *service.ParsedCallExpr
	// check if it is a database call
	dbCall := parsedFuncDecl.DatabaseCalls[node.Pos()]
	if dbCall != nil {
		parsedCall = dbCall
	}
	// check if it is a service call
	svcCall := parsedFuncDecl.ServiceCalls[node.Pos()]
	if svcCall != nil {
		parsedCall = svcCall
	}

	// if we have database or service call, then we keep track of all arguments used
	if parsedCall != nil {
		logger.Logger.Debugf("[VISITOR] finding parsed call %s: original args = %v", parsedCall.Name, node.Args)
		// gather all args used in the CallExpr
		for _, arg := range node.Args {
			var param *types.Variable

			//FIXME: CREATE HELPER FUNCTION TO COVER MORE CASES BESIDES SELECTOR
			// e.g. we can have multiple nested selectors: dummy.post.ReqID
			switch t := arg.(type) {
			case *ast.Ident:
				if ok, v := getVariableInBlock(parsedCfg, t.Name); ok {
					param = v
				}
				// e.g. &post
			case *ast.UnaryExpr:
				if ident, ok := t.X.(*ast.Ident); ok {
					name := fmt.Sprintf("&%s", ident.Name)
					if ok, v := getVariableInBlock(parsedCfg, ident.Name); ok {
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
					if ok, v := getVariableInBlock(parsedCfg, ident.Name); ok {
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
				parsedCall.Params = append(parsedCall.Params, param)
			}
		}
		logger.Logger.Debugf("[VISITOR] found parsed call %s: parsed params = %v", parsedCall.Name, parsedCall.Params)
		return true
	}
	// otherwise we return false because we did not find either
	// a database nor a service call
	return false
}

func getVariableInBlock(parsedCfg *types.ParsedCFG, name string) (bool, *types.Variable) {
	for i := len(parsedCfg.Vars) - 1; i >= 0; i-- {
		v := parsedCfg.Vars[i]
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
