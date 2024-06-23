package controlflow

import (
	"go/ast"
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
	for _, blockNode := range block.GetNodes() {
		parseExpressions(service, method, block, blockNode)
	}

	for _, succ := range block.GetSuccs() {
		parsedSucc := method.ParsedCfg.GetParsedBlockAtIndex(succ.Index)
		parsedSucc.CopyVarsFromPredecessor(block)
		visitBasicBlock(service, method, parsedSucc, visited)
	}
}

func parseExpressions(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) {
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
		// FIXME
		for _, v := range e.Values {
			saveCalls(service, method, block, v)
		}
		t := lookup.ComputeTypeForAstExpr(service.File, e.Type)
		for _, ident := range e.Names {
			decl := lookup.CreateVariableFromType(ident.Name, t)
			block.AddVariable(decl)
		}
	case *ast.AssignStmt:
		if len(e.Rhs) > 1 {
			logger.Logger.Fatalf("[CFG EXPR] unexpected number (%d) of right values (%v) in assignment (%v)", len(e.Rhs), e.Rhs, e)
		}
		for i, rvalue := range e.Rhs {
			variable := lookupVariableFromAstExpr(service, method, block, rvalue, true)

			if tupleVariable, ok := variable.(*variables.TupleVariable); ok {
				if len(e.Lhs) != len(tupleVariable.Variables) {
					logger.Logger.Fatalf("[CFG EXPR] number (%d) of left values (%v) does not match number (%d) of tuple variables (%v) in assignment %v", len(e.Lhs), e.Lhs, len(tupleVariable.Variables), tupleVariable.Variables, e)
				}

				for j, lvalue := range e.Lhs {
					variable = tupleVariable.Variables[j]
					if leftIdent, ok := lvalue.(*ast.Ident); ok {
						variable.GetVariableInfo().SetName(leftIdent.Name)
						variable.GetVariableInfo().SetUnassigned()
						block.AddVariable(variable)
					} else {
						logger.Logger.Fatalf("[CFG EXPR] unexpected type (%s) for left value (%v) in assignment (%v)", utils.GetType(lvalue), lvalue, e)
					}
				}
				logger.Logger.Infof("[CFG EXPR] matched left values (%v) to tuple variable (%v)", e.Lhs, tupleVariable.LongString())
			} else {
				lvalue := e.Lhs[i]
				if lvalue != nil {
					if leftIdent, ok := lvalue.(*ast.Ident); ok {
						variable.GetVariableInfo().SetName(leftIdent.Name)
						variable.GetVariableInfo().SetUnassigned()
						block.AddVariable(variable)
					} else {
						logger.Logger.Fatalf("[CFG EXPR] unexpected type (%s) for left value (%v) in assignment (%v)", utils.GetType(lvalue), lvalue, e)
					}
				} else {
					logger.Logger.Fatalf("[CFG EXPR] left value with index %d not found in assignment (%v)", i, e)
				}
			}
			//FIXME: assign to fields within structures
		}
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
		parseAndSaveCallIfValid(service, method, block, e)
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

func saveCalls(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) {
	logger.Logger.Infof("---------- %v", utils.GetType(node))
	switch e := node.(type) {
	case *ast.CallExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD CALL EXPR %v", e)
		parseAndSaveCallIfValid(service, method, block, e)
	case *ast.CompositeLit:
		// e.g. creating a structure where a field is obtained from a function call
		logger.Logger.Infof("FFFOOOOUNNDDD COMPOSITE LITE %v", e)
		for _, elt := range e.Elts {
			saveCalls(service, method, block, elt)
		}
	case *ast.KeyValueExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD KEYYY VALLUEEEEE EXPR %v", e)
		saveCalls(service, method, block, e.Key)
		saveCalls(service, method, block, e.Value)
	case *ast.SelectorExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD SELECTOR EXPR %v", e)
		saveCalls(service, method, block, e.X)
	case *ast.Ident:
		logger.Logger.Infof("FFFOOOOUNNDDD IDENT %v", e)
	case *ast.TypeAssertExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD TYPE ASSERT EXPR %v", e)
	case *ast.BasicLit: // e.g. integers (1), strings ("foo"), etc
		logger.Logger.Infof("FFFOOOOUNNDDD BASIC LIT %v", e)
	default:
		logger.Logger.Fatalf("unknown type in saveCalls for type %s: %v", utils.GetType(e), e)
	}
}

func getReceiverIfValid(selectorExpr *ast.SelectorExpr, receiver *types.MethodField, block *types.Block) (*ast.Ident, variables.Variable, bool) {
	if recvIdent, ok := selectorExpr.X.(*ast.Ident); ok {
		// current method receiver
		if recvIdent.Name == receiver.GetName() {
			return recvIdent, nil, true
		}
		// an NoSQL collection from a previous field
		if variable := block.GetLastestVariable(recvIdent.Name); variable != nil {
			return recvIdent, variable, true
		}
	}
	return nil, nil, false
}

func getCallIfSelectedField(expr ast.Expr, receiver *types.MethodField, block *types.Block) (funcCall *ast.CallExpr, methodIdent *ast.Ident, fieldIdent *ast.Ident, serviceRecvIdent *ast.Ident, variable variables.Variable, ok bool) {
	if callExpr, ok := expr.(*ast.CallExpr); ok {
		// e.g. f.queue.Push
		//    ^ident2 ^ident ^method
		// e.g. f.storageService.StorePost
		//      ^ident2  ^ident    ^method
		if methodSel, ok := callExpr.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if fieldSel, ok := methodSel.X.(*ast.SelectorExpr); ok {
				if recvIdent, _, ok := getReceiverIfValid(fieldSel, receiver, block); ok && recvIdent != nil {
					return callExpr, methodSel.Sel, fieldSel.Sel, recvIdent, nil, true
				}
			} else if recvIdent, variable, ok := getReceiverIfValid(methodSel, receiver, block); ok {
				return callExpr, methodSel.Sel, nil, recvIdent, variable, true
			}
		}
	}
	return nil, nil, nil, nil, nil, false
}

func saveParsedFuncCallParams(service *service.Service, method *types.ParsedMethod, block *types.Block, parsedCall types.Call, args []ast.Expr) {
	for i, arg := range args {
		logger.Logger.Tracef("[CFG] inside save func call params")
		param := lookupVariableFromAstExpr(service, method, block, arg, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetType().(*gotypes.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("[CFG] upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetType().String())
		}
		parsedCall.AddParam(param)
	}
	logger.Logger.Infof("[CFG] added params to func call %s", parsedCall.String())
}

func getFuncCallDeps(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) []variables.Variable {
	var deps []variables.Variable
	for _, expr := range callExpr.Args {
		if v := lookupVariableFromAstExpr(service, method, block, expr, false); v != nil {
			deps = append(deps, v)
		}
	}
	return deps
}

func computeFuncCallReturnedTuple(service *service.Service, block *types.Block, callExpr *ast.CallExpr) *variables.TupleVariable {
	tupleType := &gotypes.TupleType{}
	tupleVar := &variables.TupleVariable{
		VariableInfo: &variables.VariableInfo{
			Type: tupleType,
			Id:   variables.VARIABLE_INLINE_ID,
		},
	}

	if signatureGoType, ok := service.GetPackage().GetTypeInfo(callExpr.Fun).(*golangtypes.Signature); ok {
		if signatureGoType.Results() != nil {
			signatureResults := lookup.ComputeTypesForGoTypes(service.GetPackage(), signatureGoType.Results())
			for _, t := range signatureResults.(*gotypes.TupleType).Types {
				newVar := lookup.CreateVariableFromType("", t)
				tupleVar.Variables = append(tupleVar.Variables, newVar)
				tupleType.Types = append(tupleType.Types, newVar.GetType())
			}
		}
	} else {
		logger.Logger.Fatalf("[CFG CALLS] unexpected type for imported method call %v", callExpr.Fun)
	}
	return tupleVar
}

func computeFuncCallReturnedTupleWithDeps(service *service.Service, block *types.Block, callExpr *ast.CallExpr, deps []variables.Variable) *variables.TupleVariable {
	tupleType := &gotypes.TupleType{}
	tupleVar := &variables.TupleVariable{
		VariableInfo: &variables.VariableInfo{
			Type: tupleType,
			Id:   variables.VARIABLE_INLINE_ID,
		},
	}

	if signatureGoType, ok := service.GetPackage().GetTypeInfo(callExpr.Fun).(*golangtypes.Signature); ok {
		if signatureGoType.Results() != nil {
			signatureResults := lookup.ComputeTypesForGoTypes(service.GetPackage(), signatureGoType.Results())
			for _, t := range signatureResults.(*gotypes.TupleType).Types {
				newVar := lookup.CreateVariableFromType("", t)
				compositeVar := &variables.CompositeVariable{
					VariableInfo: &variables.VariableInfo{
						Type: newVar.GetType(),
						Id:   variables.VARIABLE_UNASSIGNED_ID,
					},
					Params: deps,
				}
				tupleVar.Variables = append(tupleVar.Variables, compositeVar)
			}
		}
	} else {
		logger.Logger.Fatalf("[CFG CALLS] unexpected type for imported method call %v", callExpr.Fun)
	}
	return tupleVar
}

func getFuncCallReceiver(service *service.Service, callExpr *ast.CallExpr) (string, gotypes.Type) {
	if signatureGoType, ok := service.GetPackage().GetTypeInfo(callExpr.Fun).(*golangtypes.Signature); ok {
		if signatureGoType.Recv() != nil {
			return signatureGoType.Recv().Name(), lookup.ComputeTypesForGoTypes(service.GetPackage(), signatureGoType.Recv().Type())
		}
	} else {
		logger.Logger.Fatalf("[CFG CALLS] unexpected type for imported method call %v", callExpr.Fun)
	}
	return "", nil
}

func TODO_parseAndSaveCallIfValid(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) (types.Call, *variables.TupleVariable, bool) {
	idents, identsStr := lookup.GetAllSelectorIdents(callExpr.Fun)
	leftIdent := idents[0]
	funcIdent := idents[len(idents)-1]

	// (b1) call to variable (including receiver) in block
	if variable := block.GetLastestVariable(leftIdent.Name); variable != nil {
		if pointerVar, ok := variable.(*variables.PointerVariable); ok {
			variable = pointerVar.PointerTo
		}
		for i := 1; i < len(idents); i++ {
			ident := idents[i]
			if structVar, ok := variable.(*variables.StructVariable); ok {
				variable = structVar.GetFieldVariableIfExists(ident.Name)
				if variable == nil {
					fieldType := structVar.GetStructType().GetFieldTypeByNameIfExists(ident.Name)
					fieldVar := lookup.CreateVariableFromType(ident.Name, fieldType)
					structVar.AddFieldVariable(ident.Name, fieldVar)
				}
			} else if _, ok := variable.(*variables.ServiceVariable); ok {
				break
			} else if _, ok := variable.(*blueprint.BlueprintBackendVariable); ok {
				break
			} else {
				logger.Logger.Fatalf("[CFG CALLS] unexpected call for variable (%s) with type (%s)", variable.String(), utils.GetType(variable))
			}
		}
		if serviceVar, ok := variable.(*variables.ServiceVariable); ok {
			// store function call either as service call or database call
			// if the field corresponds to a service field
			// 1. extract the service field from the current service
			// 2. get the target service service for the type
			// 3. add the targeted method of the other service for the current call expression
			targetService := service.Services[serviceVar.GetServiceName()]
			targetMethod := targetService.ExportedMethods[funcIdent.Name]
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
			tupleVar := computeFuncCallReturnedTuple(service, block, callExpr)
			method.Calls = append(method.Calls, parsedCall)
			return parsedCall, tupleVar, true
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
			saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
			tupleVar := computeFuncCallReturnedTuple(service, block, callExpr)

			// maybe user is just getting the collection
			if blueprintBackendType.IsNoSQLDatabase() && blueprintMethod.ReturnsNoSQLCollection() {
				blueprintMethod.SetNoSQLDatabaseCollection(
					parsedCall.Params[1].GetType().GetBasicValue(),
					parsedCall.Params[2].GetType().GetBasicValue(),
					blueprintBackendType.DbInstance,
				)
				logger.Logger.Infof("[CFG CALLS] found blueprint backend call %s", parsedCall.Method.String())
			} else {
				method.Calls = append(method.Calls, parsedCall)
				logger.Logger.Infof("[CFG CALLS] found new database call %s", parsedCall.Name)
			}
			return parsedCall, tupleVar, true
		}
		logger.Logger.Fatalf("[TODO 2] found call to variable (%s) with type (%s) in call expr fun: %v", variable.String(), utils.GetType(variable), callExpr.Fun)
		return nil, nil, false
	}

	// (a) call to method in current package
	if method := service.GetPackage().GetParsedMethodIfExists(funcIdent.Name, ""); method != nil {
		// FIXME: calls within app should actually be parsed
		logger.Logger.Fatalf("[TODO 1] found method call %s", method.String())
		return nil, nil, false
	}

	//FIXME: this is a workaround to (a)
	receiverName, _ := getFuncCallReceiver(service, callExpr)
	if receiverName != "" {
		logger.Logger.Fatalf("GOT REceiver NAME %s", receiverName)
	}
	if funcDecl, ok := service.InternalMethods[funcIdent.Name]; ok && receiverName == service.ImplName {
		parsedCall := &types.ParsedInternalCall{
			ParsedCall: types.ParsedCall{
				Ast:    callExpr,
				Name:   funcIdent.Name,
				Method: funcDecl,
				Pos:    callExpr.Pos(),
			},
			ServiceTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
		}
		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		tupleVar := computeFuncCallReturnedTuple(service, block, callExpr)
		method.Calls = append(method.Calls, parsedCall)
		logger.Logger.Infof("[CFG CALLS] found new internal call %s", parsedCall.Name)
		return nil, tupleVar, true
	}

	// (d) call to method in imported package
	if impt, ok := service.File.Imports[leftIdent.Name]; ok {
		if pkg := service.GetPackage().GetImportedPackage(impt.PackagePath); pkg != nil {
			switch pkg.Type {
			case types.EXTERNAL, types.APP: // FIXME: everything in app should be parsed
				if deps := getFuncCallDeps(service, method, block, callExpr); deps != nil {
					tupleVar := computeFuncCallReturnedTupleWithDeps(service, block, callExpr, deps)
					return nil, tupleVar, true
				}
				tupleVar := computeFuncCallReturnedTuple(service, block, callExpr)
				return nil, tupleVar, true
			case types.BLUEPRINT:
				// ignore direct calls to blueprint package
				// we only care about backend calls to functions of well-defined interfaces (cache, queue, nosqldatabase)
				return nil, nil, false
			}
		}
	}
	logger.Logger.Fatalf("[TODO] unexpected call: %v", callExpr.Fun)
	return nil, nil, false
}

func parseAndSaveCallIfValid(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) (*variables.TupleVariable, bool) {
	_, tupleVar, ok := TODO_parseAndSaveCallIfValid(service, method, block, callExpr)
	if ok {
		logger.Logger.Infof("[CFG CALLS] returning tuple var %v", tupleVar.LongString())
		return tupleVar, ok
	}

	funcCall, methodIdent, fieldIdent, serviceRecvIdent, variable, ok := getCallIfSelectedField(callExpr, method.Receiver, block)
	if !ok {
		_, variable, ok := TODO_parseAndSaveCallIfValid(service, method, block, callExpr)
		if ok {
			logger.Logger.Infof("[CFG] found and parsed call %v with return %s", callExpr.Fun, variable.LongString())
		}
		return variable, ok
	}
	logger.Logger.Infof("[CFG] found and parsed call %v (method ident = %v, field ident = %v, service rcv ident = %v, variable = %v)", funcCall.Fun, methodIdent, fieldIdent, serviceRecvIdent, variable)

	if signatureGoType, ok := service.GetPackage().GetTypeInfo(callExpr.Fun).(*golangtypes.Signature); ok {
		if signatureGoType.Results() != nil {
			tupleType := &gotypes.TupleType{}
			tupleVar = &variables.TupleVariable{
				VariableInfo: &variables.VariableInfo{
					Type: tupleType,
					Id:   variables.VARIABLE_INLINE_ID,
				},
			}
			signatureResults := lookup.ComputeTypesForGoTypes(service.GetPackage(), signatureGoType.Results())
			for _, t := range signatureResults.(*gotypes.TupleType).Types {
				newVar := lookup.CreateVariableFromType("", t)
				tupleVar.Variables = append(tupleVar.Variables, newVar)
				tupleType.Types = append(tupleType.Types, newVar.GetType())
				block.AddVariable(newVar)
			}
		}
	}

	if fieldIdent != nil {
		// if the targeted variable corresponds to a service field
		if field, ok := service.Fields[fieldIdent.Name]; ok {
			if serviceField, ok := field.(*types.ServiceField); ok {
				// store function call either as service call or database call
				// if the field corresponds to a service field
				// 1. extract the service field from the current service
				// 2. get the target service service for the type
				// 3. add the targeted method of the other service for the current call expression
				targetServiceType := serviceField.GetTypeName()
				targetServiceNode := service.Services[targetServiceType]
				targetMethod := targetServiceNode.ExportedMethods[methodIdent.Name]
				parsedCall := &types.ParsedServiceCall{
					ParsedCall: types.ParsedCall{
						Ast:    funcCall,
						Name:   methodIdent.Name,
						Pos:    funcCall.Pos(),
						Method: targetMethod,
					},
					CallerTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
					CalleeTypeName: serviceField.GetType(),
				}
				saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
				method.Calls = append(method.Calls, parsedCall)
				logger.Logger.Infof("[CFG] found new service call %s @ %s", parsedCall.Name, method.Name)
				return nil, true
			} else if databaseField, ok := field.(*types.DatabaseField); ok {
				// if the field corresponds to a database field
				// 1. extract the service field from the current service
				// 2. get the target database service
				// 3. add the target method for the current call expression
				blueprintType := databaseField.FieldInfo.Type.(*blueprint.BlueprintBackendType)
				blueprintMethod := blueprintType.GetMethod(methodIdent.Name)
				parsedCall := &types.ParsedDatabaseCall{
					ParsedCall: types.ParsedCall{
						Ast:    funcCall,
						Name:   methodIdent.Name,
						Pos:    funcCall.Pos(),
						Method: blueprintMethod,
					},
					CallerTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
					DbInstance:     databaseField.DbInstance,
				}
				saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)

				// maybe user is just getting the collection
				if blueprintType.IsNoSQLDatabase() && blueprintMethod.ReturnsNoSQLCollection() {
					blueprintMethod.SetNoSQLDatabaseCollection(
						parsedCall.Params[1].GetType().GetBasicValue(),
						parsedCall.Params[2].GetType().GetBasicValue(),
						databaseField.DbInstance,
					)
					logger.Logger.Infof("[CFG] found blueprint backend call %s", parsedCall.Method.String())
				} else {
					method.Calls = append(method.Calls, parsedCall)
					logger.Logger.Infof("[CFG] found new database call %s", parsedCall.Name)
				}
				return tupleVar, true
			} else {
				logger.Logger.Fatalf("[CFG] unknown call %v for field %s with type %s", callExpr.Fun, field.String(), utils.GetType(field))
			}
		}
	} else if variable != nil {
		if blueprintBackendVar, ok := variable.(*blueprint.BlueprintBackendVariable); ok && blueprintBackendVar.IsNoSQLComponent() {
			blueprintType := blueprintBackendVar.VariableInfo.Type.(*blueprint.BlueprintBackendType)
			blueprintMethod := blueprintType.GetMethod(methodIdent.Name)
			parsedCall := &types.ParsedDatabaseCall{
				ParsedCall: types.ParsedCall{
					Ast:    funcCall,
					Name:   methodIdent.Name,
					Pos:    funcCall.Pos(),
					Method: blueprintMethod,
				},
				CallerTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
				DbInstance:     blueprintType.DbInstance,
			}
			if blueprintType.IsNoSQLCollection() {
				if blueprintMethod.ReturnsNoSQLCursor() {
					blueprintMethod.SetNoSQLDatabaseCursor(
						blueprintType.NoSQLComponent.Database,
						blueprintType.NoSQLComponent.Collection,
						blueprintType.DbInstance,
					)
				}
				saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
				method.Calls = append(method.Calls, parsedCall)
				logger.Logger.Infof("[CFG] found new database call %s", parsedCall.Method.String())
				return tupleVar, true
			}
		}
	}
	if funcDecl, ok := service.InternalMethods[methodIdent.Name]; ok {
		parsedCall := &types.ParsedInternalCall{
			ParsedCall: types.ParsedCall{
				Ast:    funcCall,
				Name:   methodIdent.Name,
				Method: funcDecl,
				Pos:    funcCall.Pos(),
			},
			ServiceTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
		}
		saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
		method.Calls = append(method.Calls, parsedCall)
		logger.Logger.Infof("[CFG] found new internal call %s", parsedCall.Name)
		return tupleVar, true
	}

	logger.Logger.Fatalf("[CFG] cannot save unknown call %v", callExpr.Fun)
	return nil, false
}
