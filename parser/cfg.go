package parser

import (
	"go/ast"
	"reflect"
	"slices"

	"detection_tool/logger"

	"golang.org/x/tools/go/cfg"
)

var vars []*Variable

func GenParsedCfg(cfg *cfg.CFG, method *ParsedFuncDecl) *ParsedCFG {
	logger.Logger.Info("generating parsed config")
	parsedCfg := ParsedCFG{
		Cfg:        cfg,
		BlocksInfo: make([]*BlockInfo, 0, len(cfg.Blocks)),
	}
	for _, info := range parsedCfg.BlocksInfo {
		info.Gen = make([]*Variable, 0)
		info.In = make([]*Variable, 0)
		info.Out = make([]*Variable, 0)
	}

	vars = make([]*Variable, 0)
	pos := parsedCfg.Cfg.Blocks[0].Stmt.Pos()
	for _, param := range method.Params {
		vars = append(vars, &Variable{
			Lineno: pos,
			Name:   param,
		})
	}
	logger.Logger.Debug("Variables")
	for _, v := range vars {
		logger.Logger.Debugf("\t%s [%d], ", v.Name, v.Lineno)
	}
	return &parsedCfg

}

func VisitBasicBlockAssignments(parsedCfg *ParsedCFG) {
	logger.Logger.Info("visiting basic block assignments")
	var visited = make(map[int32]bool)
	for _, block := range parsedCfg.Cfg.Blocks {
		visitBasicBlockAssignments(block, visited)
	}
}

func visitBasicBlockAssignments(block *cfg.Block, visited map[int32]bool) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	//logger.Logger.Debug("+ in block", block, "with nodes", block.Nodes)

	for _, node := range block.Nodes {
		ok, lvalues, rvalues := isVarAssignment(node)
		if ok {
			for _, lvalue := range lvalues {
				var usedVars []*Variable
				for _, rvalue := range rvalues {
					for _, v := range vars {
						if rvalue == v.Name {
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
				newVar := &Variable{
					Lineno: node.Pos(),
					Name:   lvalue,
					Deps:   usedVars,
				}
				vars = append(vars, newVar)
			}
		}
	}

	for _, child := range block.Succs {
		//logger.Logger.Debug("in child of block", block, ":", child)
		visitBasicBlockAssignments(child, visited)
	}
	//logger.Logger.Debug("- out block", block)
}

func VisitBasicBlockFuncCalls(parsedCfg *ParsedCFG, parsedFuncDecl *ParsedFuncDecl) {
	logger.Logger.Info("visiting basic block func calls")
	var visited = make(map[int32]bool)
	for _, block := range parsedCfg.Cfg.Blocks {
		visitBasicBlockFuncCalls(block, parsedFuncDecl, visited)
	}
}

func visitBasicBlockFuncCalls(block *cfg.Block, parsedFuncDecl *ParsedFuncDecl, visited map[int32]bool) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	//logger.Logger.Debug("+ in block", block, "with nodes", block.Nodes)

	for _, node := range block.Nodes {
		hasFuncCall(node, parsedFuncDecl)
	}

	for _, child := range block.Succs {
		//logger.Logger.Debug("in child of block", block, ":", child)
		visitBasicBlockFuncCalls(child, parsedFuncDecl, visited)
	}
	//logger.Logger.Debug("- out block", block)
	//fmt.Println()
}

// hasFuncCall
// check if we found an ast node representing a database or service function call
//
// note that function calls can be embedded into:
// 1. ExprStmt 	 - simple function call
// 2. AssignStmt - assignment like errors from the return values of the function
// 3. ParenExpr  - e.g. when used as a bool value in an if statement (assumes it is inside a parentheses)
// 				   in this case, the unfolded node from ParenExpr is a CallExpr
func hasFuncCall(node ast.Node, parsedFuncDecl *ParsedFuncDecl) bool {
	switch n := node.(type) {
	case *ast.ExprStmt:
		if callExpr, ok := n.X.(*ast.CallExpr); ok {
			return hasServiceOrDatabaseCall(callExpr, parsedFuncDecl)
		}
	case *ast.AssignStmt:
		found := false
		for _, rvalue := range n.Rhs {
			if callExpr, ok := rvalue.(*ast.CallExpr); ok {
				if hasServiceOrDatabaseCall(callExpr, parsedFuncDecl) {
					found = true
				}
			}
		}
		return found
	case *ast.ParenExpr:
		return hasFuncCall(n.X, parsedFuncDecl)
	case *ast.CallExpr:
		return hasServiceOrDatabaseCall(n, parsedFuncDecl)
	case *ast.ReturnStmt:
		// nothing to do
		// ignore warning ahead
	case *ast.BinaryExpr: // e.g. if err != nil
		// nothing to do
		// ignore warning ahead
	default:
		nodeType := reflect.TypeOf(n).Elem().Name()
		logger.Logger.Warn("[WARNING] unknown node type for func call", nodeType)
	}
	

	return false
}

// hasServiceOrDatabaseCall
// 1. check if it is a database call or service call
// 2. if so, we fetch the arguments and compare against the CFG variables
func hasServiceOrDatabaseCall(node *ast.CallExpr, parsedFuncDecl *ParsedFuncDecl) bool {
	logger.Logger.Debug("found CallExpr:", node.Pos())
	var parsedCall *ParsedCallExpr
	// check if it is a database call
	dbCall := parsedFuncDecl.DatabaseCalls[node.Pos()]
	if dbCall != nil {
		parsedCall = dbCall
		logger.Logger.Debug("- database call:", dbCall.MethodName)
	}
	// check if it is a service call
	svcCall := parsedFuncDecl.ServiceCalls[node.Pos()]
	if svcCall != nil {
		parsedCall = svcCall
		logger.Logger.Debug("- service call:", svcCall.MethodName)
	}
	// if database or service call
	// we check if the variable is in the vars array
	// if yes, then we add the variable to the dependencies of the call
	var args []string
	for _, arg := range node.Args {
		if ident, ok := arg.(*ast.Ident); ok {
			args = append(args, ident.Name)
		}
	}
	if parsedCall != nil {
		for _, arg := range args {
			for _, v := range vars {
				if arg == v.Name {
					parsedCall.Deps = append(parsedCall.Deps, v)
					break
				}
			}
		}
		return true
	}
	// otherwise we return false because we did not find either
	// a database nor a service call
	return false
}

func isVarAssignment(node ast.Node) (bool, []string, []string) {
	var lvalues []string
	var rvalues []string
	if assign, ok := node.(*ast.AssignStmt); ok {
		logger.Logger.Debug("found AssignStmt:", assign.Pos())
		for _, lvalue := range assign.Lhs {
			if ident, ok := lvalue.(*ast.Ident); ok {
				lvalues = append(lvalues, ident.Name)
			}
		}
		for _, rvalue := range assign.Rhs {
			rvalues = append(rvalues, transverseAssignmentExpr(rvalue)...)
		}
		logger.Logger.Debug("\t", lvalues, "->", rvalues)
		return true, lvalues, rvalues
	}
	return false, nil, nil
}

func transverseAssignmentExpr(expr ast.Expr) []string {
	var identifiers []string

	switch e := expr.(type) {
	case *ast.Ident:
		//logger.Logger.Debug("- (ident) rvalue:", e.Name)
		identifiers = append(identifiers, e.Name)
	case *ast.BasicLit:
		//logger.Logger.Debug("- (basic) rvalue:", e.Value)
	case *ast.CallExpr:
		//logger.Logger.Debug("- (call) rvalue: Function call")
		for _, arg := range e.Args {
			identifiers = append(identifiers, transverseAssignmentExpr(arg)...)
		}
	case *ast.CompositeLit:
		//logger.Logger.Debug("- (struct) rvalue:")
		for _, elt := range e.Elts {
			if kv, ok := elt.(*ast.KeyValueExpr); ok {
				if _, ok := kv.Key.(*ast.Ident); ok {
					//logger.Logger.Debug("    - field:", ident.Name)
					identifiers = append(identifiers, transverseAssignmentExpr(kv.Value)...)
				}
			}
		}
	case *ast.SelectorExpr:
		if ident, ok := e.X.(*ast.Ident); ok {
			identifiers = append(identifiers, ident.Name)
		}
	case *ast.BinaryExpr:
		//logger.Logger.Debug("- (binary) rvalue:")
		identifiers = append(identifiers, transverseAssignmentExpr(e.X)...)
		identifiers = append(identifiers, transverseAssignmentExpr(e.Y)...)
	default:
		nodeType := reflect.TypeOf(e).Elem().Name()
		logger.Logger.Warn("[WARNING] unknown rvalue for node type", nodeType)
	}
	return identifiers
}
