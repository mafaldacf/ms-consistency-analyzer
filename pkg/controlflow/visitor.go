package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
	"go/ast"
	"go/token"
	"reflect"
	"slices"

	"analyzer/pkg/service"
	"analyzer/pkg/utils"

	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
	"golang.org/x/tools/go/cfg"
)

func VisitServiceMethodCFG(parsedCfg *types.ParsedCFG, method *service.ParsedFuncDecl) {
	VisitBasicBlockDeclAndAssigns(parsedCfg)
	VisitBasicBlockFuncCalls(parsedCfg, method)

	VisitCalls(method.DatabaseCalls)
	VisitCalls(method.ServiceCalls)
}

func VisitCalls(parsedCalls map[token.Pos]*service.ParsedCallExpr) {
	logger.Logger.Debug("visiting database/service calls for service node target method")
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

func VisitBasicBlockDeclAndAssigns(parsedCfg *types.ParsedCFG) {
	logger.Logger.Debug("visiting basic block assignments")
	var visited = make(map[int32]bool)
	for _, block := range parsedCfg.Cfg.Blocks {
		visitBasicBlockDeclAndAssigns(parsedCfg, block, visited)
	}
	logger.Logger.Debugln()
}

// visitBasicBlockDeclAndAssigns goes through the
func visitBasicBlockDeclAndAssigns(parsedCfg *types.ParsedCFG, block *cfg.Block, visited map[int32]bool) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	//logger.Logger.Debug("+ in block", block, "with nodes", block.Nodes)

	for _, node := range block.Nodes {
		ok, varType, lvalues, deps := isVarDeclOrAssign(node)
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
					Id:     -1,
					Lineno: node.Pos(),
					Name:   lvalue,
					Deps:   usedVars,
				}
				parsedCfg.Vars = append(parsedCfg.Vars, newVar)
			}
		}
	}

	for _, child := range block.Succs {
		//logger.Logger.Debug("in child of block", block, ":", child)
		visitBasicBlockDeclAndAssigns(parsedCfg, child, visited)
	}
	//logger.Logger.Debug("- out block", block)
}

func VisitBasicBlockFuncCalls(parsedCfg *types.ParsedCFG, parsedFuncDecl *service.ParsedFuncDecl) {
	logger.Logger.Debug("visiting basic block func calls")
	var visited = make(map[int32]bool)
	for _, block := range parsedCfg.Cfg.Blocks {
		visitBasicBlockFuncCalls(parsedCfg, block, parsedFuncDecl, visited)
	}
	logger.Logger.Debugln()
}

func visitBasicBlockFuncCalls(parsedCfg *types.ParsedCFG, block *cfg.Block, parsedFuncDecl *service.ParsedFuncDecl, visited map[int32]bool) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	//logger.Logger.Debug("+ in block", block, "with nodes", block.Nodes)

	for _, node := range block.Nodes {
		hasFuncCall(parsedCfg, node, parsedFuncDecl)
	}

	for _, child := range block.Succs {
		//logger.Logger.Debug("in child of block", block, ":", child)
		visitBasicBlockFuncCalls(parsedCfg, child, parsedFuncDecl, visited)
	}
	//logger.Logger.Debug("- out block", block)
	//logger.Logger.Debugln()
}

// hasFuncCall
// check if we found an ast node representing a database or service function call
//
// note that function calls can be embedded into:
//  1. ExprStmt 	 - simple function call
//  2. AssignStmt - assignment like errors from the return values of the function
//  3. ParenExpr  - e.g. when used as a bool value in an if statement (assumes it is inside a parentheses)
//     in this case, the unfolded node from ParenExpr is a CallExpr
func hasFuncCall(parsedCfg *types.ParsedCFG, node ast.Node, parsedFuncDecl *service.ParsedFuncDecl) bool {
	switch n := node.(type) {
	case *ast.ExprStmt:
		if callExpr, ok := n.X.(*ast.CallExpr); ok {
			return hasServiceOrDatabaseCall(parsedCfg, callExpr, parsedFuncDecl)
		}
	case *ast.AssignStmt:
		found := false
		for _, rvalue := range n.Rhs {
			if callExpr, ok := rvalue.(*ast.CallExpr); ok {
				if hasServiceOrDatabaseCall(parsedCfg, callExpr, parsedFuncDecl) {
					found = true
				}
			}
		}
		return found
	case *ast.ParenExpr:
		return hasFuncCall(parsedCfg, n.X, parsedFuncDecl)
	case *ast.CallExpr:
		return hasServiceOrDatabaseCall(parsedCfg, n, parsedFuncDecl)
	case *ast.ReturnStmt:
		// nothing to do
		// ignore warning ahead
	case *ast.BinaryExpr: // e.g. if err != nil
		// nothing to do
		// ignore warning ahead
	default:
		nodeType := reflect.TypeOf(n).Elem().Name()
		logger.Logger.Warnf("unknown type in hasFuncCall: %s", nodeType)
	}

	return false
}

// hasServiceOrDatabaseCall
// 1. check if it is a database call or service call
// 2. if so, we fetch the arguments and compare against the CFG variables
func hasServiceOrDatabaseCall(parsedCfg *types.ParsedCFG, node *ast.CallExpr, parsedFuncDecl *service.ParsedFuncDecl) bool {
	logger.Logger.Debug("found CallExpr:", node.Pos())
	var parsedCall *service.ParsedCallExpr
	// check if it is a database call
	dbCall := parsedFuncDecl.DatabaseCalls[node.Pos()]
	if dbCall != nil {
		parsedCall = dbCall
		logger.Logger.Debug("- database call:", dbCall.Name)
	}
	// check if it is a service call
	svcCall := parsedFuncDecl.ServiceCalls[node.Pos()]
	if svcCall != nil {
		parsedCall = svcCall
		logger.Logger.Debug("- service call:", svcCall.Name)
	}

	// if we have database or service call, then we keep track of all arguments used
	if parsedCall != nil {
		logger.Logger.Warnf("[VISITOR] found parsed call %s", parsedCall.Name)
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
							Id:   -1, // inline
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
							Id:   -1, // inline
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
	switch t := node.(type) {
	case *ast.ValueSpec:
		logger.Logger.Debugf("found ValueSpec: %d", t.Pos())
		for _, name := range t.Names {
			lvalues = append(lvalues, name.Name)
		}
		if ident, ok := t.Type.(*ast.Ident); ok {
			varType = ident.Name
		}
		return true, varType, lvalues, rvalues
	case *ast.AssignStmt:
		logger.Logger.Debugf("found AssignStmt: %d", t.Pos())
		for _, lvalue := range t.Lhs {
			if ident, ok := lvalue.(*ast.Ident); ok {
				lvalues = append(lvalues, ident.Name)
			}
		}
		for _, rvalue := range t.Rhs {
			var deps []string
			varType, deps = utils.TransverseExprIdentifiers(rvalue)
			rvalues = append(rvalues, deps...)
		}
		logger.Logger.Debugf("\t %v --- (depends on) ---> %v", lvalues, rvalues)
		return true, varType, lvalues, rvalues
	}
	return false, varType, nil, nil
}
