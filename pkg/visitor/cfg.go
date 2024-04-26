package visitor

import (
	"fmt"
	"go/ast"
	"analyzer/pkg/logger"	
	"reflect"
	"slices"

	"analyzer/pkg/models"

	"golang.org/x/tools/go/cfg"
)

func VisitBasicBlockAssignments(parsedCfg *models.ParsedCFG) {
	log.Logger.Debug("visiting basic block assignments")
	var visited = make(map[int32]bool)
	for _, block := range parsedCfg.Cfg.Blocks {
		visitBasicBlockAssignments(parsedCfg, block, visited)
	}
	log.Logger.Debugln()
}

// visitBasicBlockAssignments goes through the
func visitBasicBlockAssignments(parsedCfg *models.ParsedCFG, block *cfg.Block, visited map[int32]bool) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	//log.Logger.Debug("+ in block", block, "with nodes", block.Nodes)

	for _, node := range block.Nodes {
		ok, lvalues, rvalues := isVarAssignment(node)
		if ok {
			for _, lvalue := range lvalues {
				var usedVars []*models.Variable
				for _, rvalue := range rvalues {
					for _, v := range parsedCfg.Vars {
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
				newVar := &models.Variable{
					//Id:     len(parsedCfg.Vars),
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
		//log.Logger.Debug("in child of block", block, ":", child)
		visitBasicBlockAssignments(parsedCfg, child, visited)
	}
	//log.Logger.Debug("- out block", block)
}

func VisitBasicBlockFuncCalls(parsedCfg *models.ParsedCFG, parsedFuncDecl *models.ParsedFuncDecl) {
	log.Logger.Debug("visiting basic block func calls")
	var visited = make(map[int32]bool)
	for _, block := range parsedCfg.Cfg.Blocks {
		visitBasicBlockFuncCalls(parsedCfg, block, parsedFuncDecl, visited)
	}
	log.Logger.Debugln()
}

func visitBasicBlockFuncCalls(parsedCfg *models.ParsedCFG, block *cfg.Block, parsedFuncDecl *models.ParsedFuncDecl, visited map[int32]bool) {
	if !visited[block.Index] {
		visited[block.Index] = true
	} else {
		return
	}
	//log.Logger.Debug("+ in block", block, "with nodes", block.Nodes)

	for _, node := range block.Nodes {
		hasFuncCall(parsedCfg, node, parsedFuncDecl)
	}

	for _, child := range block.Succs {
		//log.Logger.Debug("in child of block", block, ":", child)
		visitBasicBlockFuncCalls(parsedCfg, child, parsedFuncDecl, visited)
	}
	//log.Logger.Debug("- out block", block)
	//log.Logger.Debugln()
}

// hasFuncCall
// check if we found an ast node representing a database or service function call
//
// note that function calls can be embedded into:
//  1. ExprStmt 	 - simple function call
//  2. AssignStmt - assignment like errors from the return values of the function
//  3. ParenExpr  - e.g. when used as a bool value in an if statement (assumes it is inside a parentheses)
//     in this case, the unfolded node from ParenExpr is a CallExpr
func hasFuncCall(parsedCfg *models.ParsedCFG, node ast.Node, parsedFuncDecl *models.ParsedFuncDecl) bool {
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
		log.Logger.Warn("unknown node type for func call", nodeType)
	}

	return false
}

// hasServiceOrDatabaseCall
// 1. check if it is a database call or service call
// 2. if so, we fetch the arguments and compare against the CFG variables
func hasServiceOrDatabaseCall(parsedCfg *models.ParsedCFG, node *ast.CallExpr, parsedFuncDecl *models.ParsedFuncDecl) bool {
	log.Logger.Debug("found CallExpr:", node.Pos())
	var parsedCall *models.ParsedCallExpr
	// check if it is a database call
	dbCall := parsedFuncDecl.DatabaseCalls[node.Pos()]
	if dbCall != nil {
		parsedCall = dbCall
		log.Logger.Debug("- database call:", dbCall.MethodName)
	}
	// check if it is a service call
	svcCall := parsedFuncDecl.ServiceCalls[node.Pos()]
	if svcCall != nil {
		parsedCall = svcCall
		log.Logger.Debug("- service call:", svcCall.MethodName)
	}

	// if we have database or service call, then we keep track of all arguments used
	if parsedCall != nil {
		// gather all args used in the CallExpr
		var args []string
		for _, arg := range node.Args {
			//FIXME: CREATE HELPER FUNCTION TO COVER MORE CASES BESIDES SELECTOR
			// e.g. we can have multiple nested selectors: dummy.post.ReqID
			switch e := arg.(type) {
			case *ast.Ident:
				args = append(args, e.Name)

			// post.ReqID
			// ^ ident ^ selector
			case *ast.SelectorExpr:
				if ident, ok := e.X.(*ast.Ident); ok {
					name := fmt.Sprintf("%s.%s", ident.Name, e.Sel.Name)

					// now we have to get the actual dependency for ReqID with is postID
					// REMINDER: this actually takes into account if the variable is assigned again
					// because we are inside a block and we are using the last definition
					// before the current lineno
					for i := len(parsedCfg.Vars) - 1; i >= 0; i-- {
						v := parsedCfg.Vars[i]
						if ident.Name == v.Name {
							newInlineVariable := &models.Variable{
								Id:   -1,
								Name: name,
								Deps: []*models.Variable{v},
							}
							parsedCall.Deps = append(parsedCall.Deps, newInlineVariable)
							break
						}
					}
				}
			}

		}
		// for each arg, check if it is in the block variables array
		// if yes, then we add the arg to the dependencies of the parsed call
		// REMINDER: this is not necessary for e.g. SelectorExpr
		for _, arg := range args {
			log.Logger.Debugf("got arg '%s' for call '%s'", arg, parsedCall.MethodName)
			for _, v := range parsedCfg.Vars {
				if arg == v.Name {
					log.Logger.Debugf("add dep '%s':%d for call '%s'", v.Name, v.Lineno, parsedCall.MethodName)
					parsedCall.Deps = append(parsedCall.Deps, v)
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
		log.Logger.Debug("found AssignStmt:", assign.Pos())
		for _, lvalue := range assign.Lhs {
			if ident, ok := lvalue.(*ast.Ident); ok {
				lvalues = append(lvalues, ident.Name)
			}
		}
		for _, rvalue := range assign.Rhs {
			rvalues = append(rvalues, transverseAssignmentExpr(rvalue)...)
		}
		log.Logger.Debug("\t", lvalues, "->", rvalues)
		return true, lvalues, rvalues
	}
	return false, nil, nil
}

/* func transverseSelectorExpr(selectorExpr *ast.SelectorExpr) string {
	var repr string

	switch e := selectorExpr.X.(type) {
		case *ast.Ident:
			//log.Logger.Debug("- (ident) rvalue:", e.Name)
			repr = repr + "." + e
		case *ast.SelectorExpr:
			repr = repr + "." + transverseSelectorExpr(e.X)
		default:
			nodeType := reflect.TypeOf(e).Elem().Name()
			log.Logger.Warn("unknown rvalue selector", nodeType)
	}
	return repr
} */

func transverseAssignmentExpr(expr ast.Expr) []string {
	var identifiers []string

	switch e := expr.(type) {
	case *ast.Ident:
		//log.Logger.Debug("- (ident) rvalue:", e.Name)
		identifiers = append(identifiers, e.Name)
	case *ast.BasicLit:
		//log.Logger.Debug("- (basic) rvalue:", e.Value)
	case *ast.CallExpr:
		//log.Logger.Debug("- (call) rvalue: Function call")
		for _, arg := range e.Args {
			identifiers = append(identifiers, transverseAssignmentExpr(arg)...)
		}
	case *ast.CompositeLit:
		//log.Logger.Debug("- (struct) rvalue:")
		for _, elt := range e.Elts {
			if kv, ok := elt.(*ast.KeyValueExpr); ok {
				if _, ok := kv.Key.(*ast.Ident); ok {
					//log.Logger.Debug("    - field:", ident.Name)
					identifiers = append(identifiers, transverseAssignmentExpr(kv.Value)...)
				}
			}
		}
	case *ast.SelectorExpr:
		if ident, ok := e.X.(*ast.Ident); ok {
			identifiers = append(identifiers, ident.Name)
		}
	case *ast.BinaryExpr:
		//log.Logger.Debug("- (binary) rvalue:")
		identifiers = append(identifiers, transverseAssignmentExpr(e.X)...)
		identifiers = append(identifiers, transverseAssignmentExpr(e.Y)...)
	default:
		nodeType := reflect.TypeOf(e).Elem().Name()
		log.Logger.Warn("unknown rvalue for node type", nodeType)
	}
	return identifiers
}
