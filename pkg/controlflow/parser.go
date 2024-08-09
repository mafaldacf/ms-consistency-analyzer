package controlflow

import (
	"fmt"
	"go/ast"
	"go/token"
	golangtypes "go/types"

	"golang.org/x/tools/go/cfg"

	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/lookup"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

func ParseServiceMethodCFG(service *service.Service, method *types.ParsedMethod) {
	if method.IsParsed() {
		logger.Logger.Warnf("[CFG] [%s] ignoring parsing for already parsed method: %s", service.GetName(), method.String())
		return
	}
	method.SetParsed()

	var blocksStr string
	for _, block := range method.ParsedCfg.GetParsedBlocks() {
		blocksStr += "\t\t\t\t\t - " + block.AstInfoString() + "\n"
	}

	logger.Logger.Debugf("[CFG] [%s] parsing service method cfg for (%s):\n%s", service.GetName(), method.String(), blocksStr)

	entryBlock := method.ParsedCfg.GetEntryParsedBlock()
	visitBasicBlock(service, method, entryBlock)

	/* if method.GetName() == "Run" {
		logger.Logger.Fatal("EXIT!")
	} */
}

func visitBasicBlock(service *service.Service, method *types.ParsedMethod, block *types.Block) {
	if block.Visited {
		return
	}

	switch block.Block.Stmt.(type) {
	case *ast.BlockStmt:
		logger.Logger.Infof("\n--------------------------------------------------------------------------------------------\nVISITING BlockStmt: %s \n--------------------------------------------------------------------------------------------", block.String())
	case *ast.ForStmt:
		logger.Logger.Infof("\n--------------------------------------------------------------------------------------------\nVISITING ForStmt: %s \n--------------------------------------------------------------------------------------------", block.String())
	case *ast.ReturnStmt:
		logger.Logger.Infof("\n--------------------------------------------------------------------------------------------\nVISITING ReturnStmt: %s \n--------------------------------------------------------------------------------------------", block.String())
	default:
		logger.Logger.Infof("\n--------------------------------------------------------------------------------------------\nVISITING UNKNOWN (%s) BLOCK: %s \n--------------------------------------------------------------------------------------------", utils.GetType(block.Block.Stmt), block.String())

	}

	var deferStmts []*ast.DeferStmt
	block.Visited = true
	for i, blockNode := range block.GetNodes() { //FIXME????
		if block.Block.Kind == cfg.KindBody && i == len(block.GetNodes())-1 {
			for _, succ := range block.GetSuccs() {
				// skip last node if we have successors for (i) if branches
				// in these cases, the last node usually corresponds to the conditional expression
				// do not skip for forloops since this is the only way to capture the initial declaration (e.g. for i := 0)
				if succ.Kind == cfg.KindIfThen {
					break
				}
			}
		}

		logger.Logger.Warnf("\n\n----------------------------------------------\nPARSING BLOCK [%d] NODE [%d]: %v \n----------------------------------------------", block.Block.Index, i, blockNode)
		deferStmts = append(deferStmts, parseNode(service, method, block, blockNode)...)
	}

	for _, deferStmt := range deferStmts {
		parseAndSaveCall(service, method, block, deferStmt.Call)
	}

	if block.Block.Kind == cfg.KindForPost { // FIXME: skip going again for loop
		return
	}

	for _, succ := range block.GetSuccs() {
		parsedSucc := method.ParsedCfg.GetParsedBlockAtIndex(succ.Index)
		parsedSucc.AppendVarsFromPredecessor(block)
		parsedSucc.AppendInlineFuncsFromPredecessor(block)
		logger.Logger.Debugf("\n\n----------------------------------------------\nFOUND BLOCK SUCC [%d -> %d]: %s \n----------------------------------------------", block.Block.Index, parsedSucc.Block.Index, parsedSucc.String())

		visitBasicBlock(service, method, parsedSucc)
	}
}

func getAssignmentRightVariables(service *service.Service, method *types.ParsedMethod, block *types.Block, rightExprs []ast.Expr) []variables.Variable {
	var rvariables []variables.Variable
	for _, rvalue := range rightExprs {
		variable, _ := lookupVariableFromAstExpr(service, method, block, rvalue, nil, true)
		if tupleVariable, ok := variable.(*variables.TupleVariable); ok {
			rvariables = append(rvariables, tupleVariable.Variables...)
		} else {
			rvariables = append(rvariables, variable)
		}
	}
	return rvariables
}

func declareLeftIdents(service *service.Service, block *types.Block, leftIdents []*ast.Ident, t ast.Expr) {
	for _, ident := range leftIdents {
		t := lookup.ComputeTypeForAstExpr(service.File, t)
		declaredVariable := lookup.CreateVariableFromType(ident.Name, t)
		logger.Logger.Warnf("[CFG - PARSE EXPR] VARIABLE IS DECLARED: %s", declaredVariable.String())
		block.AddVariable(declaredVariable)
	}
}

func assignLeftIdents(service *service.Service, method *types.ParsedMethod, block *types.Block, leftIdents []*ast.Ident, rightExprs []ast.Expr) {
	rvariables := getAssignmentRightVariables(service, method, block, rightExprs)
	for i, rvariable := range rvariables {
		leftIdent := leftIdents[i]
		rvariable.GetVariableInfo().SetUnassigned()
		rvariable.GetVariableInfo().SetName(leftIdent.Name)
		block.AddVariable(rvariable)
	}
}

func incDecLeftValues(service *service.Service, method *types.ParsedMethod, block *types.Block, leftExpr ast.Expr, tok token.Token) {
	lvariable, _ := lookupVariableFromAstExpr(service, method, block, leftExpr, nil, true)
	switch tok {
	case token.INC:
		lvariable.GetType().AddValue("1")
	case token.DEC:
		lvariable.GetType().AddValue("-1")
	default:
		logger.Logger.Fatalf("[CFG - INC/DEC LEFT] unknown token: %s", tok.String())
	}
}

func assignLeftValues(service *service.Service, method *types.ParsedMethod, block *types.Block, assignStmt *ast.AssignStmt) {
	logger.Logger.Debugf("[CFG - ASSIGN LEFT] [%s] visiting stmt (%s): %v", service.GetName(), utils.GetType(assignStmt), assignStmt)
	rvariables := getAssignmentRightVariables(service, method, block, assignStmt.Rhs)
	for i, rvariable := range rvariables {
		lvalue := assignStmt.Lhs[i]
		logger.Logger.Debugf("[CFG - ASSIGN LEFT] [%s] assigning left values: \n\t\t\t\t\t\t - (lvalue) (%s) %v \n\t\t\t\t\t\t - (rvalue) (%s) %s", service.GetName(), utils.GetType(lvalue), lvalue, variables.VariableTypeName(rvariable), rvariable.LongString())
		switch e := lvalue.(type) {
		case *ast.Ident:
			if assignStmt.Tok == token.DEFINE || assignStmt.Tok == token.ASSIGN { // := OR =
				if rvariable.GetVariableInfo().GetName() == "" { // defining for the first time (token.DEFINE)
					rvariable.GetVariableInfo().SetUnassigned()
					rvariable.GetVariableInfo().SetName(e.Name)
					block.AddVariable(rvariable)
				} else { // already exists (token.ASSIGN)
					logger.Logger.Warnf("[CFG - ASSIGN LEFT] FIX ME!!!! WE SHOULD SEARCH FOR THE LEFT VARIABLE THAT ALREADY EXISTS IN THE BLOCK")
					lvariable := rvariable.Copy(true)
					lvariable.GetVariableInfo().SetName(e.Name)
					lvariable.GetVariableInfo().SetUnassigned()
					block.AddVariable(lvariable)
					if e.Name == "workerMessage" {
						logger.Logger.Fatal("[CFG - ASSIGN LEFT] 2 HERE!")
					}
				}
				if funcVar, ok := rvariable.(*variables.FuncVariable); ok {
					funcVar.GetFuncType().Name = e.Name
					parseInlineFuncDeclaration(block, funcVar.GetFuncType().Body, e.Name)
				}
			} else if assignStmt.Tok == token.ADD_ASSIGN { // +=
				lvariable := block.GetLastestVariable(e.Name)
				lvariable.GetType().AddValue(rvariable.GetType().GetBasicValue())
			} else {
				logger.Logger.Fatalf("[CFG - ASSIGN LEFT] [%s] unexpected token (%v) for assignment: %v", service.GetName(), assignStmt.Tok, assignStmt)
			}
		case *ast.SelectorExpr:
			lvariable, _ := lookupVariableFromAstExpr(service, method, block, e, nil, true)
			switch ee := lvariable.(type) {
			case *variables.FieldVariable:
				lvariable.AssignVariable(rvariable)
			default:
				logger.Logger.Fatalf("[CFG - ASSIGN LEFT] [%s] unsupported left variable type (%s): %v", service.GetName(), utils.GetType(ee), lvariable.String())
			}
		case *ast.IndexExpr: // e.g. res[rt] = pc
			lvariable, _ := lookupVariableFromAstExpr(service, method, block, e.X, nil, true)
			switch ee := lvariable.(type) {
			case *variables.MapVariable:
				idxVariable, _ := lookupVariableFromAstExpr(service, method, block, e.Index, nil, true)
				ee.AddKeyValue(idxVariable, rvariable)
			default:
				logger.Logger.Fatalf("[CFG - ASSIGN LEFT] [%s] unsupported left variable type (%s): %v", service.GetName(), utils.GetType(ee), lvariable.String())
			}
		default:
			logger.Logger.Fatalf("[CFG - ASSIGN LEFT] [%s] unexpected type (%s) for left value (%v) in assignment with token (%v): %v", method.Name, utils.GetType(lvalue), lvalue, assignStmt.Tok, assignStmt)
		}
	}
}

func parseInlineFuncDeclaration(block *types.Block, body *ast.BlockStmt, name string) *types.CFG {
	inlineCFG := GenerateInlineFuncCFG(body, name)
	if name != "" { // if empty then it is an anonymous function
		block.AddInlineFunc(name, inlineCFG)
	}
	return inlineCFG
}

func parseInlineFuncCall(service *service.Service, method *types.ParsedMethod, block *types.Block, inlineCFG *types.CFG, params *ast.FieldList, args []ast.Expr) []variables.Variable {
	entryBlock := inlineCFG.GetEntryParsedBlock()
	entryBlock.AppendVarsFromPredecessor(block)
	entryBlock.AppendInlineFuncsFromPredecessor(block)

	var variables []variables.Variable
	for i, arg := range args {
		v, _ := lookupVariableFromAstExpr(service, method, block, arg, nil, true)
		v = v.DeepCopy()
		v.GetVariableInfo().SetName(params.List[i].Names[0].Name)
		variables = append(variables, v)
	}
	entryBlock.AddVariables(variables)

	var blocksStr string
	for _, block := range inlineCFG.GetParsedBlocks() {
		blocksStr += "\t\t\t\t\t - " + block.AstInfoString() + "\n"
	}

	visitBasicBlock(service, method, entryBlock)
	return entryBlock.Results

	//logger.Logger.Fatalf("[CFG] [%s] parsing service method cfg for (%s):\n%s", service.GetName(), method.String(), blocksStr)
}

func parseNode(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) []*ast.DeferStmt {
	var deferStmts []*ast.DeferStmt
	logger.Logger.Debugf("[CFG - PARSE EXPR] (%s) visiting node (%v)", utils.GetType(node), node)
	switch e := node.(type) {
	// ------------
	// Go Routines
	// ------------
	case *ast.GoStmt:
		if funcLit, ok := e.Call.Fun.(*ast.FuncLit); ok {
			cfg := parseInlineFuncDeclaration(block, funcLit.Body, "")
			parseInlineFuncCall(service, method, block, cfg, funcLit.Type.Params, e.Call.Args)
		} else { // e.g. we can have a previous assignment to a variable function and then call it here
			parseAndSaveCall(service, method, block, e.Call)
		}
	// ----------------------------
	// Declarations and Assignments
	// ----------------------------
	case *ast.DeclStmt: // e.g. foobar := "foobar"
		for _, spec := range e.Decl.(*ast.GenDecl).Specs {
			parseNode(service, method, block, spec)
		}
	case *ast.ValueSpec: // e.g. var foobar OR var foobar = "foobar"
		logger.Logger.Warnf("[CFG - PARSE EXPR] parsing value spec with names = (%v) and values = (%v)", e.Names, e.Values)
		if len(e.Values) > 0 { // variables are being declared and assigned
			assignLeftIdents(service, method, block, e.Names, e.Values)
		} else { // variables are being declared with types
			declareLeftIdents(service, block, e.Names, e.Type)
		}
	case *ast.AssignStmt: // e.g. for i := 0
		assignLeftValues(service, method, block, e)
	// -----------------------------------
	// Calls and Parenthesized Expressions
	// -----------------------------------
	case *ast.CallExpr:
		// a call expr can also happen upon a structure assignment
		// e.g. post := Post { ... }
		parseAndSaveCall(service, method, block, e)
	case *ast.ParenExpr:
		// e.g. when used as a bool value in an if statement (assumes it is inside a parentheses)
		// in this case, the unfolded service from ParenExpr is a CallExpr
		parseNode(service, method, block, e.X)
	// -----------------
	// Other Expressions
	// -----------------
	case *ast.ExprStmt:
		parseNode(service, method, block, e.X)
	case *ast.UnaryExpr: // e.g. <-forever
		logger.Logger.Warnf("[CFG - PARSE EXPR] [%s.%s] ignoring %s: %s", service.GetName(), method.GetName(), utils.GetType(node), node)
	// -------
	// Returns
	// -------
	case *ast.ReturnStmt:
		for _, resultExpr := range e.Results {
			v, _ := lookupVariableFromAstExpr(service, method, block, resultExpr, nil, false)
			block.AddResult(v)
		}
	// -------------
	// If Statements
	// -------------
	case *ast.IfStmt: // FIXME: we should not needs this! we are only encountering this because we are fully parsing the GoStmt
		logger.Logger.Warnf("[CFG - PARSE EXPR] [%s.%s] ignoring %s: %s", service.GetName(), method.GetName(), utils.GetType(node), node)
	case *ast.BinaryExpr: // FIXME: same... e.g. if err != nil
		logger.Logger.Warnf("[CFG - PARSE EXPR] [%s.%s] ignoring %s: %s", service.GetName(), method.GetName(), utils.GetType(node), node)
	case *ast.Ident: // FIXME: same... e.g. if flag ...
		logger.Logger.Warnf("[CFG - PARSE EXPR] [%s.%s] ignoring %s: %s", service.GetName(), method.GetName(), utils.GetType(node), node)
	case *ast.SelectorExpr: // FIXME: same...
		logger.Logger.Fatalf("[CFG - PARSE EXPR] [%s.%s] ignoring %s: %s", service.GetName(), method.GetName(), utils.GetType(node), node)

	// ---------
	// For Loops
	// ---------
	case *ast.IncDecStmt: // e.g. increment in ForPost block (e.g. i++)
		incDecLeftValues(service, method, block, e.X, e.Tok)

	// ----------------
	// Other Statements
	// ----------------
	case *ast.DeferStmt:
		deferStmts = append(deferStmts, e)

	// ----------------
	// Ignore Remaining
	// ----------------
	default:
		logger.Logger.Fatalf("[CFG - PARSE EXPR] [%s.%s] unknown type in parseExpressions: %s", service.GetName(), method.GetName(), utils.GetType(node))
	}
	return deferStmts
}

func saveParsedFuncCallParams(service *service.Service, method *types.ParsedMethod, block *types.Block, parsedCall types.Call, args []ast.Expr) {
	if parsedCall.GetName() == "StorePost" {
		logger.Logger.Tracef("(1) FOUND CALL TO SERVICE VAR %s", parsedCall.GetName())
	}
	for i, arg := range args {
		logger.Logger.Tracef("[CFG] inside save func call params")
		param, _ := lookupVariableFromAstExpr(service, method, block, arg, nil, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetType().(*gotypes.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("[CFG] upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetType().String())
		}
		parsedCall.AddParam(param)
		logger.Logger.Tracef("ADDED PARAM: %s", param.LongString())
	}
	if parsedCall.GetName() == "StorePost" {
		logger.Logger.Tracef("(1) FOUND CALL TO SERVICE VAR %s", parsedCall.GetName())
	}
}

func getFuncCallDeps(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) []variables.Variable {
	var deps []variables.Variable
	for _, expr := range callExpr.Args {
		logger.Logger.Warnf("[CFG] [%s] searching for function call deps in expression %v", service.GetName(), expr)
		if v, _ := lookupVariableFromAstExpr(service, method, block, expr, nil, false); v != nil {
			deps = append(deps, v)
		}
	}
	return deps
}

func computeInternalFuncCallReturns(service *service.Service, callExpr *ast.CallExpr, call types.Call) *variables.TupleVariable {
	tupleVar := &variables.TupleVariable{
		VariableInfo: &variables.VariableInfo{
			Type: &gotypes.TupleType{},
			Id:   variables.VARIABLE_INLINE_ID,
		},
	}

	if signatureGoType, ok := service.GetPackage().GetTypeInfo(callExpr.Fun).(*golangtypes.Signature); ok {
		if signatureGoType.Results() != nil {
			signatureResults := lookup.LookupTypesForGoTypes(service.GetPackage(), signatureGoType.Results())
			for _, t := range signatureResults.(*gotypes.TupleType).Types {
				newVar := lookup.CreateVariableFromType("", t)
				tupleVar.AddVariableAndType(newVar)
				newVar.GetVariableInfo().SetParent(newVar, tupleVar)
				call.AddReturn(newVar)
			}
		}
	} else {
		logger.Logger.Fatalf("[CFG CALLS] unexpected type for imported method call %v", callExpr.Fun)
	}
	return tupleVar
}

func computeExternalFuncCallReturns(service *service.Service, callExpr *ast.CallExpr, deps []variables.Variable) *variables.TupleVariable {
	tupleType := &gotypes.TupleType{}
	tupleVar := &variables.TupleVariable{
		VariableInfo: &variables.VariableInfo{
			Type: tupleType,
			Id:   variables.VARIABLE_INLINE_ID,
		},
	}

	if signatureGoType, ok := service.GetPackage().GetTypeInfo(callExpr.Fun).(*golangtypes.Signature); ok {
		if signatureGoType.Results() != nil {
			signatureResults := lookup.LookupTypesForGoTypes(service.GetPackage(), signatureGoType.Results())

			if len(signatureResults.(*gotypes.TupleType).Types) == 1 && len(deps) == 0 {
				newVar := lookup.CreateVariableFromType("", signatureResults.(*gotypes.TupleType).Types[0])
				logger.Logger.Warnf("[FIXMEEEEEEE!!!!!!] (IS THIS EVEN CORRECT???) CREATED VAR FOR RETURNED TUPLE IN EXTERNAL FUNC CALL: %s", newVar.String())
				tupleVar.Variables = append(tupleVar.Variables, newVar)
				newVar.GetVariableInfo().SetParent(newVar, tupleVar)
			} else {
				logger.Logger.Warnf("[CFG CALLS] call returns tuple with len %d and depends on %d variables", len(signatureResults.(*gotypes.TupleType).Types), len(deps))
				for _, t := range signatureResults.(*gotypes.TupleType).Types {
					newVar := lookup.CreateVariableFromType("", t)
					ok := variables.AddUnderlyingDependencies(newVar, deps)
					if !ok {
						logger.Logger.Warnf("[CFG CALLS] cannot keep variable (%s) (%s) for underlying deps list with len (%d): %v", variables.VariableTypeName(newVar), newVar.String(), len(deps), deps)
						/* newVar = &variables.GenericVariable{
							VariableInfo: &variables.VariableInfo{
								Type: newVar.GetType(),
								Id:   variables.VARIABLE_UNASSIGNED_ID,
							},
							Params: deps,
						} */
						variables.AddVariableInfoDependencies(newVar, deps)
					}
					tupleVar.Variables = append(tupleVar.Variables, newVar)
					newVar.GetVariableInfo().SetParent(newVar, tupleVar)
				}
				logger.Logger.Warnf("CREATED COMPOSITE VAR FOR (%d) TUPLE: %s", len(deps), tupleVar.String())
			}
		}
	} else {
		logger.Logger.Fatalf("[CFG CALLS] unexpected type for imported method call %v", callExpr.Fun)
	}
	return tupleVar
}

func saveCallToStructOrInterface(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, leftVariableTypeName string, methodName string, pkgPath string) (*types.ParsedInternalCall, *variables.TupleVariable, *variables.TupleVariable) {
	pkg := service.GetPackage().GetImportedPackage(pkgPath)
	parsedMethod := pkg.GetParsedMethodIfExists(methodName, leftVariableTypeName)

	if parsedMethod != nil {
		logger.Logger.Warnf("[CFG CALLS] [%s] !!!!!!!!!!!! GOT PARSED METHOD (%s): %v", service.GetName(), methodName, parsedMethod.GetParsedCfg())
		//logger.Logger.Debugf("[CFG CALLS] got parsed method %s", parsedMethod.String())
		parsedCall := &types.ParsedInternalCall{
			ParsedCall: types.ParsedCall{
				Ast:    callExpr,
				Name:   parsedMethod.Name,
				Method: parsedMethod,
			},
			ServiceTypeName: &gotypes.ServiceType{Name: service.Name, PackagePath: service.GetPackageName()},
		}
		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		method.Calls = append(method.Calls, parsedCall)
		variable := computeInternalFuncCallReturns(service, callExpr, parsedCall)
		logger.Logger.Infof("[CFG CALLS] [%s] found internal call (%s) in package (%s) -- returned tuple: %s", service.GetName(), parsedCall.GetName(), pkg.GetName(), variable.String())
		return parsedCall, variable, nil
	}
	deps := getFuncCallDeps(service, method, block, callExpr)
	tupleVar := computeExternalFuncCallReturns(service, callExpr, deps)
	return nil, nil, tupleVar
}

// (b1) call to variable (including receiver) in block
func parseCallToVariableInBlock(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, variable variables.Variable, idents []*ast.Ident, identsStr string) *variables.TupleVariable {
	funcIdent := idents[len(idents)-1]
	logger.Logger.Infof("[CFG] [%s.%s] parsing call to variable (%s) in block for method (%s): %v", service.GetName(), method.Name, variable.String(), funcIdent, callExpr)

	// check if variable is a declared func
	if funcVar, ok := variable.(*variables.FuncVariable); ok {
		inlineFunc := block.GetLatestInlineFunc(funcVar.GetFuncType().GetName())
		tupleVar := &variables.TupleVariable{
			VariableInfo: &variables.VariableInfo{
				Id:   variables.VARIABLE_INLINE_ID,
				Type: &gotypes.TupleType{},
			},
		}
		results := parseInlineFuncCall(service, method, block, inlineFunc.CFG, funcVar.GetFuncType().Params, callExpr.Args)
		for _, r := range results {
			tupleVar.AddVariableAndType(r)
		}
		return tupleVar
	}

	logger.Logger.Tracef("[CFG CALLS] (1) call to variable: %s", variable.LongString())
	leftVariableTypeName := variable.GetType().GetName()
	variable = variables.UnwrapPointerVariable(variable)
	logger.Logger.Debugf("START ITERATING for variable: %s", variable)
	for i := 1; i < len(idents); i++ {
		logger.Logger.Debugf("ITERATING (%d) for variable: %s", i, variable)
		ident := idents[i]
		variable = variables.UnwrapPointerVariable(variable)

		if structVar, ok := variable.(*variables.StructVariable); ok {
			fieldName := ident.Name
			variable = structVar.GetFieldVariableIfExists(fieldName)

			if variable == nil {
				fieldType := structVar.GetStructType().GetFieldTypeByNameIfExists(fieldName)
				if fieldType != nil {
					fieldVar := lookup.CreateVariableFromType(fieldName, fieldType)
					structVar.AddFieldKeyVariable(fieldName, fieldVar)
				} else {
					methodName := ident.Name
					pkgPath := structVar.GetStructType().GetMethodPackagePath(methodName)

					var externalCallTupleVar *variables.TupleVariable
					_, variable, externalCallTupleVar = saveCallToStructOrInterface(service, method, block, callExpr, leftVariableTypeName, methodName, pkgPath)
					if externalCallTupleVar != nil {
						return externalCallTupleVar
					}
				}
			}
		} else if genericVar, ok := variable.(*variables.GenericVariable); ok {
			logger.Logger.Warnf("[CFG CALLS] ignoring generic var %s", genericVar.LongString())
			if deps := getFuncCallDeps(service, method, block, callExpr); deps != nil {
				tupleVar := computeExternalFuncCallReturns(service, callExpr, deps)
				return tupleVar
			}
			parsedCall := &types.ParsedInternalCall{
				ParsedCall: types.ParsedCall{
					Ast:     callExpr,
					CallStr: identsStr,
					Name:    funcIdent.Name,
					Pos:     callExpr.Pos(),
				},
			}
			tupleVar := computeInternalFuncCallReturns(service, callExpr, parsedCall)
			return tupleVar
		} else if interfaceVar, ok := variable.(*variables.InterfaceVariable); ok {
			methodName := ident.Name
			pkgPath := interfaceVar.GetInterfaceType().GetMethodPackagePath(methodName)

			var externalCallTupleVar *variables.TupleVariable
			_, variable, externalCallTupleVar = saveCallToStructOrInterface(service, method, block, callExpr, leftVariableTypeName, methodName, pkgPath)
			if externalCallTupleVar != nil {
				logger.Logger.Warnf("[CFG CALLS] EXTERNAL TUPLE VAR: %s (%s)", externalCallTupleVar.String(), utils.GetType(externalCallTupleVar.Variables[0]))
				return externalCallTupleVar
			}

			logger.Logger.Fatalf("[CFG CALLS] call to interface variable (%s) for method (%s) in package path (%s)", interfaceVar.LongString(), methodName, pkgPath)
			return nil
		} else if fieldVariable, ok := variable.(*variables.FieldVariable); ok {
			variable = fieldVariable.GetWrappedVariable()
			logger.Logger.Warnf("GOT VAR: %s", variable.String())
		} else if _, ok := variable.(*variables.ServiceVariable); ok {
			break
		} else if _, ok := variable.(*blueprint.BlueprintBackendVariable); ok {
			break
		} else if _, ok := variable.(*variables.TupleVariable); ok {
			logger.Logger.Fatalf("[CFG CALLS] [TODO] nested calls!")
		} else {
			logger.Logger.Fatalf("[CFG CALLS] unexpected call for variable (%s) with type (%s) (%s)", variable.String(), utils.GetType(variable), utils.GetType(variable.GetType()))
		}
	}
	// e.g. from internal calls
	if tupleVar, ok := variable.(*variables.TupleVariable); ok {
		return tupleVar
	}
	if serviceVar, ok := variable.(*variables.ServiceVariable); ok {
		// store function call either as service call or database call
		// if the field corresponds to a service field
		// 1. extract the service field from the current service
		// 2. get the target service service for the type
		// 3. add the targeted method of the other service for the current call expression
		targetService := service.Services[serviceVar.GetServiceName()]
		targetMethod := targetService.GetExportedMethod(funcIdent.Name)
		parsedCall := &types.ParsedServiceCall{
			ParsedCall: types.ParsedCall{
				Ast:     callExpr,
				CallStr: identsStr,
				Name:    funcIdent.Name,
				Pos:     callExpr.Pos(),
				Method:  targetMethod,
			},
			CallerTypeName: &gotypes.ServiceType{Name: service.Name, PackagePath: service.GetPackageName()},
			CalleeTypeName: serviceVar.GetType(),
		}
		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		tupleVar := computeInternalFuncCallReturns(service, callExpr, parsedCall)
		method.Calls = append(method.Calls, parsedCall)
		logger.Logger.Infof("[CFG CALLS] [%s] found service call (%s) -- returned tuple: %s", service.GetName(), parsedCall.Name, tupleVar.String())
		return tupleVar
	}
	if blueprintBackendVar, ok := variable.(*blueprint.BlueprintBackendVariable); ok {
		logger.Logger.Warnf("GOT BLUEPRINT BACKEND VAR: %s", blueprintBackendVar.String())
		blueprintBackendType := blueprintBackendVar.GetBlueprintBackendType()
		blueprintMethod := blueprintBackendType.GetMethod(funcIdent.Name)
		parsedCall := &types.ParsedDatabaseCall{
			ParsedCall: types.ParsedCall{
				Ast:     callExpr,
				CallStr: identsStr,
				Name:    funcIdent.Name,
				Pos:     callExpr.Pos(),
				Method:  blueprintMethod,
			},
			CallerTypeName: &gotypes.ServiceType{Name: service.Name, PackagePath: service.GetPackageName()},
			DbInstance:     blueprintBackendType.DatastoreInstance,
		}

		if blueprintBackendType.DatastoreInstance == nil {
			logger.Logger.Fatalf("[CFG CALLS] unexpected nil db instance for backend type (%s)", blueprintBackendType.String())
		}

		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		tupleVar := computeInternalFuncCallReturns(service, callExpr, parsedCall)

		// maybe user is just getting the collection
		if blueprintMethod.IsNoSQLBackendCall() {
			if ok, index := blueprintMethod.ReturnsNoSQLCollection(); ok {
				databaseName := parsedCall.Params[1].GetType().GetBasicValue()
				collectionName := parsedCall.Params[2].GetType().GetBasicValue()

				blueprintMethod.SetNoSQLDatabaseCollection(databaseName, collectionName, blueprintBackendType.DatastoreInstance)
				collectionType := tupleVar.GetVariableAt(index).(*blueprint.BlueprintBackendVariable).GetBlueprintBackendType()
				collectionType.SetNoSQLDatabaseCollection(databaseName, collectionName, blueprintBackendType.DatastoreInstance)
				logger.Logger.Infof("[CFG CALLS] found NoSQLDatabase call (%s) to instance (%s) -- returned tuple: %s", parsedCall.Name, parsedCall.DbInstance.String(), tupleVar.String())
				return tupleVar
			} else {
				logger.Logger.Fatalf("[CFG CALLS] method (%s) must return NoSQL collection", blueprintMethod.String())
			}
		}
		if blueprintMethod.IsNoSQLCollectionCall() && blueprintBackendType.IsNoSQLCollection() {
			databaseName := blueprintBackendType.NoSQLComponent.Database
			collectionName := blueprintBackendType.NoSQLComponent.Collection

			if ok, index := blueprintMethod.ReturnsNoSQLCursor(); ok {
				fmt.Printf("[%s] HERE: %s (DATABASE = %s, COLLECTION = %s)", service.GetName(), blueprintMethod.String(), databaseName, collectionName)
				collectionType := tupleVar.GetVariableAt(index).(*blueprint.BlueprintBackendVariable).GetBlueprintBackendType()
				collectionType.SetNoSQLDatabaseCursor(databaseName, collectionName, blueprintBackendType.DatastoreInstance)

				method.Calls = append(method.Calls, parsedCall)
				logger.Logger.Infof("[CFG CALLS] found (NoSQLDatabase.NoSQLCollection -> NoSQLCursor) call (%s) to instance (%s) -- returned tuple: %s", parsedCall.Name, parsedCall.DbInstance.String(), tupleVar.String())
				return tupleVar
			} else {
				// e.g. NoSQLDatabase.NoSQLCollection.InsertOne(), NoSQLDatabase.NoSQLCollection.InsertMany()
				method.Calls = append(method.Calls, parsedCall)
				logger.Logger.Infof("[CFG CALLS] found (NoSQLDatabase.NoSQLCollection -> _ ) call (%s) to instance (%s) -- returned tuple: %s", parsedCall.Name, parsedCall.DbInstance.String(), tupleVar.String())
				return tupleVar
			}
		}
		if blueprintMethod.IsNoSQLCursorCall() {
			// e.g. NoSQLDatabase.NoSQLCursor.One(), NoSQLDatabase.NoSQLCursor.All()
			// do not append: cursor is already tainted after reading from collection
			logger.Logger.Infof("[CFG CALLS] found NoSQLCursor call (%s) to instance (%s) -- returned tuple: %s", parsedCall.Name, parsedCall.DbInstance.String(), tupleVar.String())
			return tupleVar
		}
		method.Calls = append(method.Calls, parsedCall)
		logger.Logger.Infof("[CFG CALLS] found Cache or Queue datastore call (%s) to instance (%s) -- returned tuple: %s", parsedCall.Name, parsedCall.DbInstance.String(), tupleVar.String())
		return tupleVar
	}
	logger.Logger.Fatalf("[CFG CALLS] unable to parse call to variable (%s) with type (%s) in call expr fun: %v\nBLOCK VARS: %v", variable.String(), utils.GetType(variable), callExpr.Fun, block.Vars)
	return nil
}

func searchCallToMethodInImportedPackage(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, pkg *types.Package, idents []*ast.Ident, identsStr string) (*variables.TupleVariable, *types.Package, bool) {
	funcIdent := idents[len(idents)-1]
	logger.Logger.Infof("[CFG CALLS] [%s.%s] searching call to method (%s) in imported package (%s)", service.GetName(), method.Name, funcIdent, pkg.GetName())
	switch pkg.Type {
	case types.EXTERNAL:
		if deps := getFuncCallDeps(service, method, block, callExpr); deps != nil {
			tupleVar := computeExternalFuncCallReturns(service, callExpr, deps)
			return tupleVar, nil, false
		}
		parsedCall := &types.ParsedInternalCall{
			ParsedCall: types.ParsedCall{
				Ast:     callExpr,
				CallStr: identsStr,
				Name:    funcIdent.Name,
				Pos:     callExpr.Pos(),
			},
		}
		tupleVar := computeInternalFuncCallReturns(service, callExpr, parsedCall)
		logger.Logger.Infof("[CFG CALLS] [%s.%s] found call (%s) to method in imported external package (%s) -- returned tuple: %s", service.GetName(), method.Name, parsedCall.CallStr, pkg.GetName(), tupleVar.String())
		return tupleVar, nil, false
	case types.BLUEPRINT:
		logger.Logger.Warnf("[CFG CALLS] [%s.%s] ignoring call with idents (%v) in blueprint package", service.GetName(), method.Name, identsStr)
		// ignore direct calls to blueprint package
		// we only care about backend calls to functions of well-defined interfaces (cache, queue, nosqldatabase)
		return nil, nil, true
	case types.APP:
		if parsedMethod := pkg.GetParsedMethodIfExists(funcIdent.Name, ""); parsedMethod != nil {
			return nil, pkg, false

		}
	}
	return nil, nil, false
}

func searchCallToMethodInImport(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, impt *types.Import, idents []*ast.Ident, identsStr string) (*variables.TupleVariable, *types.Package, bool) {
	funcIdent := idents[len(idents)-1]
	logger.Logger.Infof("[CFG CALLS] [%s.%s] searching call to method (%s) in imported package (%s)", service.GetName(), method.Name, funcIdent, impt.Alias)

	if pkg := service.GetPackage().GetImportedPackage(impt.PackagePath); pkg != nil {
		return searchCallToMethodInImportedPackage(service, method, block, callExpr, pkg, idents, identsStr)
	}
	return nil, nil, false
}

func parseCallToMethodInImportedOrCurrentPackage(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, callPkg *types.Package, idents []*ast.Ident, identsStr string) *variables.TupleVariable {
	funcIdent := idents[len(idents)-1]
	logger.Logger.Infof("[CFG CALLS] [%s.%s] parsing call to method (%s) in imported or current package (%s): %v", service.GetName(), method.Name, funcIdent, callPkg.Name, callExpr)

	if parsedMethod := callPkg.GetParsedMethodIfExists(funcIdent.Name, ""); parsedMethod != nil {
		parsedCall := &types.ParsedInternalCall{
			ParsedCall: types.ParsedCall{
				Ast:     callExpr,
				CallStr: identsStr,
				Name:    funcIdent.Name,
				Method:  parsedMethod,
			},
			ServiceTypeName: &gotypes.ServiceType{Name: service.Name, PackagePath: service.GetPackageName()},
		}
		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		tupleVar := computeInternalFuncCallReturns(service, callExpr, parsedCall)
		if callPkg == service.GetPackage() {
			logger.Logger.Infof("[CFG CALLS] [%s.%s] found call (%s) to method in current package (%s) -- returned tuple: %s", service.GetName(), method.Name, parsedCall.CallStr, callPkg.Name, tupleVar.String())
			method.Calls = append(method.Calls, parsedCall)
			return tupleVar
		}

		logger.Logger.Infof("[CFG CALLS] [%s.%s] found call (%s) to method in imported app package (%s) -- returned tuple: %s", service.GetName(), method.Name, parsedCall.CallStr, callPkg.Name, tupleVar.String())
		if deps := getFuncCallDeps(service, method, block, callExpr); deps != nil {
			tupleVar := computeExternalFuncCallReturns(service, callExpr, deps)
			return tupleVar
		}
		parsedCall = &types.ParsedInternalCall{
			ParsedCall: types.ParsedCall{
				Ast:     callExpr,
				CallStr: identsStr,
				Name:    funcIdent.Name,
				Pos:     callExpr.Pos(),
			},
		}
		tupleVar = computeInternalFuncCallReturns(service, callExpr, parsedCall)
		return tupleVar
	}
	return nil
}

func wrapInTupleVariable(varsToWrap ...variables.Variable) *variables.TupleVariable {
	var typesToWrap []gotypes.Type
	for _, v := range varsToWrap {
		typesToWrap = append(typesToWrap, v.GetType())
	}
	return &variables.TupleVariable{
		Variables: varsToWrap,
		VariableInfo: &variables.VariableInfo{
			Type: &gotypes.TupleType{
				Types: typesToWrap,
			},
			Id: variables.VARIABLE_UNASSIGNED_ID,
		},
	}
}

func wrapInBasicVariable(variable variables.Variable, typeName string) *variables.BasicVariable {
	return &variables.BasicVariable{
		VariableInfo: &variables.VariableInfo{
			Type: &gotypes.BasicType{
				Name:  typeName,
				Value: variable.GetType().GetBasicValue(),
			},
			Id: variables.VARIABLE_UNASSIGNED_ID,
		},
	}
}

// call to golang built-in func or type
func parseBuiltInGoFuncOrTypeCall(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, funcIdent *ast.Ident) variables.Variable {
	logger.Logger.Infof("[CFG] [%s.%s] parsing built-in go function or type call (%s) in imported or current package: %v", service.GetName(), method.Name, funcIdent.Name, callExpr)

	if utils.IsBuiltInGoFunc(funcIdent.Name) {
		return parseBuiltInGoFuncCall(service, method, block, callExpr, funcIdent)
	} else if utils.IsBuiltInGoType(funcIdent.Name) {
		return parseBuiltInGoTypeCall(service, method, block, callExpr, funcIdent)
	}
	logger.Logger.Fatalf("[CFG] [%s.%s] unexpected built-in go func or type (%s): %v", service.GetName(), method.Name, funcIdent.Name, callExpr)
	return nil
}

// call to golang built-in func e.g. make(...), println(...), append(...)
func parseBuiltInGoFuncCall(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, funcIdent *ast.Ident) variables.Variable {
	logger.Logger.Infof("[CFG] [%s.%s] parsing built-in go function call (%s) in imported or current package: %v", service.GetName(), method.Name, funcIdent.Name, callExpr)

	deps := getFuncCallDeps(service, method, block, callExpr)
	switch funcIdent.Name {
	case "make":
		return wrapInTupleVariable(deps[0])
	case "len":
		return &variables.BasicVariable{
			VariableInfo: &variables.VariableInfo{
				Type: &gotypes.BasicType{
					Name:  "int",
					Value: fmt.Sprintf("len(%s)", deps[0].String()),
				},
				Id: variables.VARIABLE_UNASSIGNED_ID,
			},
			UnderlyingVariables: deps,
		}
	case "append":
		slice := deps[0]
		elems := deps[1]

		if sliceVariable, ok := slice.(*variables.SliceVariable); ok {
			sliceVariable.AppendElements(elems)
		} else if arrayVariable, ok := slice.(*variables.ArrayVariable); ok {
			arrayVariable.AppendElements(elems)
		} else {
			logger.Logger.Fatalf("[CFG] [%s] unexpected slice type (%s) in \"append\" call (%v)", service.GetName(), utils.GetType(slice), callExpr)
		}
		return wrapInTupleVariable(slice)
	case "println":
		return nil
	default:
		logger.Logger.Fatalf("[CFG] [%s] unexpected built-in go func (%s) for function call (%v)", service.GetName(), funcIdent.Name, callExpr)
	}
	return nil
}

// call to golang built-in type e.g. []byte(...)
func parseBuiltInGoTypeCall(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, funcIdent *ast.Ident) variables.Variable {
	logger.Logger.Infof("[CFG] [%s.%s] parsing built-in go type call (%s) in imported or current package: %v", service.GetName(), method.Name, funcIdent.Name, callExpr)

	deps := getFuncCallDeps(service, method, block, callExpr)
	switch funcIdent.Name {
	case "byte":
		return wrapInBasicVariable(deps[0], "byte")
	case "string":
		return wrapInBasicVariable(deps[0], "string")
	case "float32":
		return wrapInBasicVariable(deps[0], "float32")
	default:
		logger.Logger.Fatalf("[CFG] [%s] unexpected built-in go type (%s) for function call (%v)", service.GetName(), funcIdent.Name, callExpr)
	}
	return nil
}

// FIXME: this does not support nested calls!!!!
func parseAndSaveCall(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) variables.Variable {
	logger.Logger.Infof("[CFG CALLS] [%s] parsing call (%s) for args (%v)", service.GetName(), callExpr.Fun, callExpr.Args)
	idents, identsStr := lookup.GetAllSelectorIdents(callExpr.Fun)
	leftIdent := idents[0]
	funcIdent := idents[len(idents)-1]

	var varsStr = ""
	for i, expr := range callExpr.Args {
		v, _ := lookupVariableFromAstExpr(service, method, block, expr, nil, false)
		varsStr += fmt.Sprintf("\t\t\t\t\t\t\t - argument %d: (%s)\n", i, v.String())
	}

	logger.Logger.Infof("[CFG CALLS] [%s] found arguments for call with idents (%s):\n%s", service.GetName(), identsStr, varsStr)

	// call to variable (including receiver) in block
	if variable := block.GetLastestVariableIfExists(leftIdent.Name); variable != nil {
		tupleVar := parseCallToVariableInBlock(service, method, block, callExpr, variable, idents, identsStr)
		if tupleVar != nil {
			return tupleVar
		}
	}

	// call to golang built-in type (e.g. make, println, append)
	if len(idents) == 1 && utils.IsBuiltInGoTypeOrFunc(funcIdent.Name) {
		return parseBuiltInGoFuncOrTypeCall(service, method, block, callExpr, funcIdent)
	}

	var callInPackage bool
	var callPkg *types.Package
	var tupleVar *variables.TupleVariable

	// call to method in imported package of file
	logger.Logger.Debugf("[CFG CALLS] check if call is to imported package (%s) for package import map:\n%v", leftIdent.Name, service.GetPackage().ImportsByAliasMapStr())
	if pkg := service.GetPackage().GetImportedPackageByAliasIfExists(leftIdent.Name); pkg != nil {
		var isBlueprintCall bool
		tupleVar, callPkg, isBlueprintCall = searchCallToMethodInImportedPackage(service, method, block, callExpr, pkg, idents, identsStr)
		logger.Logger.Warnf("!!!!!!!!!!!!!!! FOUND CALL TO METHOD IN IMPORTED PACKAGE: %v // %v // %v", tupleVar, callPkg, isBlueprintCall)
		if isBlueprintCall { // skip all blueprint calls that are not on backend components - e.g. backend.GetLogger().Info(...)
			return nil
		}
		if tupleVar != nil {
			return tupleVar
		}
		if callPkg != nil {
			callInPackage = true
		}
	} else if  impt := service.File.GetImportIfExists(leftIdent.Name); impt != nil {
		var isBlueprintCall bool
		tupleVar, callPkg, isBlueprintCall = searchCallToMethodInImport(service, method, block, callExpr, impt, idents, identsStr)
		if isBlueprintCall { // skip all blueprint calls that are not on backend components - e.g. backend.GetLogger().Info(...)
			return nil
		}
		if tupleVar != nil {
			return tupleVar
		}
		if callPkg != nil {
			callInPackage = true
		}
	}

	// call to method in current package
	logger.Logger.Infof("[CFG CALLS] [%s.%s] try parsing call to method (%s) in current package (%s): %v", service.GetName(), method.Name, funcIdent.Name, service.GetPackageName(), callExpr)
	if parsedMethod := service.GetPackage().GetParsedMethodIfExists(funcIdent.Name, ""); parsedMethod != nil {
		callInPackage = true
		callPkg = service.GetPackage()
	}

	if callInPackage && callPkg != nil {
		tupleVar := parseCallToMethodInImportedOrCurrentPackage(service, method, block, callExpr, callPkg, idents, identsStr)
		if tupleVar != nil {
			return tupleVar
		}
	}

	logger.Logger.Fatalf("[TODO] unexpected call: %v (call in package = %t, call pkg = %s) -- idents types = %v", callExpr.Fun, callInPackage, callPkg, idents)
	return nil
}
