package controlflow

import (
	"fmt"
	"go/ast"
	"go/token"
	golangtypes "go/types"

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
		logger.Logger.Warnf("[CFG] [%s] ignoring parsing for already parsed method (%s)", service.GetName(), method.String())
		return
	}
	method.SetParsed()
	var visited = make(map[int32]bool)
	for _, block := range method.ParsedCfg.GetParsedBlocks() {
		visitBasicBlock(service, method, block, visited)
	}
}

func visitBasicBlock(service *service.Service, method *types.ParsedMethod, block *types.Block, visited map[int32]bool) {
	if visited[block.GetIndex()] {
		return
	}
	visited[block.GetIndex()] = true
	for _, blockNode := range block.GetNodes() { //FIXME????
		parseExpressions(service, method, block, blockNode)
	}

	for _, succ := range block.GetSuccs() {
		parsedSucc := method.ParsedCfg.GetParsedBlockAtIndex(succ.Index)
		parsedSucc.AppendVarsFromPredecessor(block)
		visitBasicBlock(service, method, parsedSucc, visited)
	}
}

func getAssignmentRightVariables(service *service.Service, method *types.ParsedMethod, block *types.Block, assignStmt *ast.AssignStmt) []variables.Variable {
	var rvariables []variables.Variable
	for _, rvalue := range assignStmt.Rhs {
		variable, _ := lookupVariableFromAstExpr(service, method, block, rvalue, true)
		if tupleVariable, ok := variable.(*variables.TupleVariable); ok {
			rvariables = append(rvariables, tupleVariable.Variables...)
		} else {
			rvariables = append(rvariables, variable)
		}
	}
	return rvariables
}

func assignLeftValues(service *service.Service, method *types.ParsedMethod, block *types.Block, assignStmt *ast.AssignStmt) {
	logger.Logger.Debugf("[CFG ASSIGN LEFT] [%s] visiting stmt (%s): %v", service.GetName(), utils.GetType(assignStmt), assignStmt)
	rvariables := getAssignmentRightVariables(service, method, block, assignStmt)
	for i, rvariable := range rvariables {
		lvalue := assignStmt.Lhs[i]
		logger.Logger.Debugf("[CFG ASSIGN LEFT] [%s] got rvariable type (%s) for lvalue type (%s): %v", service.GetName(), utils.GetType(rvariable), utils.GetType(lvalue), rvariable.String())
		switch e := lvalue.(type) {
		case *ast.Ident:
			if assignStmt.Tok == token.DEFINE || assignStmt.Tok == token.ASSIGN { // := OR =
				if rvariable.GetVariableInfo().GetName() == "" {
					rvariable.GetVariableInfo().SetUnassigned()
					rvariable.GetVariableInfo().SetName(e.Name)
					block.AddVariable(rvariable)
					// HERE FOR QUERY (SliceVariable): query primitive.D = (struct{Key "postid" string, Value int64})
					/* if rvariable.GetVariableInfo().GetName() == "query" {
						for _, b := range method.ParsedCfg.Cfg.Blocks {
							logger.Logger.Debugf("BLOCK: index = %d, kind = %v, nodes = %v", b.Index, b.Kind, b.Live)
							for _, n := range b.Nodes {
								logger.Logger.Debugf("\t\t - Node: %v", utils.GetType(n))
							}
						}
						logger.Logger.Fatalf("[BLOCK (%d)] HERE FOR QUERY (%s): %s", block.Block.Index, utils.GetType(rvariable), rvariable.LongString())
					} */
				} else {
					logger.Logger.Warnf("[CFG] FIX ME!!!! WE SHOULD SEARCH FOR THE LEFT VARIABLE THAT ALREADY EXISTS IN THE BLOCK")
					lvariable := rvariable.DeepCopy(true)
					lvariable.GetVariableInfo().SetName(e.Name)
					lvariable.GetVariableInfo().SetUnassigned()
					block.AddVariable(lvariable)
				}
			} else if assignStmt.Tok == token.ADD_ASSIGN {
				lvariable := block.GetLastestVariable(e.Name)
				lvariable.GetType().AddValue(rvariable.GetType().GetBasicValue())
			} else {
				logger.Logger.Fatalf("[CFG ASSIGN LEFT] [%s] unexpected token (%v) for assignment: %v", service.GetName(), assignStmt.Tok, assignStmt)
			}
		case *ast.SelectorExpr:
			lvariable, _ := lookupVariableFromAstExpr(service, method, block, e, false)
			switch ee := lvariable.(type) {
			case *variables.FieldVariable:
				lvariable.AssignVariable(rvariable)
			default:
				logger.Logger.Fatalf("[CFG ASSIGN LEFT] [%s] unsupported left variable type (%s): %v", service.GetName(), utils.GetType(ee), lvariable.String())
			}
		case *ast.IndexExpr: // e.g. res[rt] = pc
			lvariable, _ := lookupVariableFromAstExpr(service, method, block, e.X, false)
			switch ee := lvariable.(type) {
			case *variables.MapVariable:
				idxVariable, _ := lookupVariableFromAstExpr(service, method, block, e.Index, false)
				ee.AddKeyValue(idxVariable, rvariable)
			default:
				logger.Logger.Fatalf("[CFG ASSIGN LEFT] [%s] unsupported left variable type (%s): %v", service.GetName(), utils.GetType(ee), lvariable.String())
			}
		default:
			logger.Logger.Fatalf("[CFG ASSIGN LEFT] [%s] unexpected type (%s) for left value (%v) in assignment with token (%v): %v", method.Name, utils.GetType(lvalue), lvalue, assignStmt.Tok, assignStmt)
		}
	}
}

func parseExpressions(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) {
	logger.Logger.Debugf("[CFG PARSER EXPR] (%s) visiting node (%v)", utils.GetType(node), node)
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
		// e.g. var str []byte
		// OR
		// e.g. var str = []byte(...)

		logger.Logger.Warnf("[CFG PARSER EXPR] parsing value spec with names = (%v) and values = (%v)", e.Names, e.Values)
		// FIXME

		var vars []variables.Variable
		for i, v := range e.Values {
			logger.Logger.Warnf("[CFG PARSER EXPR] (%d) COMPUTING VALUESPEC VALUE: %v", i, v)
			variable := saveCalls(service, method, block, v)
			vars = append(vars, variable)
			logger.Logger.Warnf("[CFG PARSER EXPR] (%d) GOT TUPLE VAR: %s", i, variable.String())
		}
		for i, ident := range e.Names {
			// variable is being declared and assigned
			if len(vars) > 0 && i < len(vars) {
				assignedVariable := vars[i]
				assignedVariable.GetVariableInfo().SetName(ident.Name)
				logger.Logger.Warnf("[CFG PARSER EXPR] VARIABLE IS ASSIGNED: %s", assignedVariable.String())
				block.AddVariable(assignedVariable)
			} else { // variable is being just declared
				t := lookup.ComputeTypeForAstExpr(service.File, e.Type)
				declaredVariable := lookup.CreateVariableFromType(ident.Name, t)
				logger.Logger.Warnf("[CFG PARSER EXPR] VARIABLE IS DECLARED: %s", declaredVariable.String())
				block.AddVariable(declaredVariable)
			}
		}
	case *ast.AssignStmt:
		assignLeftValues(service, method, block, e)
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
		logger.Logger.Debugf("[CFG EXPR] FFFOOOOUNNDDD COMPOSITE LITE %v", e.Elts)
		for _, elt := range e.Elts {
			parseExpressions(service, method, block, elt)
		}
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
		logger.Logger.Fatalf("unknown type in parseExpressions for type %s: %v", utils.GetType(service), service)
	}
}

func saveCalls(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) variables.Variable {
	logger.Logger.Debugf("[CFG SAVE CALLS] (%s) visiting node (%v)", utils.GetType(node), node)

	switch e := node.(type) {
	case *ast.CallExpr:
		return parseAndSaveCall(service, method, block, e)
	case *ast.CompositeLit:
		// e.g. creating a structure where a field is obtained from a function call
		//FIXME: is this even correct????
		var composedTupleVar *variables.TupleVariable
		for _, elt := range e.Elts {
			tupleVar := saveCalls(service, method, block, elt)
			if composedTupleVar == nil {
				composedTupleVar = tupleVar.(*variables.TupleVariable)
			} else {
				composedTupleVar.MergeTupleVariable(tupleVar.(*variables.TupleVariable))
			}

		}
	case *ast.KeyValueExpr:
		//FIXME: is this even correct????
		composedTupleVar := saveCalls(service, method, block, e.Key)
		tupleVar := saveCalls(service, method, block, e.Value)
		composedTupleVar.(*variables.TupleVariable).MergeTupleVariable(tupleVar.(*variables.TupleVariable))
		return tupleVar
	case *ast.SelectorExpr:
		return saveCalls(service, method, block, e.X)
	case *ast.Ident, *ast.TypeAssertExpr, *ast.BasicLit: // basic lit e.g. integers (1), strings ("foo"), etc
	default:
		logger.Logger.Fatalf("unknown type in saveCalls for type %s: %v", utils.GetType(e), e)
	}
	return nil
}

func saveParsedFuncCallParams(service *service.Service, method *types.ParsedMethod, block *types.Block, parsedCall types.Call, args []ast.Expr) {
	/* if parsedCall.GetName() == "StorePostNoSQL" {
		logger.Logger.Debugf("(1) FOUND CALL TO SERVICE VAR %s", parsedCall.GetName())
	} */
	for i, arg := range args {
		logger.Logger.Tracef("[CFG] inside save func call params")
		param, _ := lookupVariableFromAstExpr(service, method, block, arg, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetType().(*gotypes.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("[CFG] upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetType().String())
		}
		parsedCall.AddParam(param)
		/* logger.Logger.Debugf("added param with type (%s): %s", utils.GetType(param), param.String())
		for _, d := range variables.GetIndirectDependencies(param) {
			logger.Logger.Debugf("\t\t\t - %s", d.String())
		} */
	}
	//logger.Logger.Debugf("[CFG] added params to func call %s", parsedCall.String())
	/* if parsedCall.GetName() == "InsertOne" {
		logger.Logger.Fatalf("(2) FOUND CALL TO SERVICE VAR %s: BLOCK VARS:\n%v", parsedCall.GetName(), block.Vars)
	} */
}

func getFuncCallDeps(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) []variables.Variable {
	var deps []variables.Variable
	for _, expr := range callExpr.Args {
		logger.Logger.Warnf("[CFG] [%s] searching for function call deps in expression %v", service.GetName(), expr)
		if v, _ := lookupVariableFromAstExpr(service, method, block, expr, false); v != nil {
			deps = append(deps, v)
		}
	}
	return deps
}

func computeInternalFuncCallReturns(service *service.Service, callExpr *ast.CallExpr, call types.Call) *variables.TupleVariable {
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
			for _, t := range signatureResults.(*gotypes.TupleType).Types {
				newVar := lookup.CreateVariableFromType("", t)
				tupleVar.Variables = append(tupleVar.Variables, newVar)
				tupleType.Types = append(tupleType.Types, newVar.GetType())
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
			} else {
				for _, t := range signatureResults.(*gotypes.TupleType).Types {
					newVar := lookup.CreateVariableFromType("", t)
					compositeVar := &variables.CompositeVariable{
						VariableInfo: &variables.VariableInfo{
							Type: newVar.GetType(),
							Id:   variables.VARIABLE_UNASSIGNED_ID,
						},
						Params: deps,
					}
					logger.Logger.Warnf("CREATED COMPOSITE VAR FOR (%d) DEPS: %s", len(deps), compositeVar.String())
					tupleVar.Variables = append(tupleVar.Variables, compositeVar)
				}
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
			ServiceTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
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

	logger.Logger.Tracef("[CFG CALLS] (1) call to variable: %s", variable.LongString())
	leftVariableTypeName := variable.GetType().GetName()
	if pointerVar, ok := variable.(*variables.PointerVariable); ok {
		//logger.Logger.Debugf("[CFG CALLS] (0) got pointer var (to %s): %s", utils.GetType(pointerVar.PointerTo.GetType()), pointerVar.String())
		variable = pointerVar.PointerTo
	}
	for i := 1; i < len(idents); i++ {
		ident := idents[i]
		if pointerVar, ok := variable.(*variables.PointerVariable); ok {
			//logger.Logger.Debugf("[CFG CALLS] (1) got pointer var (to %s): %s", utils.GetType(pointerVar.PointerTo.GetType()), pointerVar.String())
			variable = pointerVar.GetPointerTo()
		}

		if _, ok := variable.GetType().(*gotypes.UserType); ok {
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
			} else {
				logger.Logger.Fatalf("[CFG CALLS] (5) call to variable (type = %s): %s", utils.GetType(variable), variable.LongString())
				return nil
			}
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
			CallerTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
			CalleeTypeName: serviceVar.GetType(),
		}
		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		tupleVar := computeInternalFuncCallReturns(service, callExpr, parsedCall)
		method.Calls = append(method.Calls, parsedCall)
		logger.Logger.Infof("[CFG CALLS] [%s] found service call (%s) -- returned tuple: %s", service.GetName(), parsedCall.Name, tupleVar.String())
		return tupleVar
	}
	if blueprintBackendVar, ok := variable.(*blueprint.BlueprintBackendVariable); ok {
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
			CallerTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
			DbInstance:     blueprintBackendType.DbInstance,
		}

		if blueprintBackendType.DbInstance == nil {
			logger.Logger.Fatalf("[CFG CALLS] unexpected nil db instance for backend type (%s)", blueprintBackendType.String())
		}

		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		tupleVar := computeInternalFuncCallReturns(service, callExpr, parsedCall)

		// maybe user is just getting the collection
		if blueprintMethod.IsNoSQLBackendCall() {
			if ok, index := blueprintMethod.ReturnsNoSQLCollection(); ok {
				databaseName := parsedCall.Params[1].GetType().GetBasicValue()
				collectionName := parsedCall.Params[2].GetType().GetBasicValue()

				blueprintMethod.SetNoSQLDatabaseCollection(databaseName, collectionName, blueprintBackendType.DbInstance)
				collectionType := tupleVar.GetVariableAt(index).(*blueprint.BlueprintBackendVariable).GetBlueprintBackendType()
				collectionType.SetNoSQLDatabaseCollection(databaseName, collectionName, blueprintBackendType.DbInstance)
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
				blueprintMethod.SetNoSQLDatabaseCursor(databaseName, collectionName, blueprintBackendType.DbInstance)
				collectionType := tupleVar.GetVariableAt(index).(*blueprint.BlueprintBackendVariable).GetBlueprintBackendType()
				collectionType.SetNoSQLDatabaseCursor(databaseName, collectionName, blueprintBackendType.DbInstance)

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

func searchCallToMethodInImportedPackage(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr, impt *types.Import, idents []*ast.Ident, identsStr string) (*variables.TupleVariable, *types.Package, bool) {
	funcIdent := idents[len(idents)-1]
	logger.Logger.Infof("[CFG CALLS] [%s.%s] searching call to method (%s) in imported package (%s)", service.GetName(), method.Name, funcIdent, impt.Alias)

	if pkg := service.GetPackage().GetImportedPackage(impt.PackagePath); pkg != nil {
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
			logger.Logger.Infof("[CFG CALLS] [%s.%s] found call (%s) to method in imported external package (%s) -- returned tuple: %s", service.GetName(), method.Name, parsedCall.CallStr, impt.PackageName, tupleVar.String())
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
			ServiceTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
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
		v, _ := lookupVariableFromAstExpr(service, method, block, expr, false)
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

	// call to method in imported package
	logger.Logger.Debugf("[CFG CALLS] IS CALL TO IMPORTED PACKAGE ???? (IDENT = %s): IMPORTS = %v", leftIdent.Name, service.File.Imports)
	if impt, ok := service.File.Imports[leftIdent.Name]; ok {
		var isBlueprintCall bool
		tupleVar, callPkg, isBlueprintCall = searchCallToMethodInImportedPackage(service, method, block, callExpr, impt, idents, identsStr)
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

	// can be a type declaration e.g. []byte()
	//FIXME
	/* v, t := lookupVariableFromAstExpr(service, method, block, callExpr.Fun, false)
	if v != nil && t != nil {
		logger.Logger.Warnf("FIXME: ADD CONTENT TO VAR!!!!")
		return v
	} */

	logger.Logger.Fatalf("[TODO] unexpected call: %v (call in package = %t, call pkg = %s) -- idents types = %v", callExpr.Fun, callInPackage, callPkg, idents)
	return nil
}
