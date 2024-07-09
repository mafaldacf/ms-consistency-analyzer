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
			variable, _ := lookupVariableFromAstExpr(service, method, block, rvalue, true)

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
				//logger.Logger.Debugf("[CFG EXPR] matched left values (%v) to tuple variable (%v)", e.Lhs, tupleVariable.LongString())
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

func saveCalls(service *service.Service, method *types.ParsedMethod, block *types.Block, node ast.Node) {
	switch e := node.(type) {
	case *ast.CallExpr:
		parseAndSaveCall(service, method, block, e)
	case *ast.CompositeLit:
		// e.g. creating a structure where a field is obtained from a function call
		for _, elt := range e.Elts {
			saveCalls(service, method, block, elt)
		}
	case *ast.KeyValueExpr:
		saveCalls(service, method, block, e.Key)
		saveCalls(service, method, block, e.Value)
	case *ast.SelectorExpr:
		saveCalls(service, method, block, e.X)
	case *ast.Ident, *ast.TypeAssertExpr, *ast.BasicLit: // basic lit e.g. integers (1), strings ("foo"), etc
	default:
		logger.Logger.Fatalf("unknown type in saveCalls for type %s: %v", utils.GetType(e), e)
	}
}

func saveParsedFuncCallParams(service *service.Service, method *types.ParsedMethod, block *types.Block, parsedCall types.Call, args []ast.Expr) {
	for i, arg := range args {
		logger.Logger.Tracef("[CFG] inside save func call params")
		param, _ := lookupVariableFromAstExpr(service, method, block, arg, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetType().(*gotypes.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("[CFG] upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetType().String())
		}
		parsedCall.AddParam(param)
	}
	//logger.Logger.Debugf("[CFG] added params to func call %s", parsedCall.String())
}

func getFuncCallDeps(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) []variables.Variable {
	var deps []variables.Variable
	for _, expr := range callExpr.Args {
		logger.Logger.Warnf(">>>>>> LOOKING EXPR %s", expr)
		if v, _ := lookupVariableFromAstExpr(service, method, block, expr, false); v != nil {
			deps = append(deps, v)
		}
	}
	return deps
}

func computeFuncCallReturns(service *service.Service, callExpr *ast.CallExpr, call types.Call) *variables.TupleVariable {
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
				call.AddReturn(newVar)
			}
		}
	} else {
		logger.Logger.Fatalf("[CFG CALLS] unexpected type for imported method call %v", callExpr.Fun)
	}
	return tupleVar
}

func computeFuncCallReturnedTupleWithDeps(service *service.Service, callExpr *ast.CallExpr, deps []variables.Variable) *variables.TupleVariable {
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

// FIXME: this does not support nested calls!!!!
func parseAndSaveCall(service *service.Service, method *types.ParsedMethod, block *types.Block, callExpr *ast.CallExpr) variables.Variable {
	idents, identsStr := lookup.GetAllSelectorIdents(callExpr.Fun)
	leftIdent := idents[0]
	funcIdent := idents[len(idents)-1]

	var argVars []variables.Variable
	for i, expr := range callExpr.Args {
		v, _ := lookupVariableFromAstExpr(service, method, block, expr, false)
		logger.Logger.Debugf("[CFG CALLS] argument %d: (%s)", i, v.String())
		argVars = append(argVars, v)
	}

	//logger.Logger.Debugf("[CFG CALLS] ALL IDENTS: %s", identsStr)

	// (b1) call to variable (including receiver) in block
	var parsedCall types.Call
	if variable := block.GetLastestVariableIfExists(leftIdent.Name); variable != nil {
		logger.Logger.Debugf("[CFG CALLS] (1) call to variable: %s", variable.LongString())
		leftVariableTypeName := variable.GetType().GetName()
		if pointerVar, ok := variable.(*variables.PointerVariable); ok {
			//logger.Logger.Debugf("[CFG CALLS] (0) got pointer var (to %s): %s", utils.GetType(pointerVar.PointerTo.GetType()), pointerVar.String())
			variable = pointerVar.PointerTo
		}
		for i := 1; i < len(idents); i++ {
			ident := idents[i]
			if pointerVar, ok := variable.(*variables.PointerVariable); ok {
				//logger.Logger.Debugf("[CFG CALLS] (1) got pointer var (to %s): %s", utils.GetType(pointerVar.PointerTo.GetType()), pointerVar.String())
				variable = pointerVar.PointerTo
			}
			
			if _, ok := variable.GetType().(*gotypes.UserType); ok {
				if structVar, ok := variable.(*variables.StructVariable); ok {
					fieldName := ident.Name
					variable = structVar.GetFieldVariableIfExists(fieldName)
					if variable == nil {
						fieldType := structVar.GetStructType().GetFieldTypeByNameIfExists(fieldName)
						if fieldType != nil {
							fieldVar := lookup.CreateVariableFromType(fieldName, fieldType)
							structVar.AddFieldVariable(fieldName, fieldVar)
						} else {
							methodName := ident.Name
							pkgPath := structVar.GetStructType().GetMethodPackagePath(methodName)
							pkg := service.GetPackage().GetImportedPackage(pkgPath)
							parsedMethod := pkg.GetParsedMethod(methodName, leftVariableTypeName)
							//logger.Logger.Debugf("[CFG CALLS] got parsed method %s", parsedMethod.String())

							parsedCall = &types.ParsedInternalCall{
								ParsedCall: types.ParsedCall{
									Ast:    callExpr,
									Name:   parsedMethod.Name,
									Method: parsedMethod,
								},
								ServiceTypeName: &gotypes.ServiceType{Name: service.Name, Package: service.GetPackageName()},
							}
							saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
							method.Calls = append(method.Calls, parsedCall)
							variable = computeFuncCallReturns(service, callExpr, parsedCall)
							logger.Logger.Infof("[CFG CALLS] found internal call (%s) in package (%s) -- returned tuple: %s", parsedCall.GetName(), pkg.GetName(), variable.String())
						}
					}
				} else if interfaceVar, ok := variable.(*variables.StructVariable); ok {
					userType := variable.GetType().GetParentUserType()
					logger.Logger.Fatalf("[CFG CALLS] %s -- %s ", interfaceVar.String(), userType.String())
				} else if genericVar, ok := variable.(*variables.GenericVariable); ok {
					logger.Logger.Warnf("[CFG CALLS] ignoring generic var %s", genericVar.LongString())
					if deps := getFuncCallDeps(service, method, block, callExpr); deps != nil {
						tupleVar := computeFuncCallReturnedTupleWithDeps(service, callExpr, deps)
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
					tupleVar := computeFuncCallReturns(service, callExpr, parsedCall)
					return tupleVar
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
			tupleVar := computeFuncCallReturns(service, callExpr, parsedCall)
			method.Calls = append(method.Calls, parsedCall)
			logger.Logger.Infof("[CFG CALLS] found service call (%s) -- returned tuple: %s", parsedCall.Name, tupleVar.String())
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
				logger.Logger.Fatalf("unexpected nil db instance for backend type (%s)", blueprintBackendType.String())
			}

			saveParsedFuncCallParams(service, method, block, parsedCall, callExpr.Args)
			tupleVar := computeFuncCallReturns(service, callExpr, parsedCall)

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

	var callInPackage bool
	var callPkg *types.Package

	// (d) call to method in imported package
	if impt, ok := service.File.Imports[leftIdent.Name]; ok {
		if pkg := service.GetPackage().GetImportedPackage(impt.PackagePath); pkg != nil {
			switch pkg.Type {
			case types.EXTERNAL:
				if deps := getFuncCallDeps(service, method, block, callExpr); deps != nil {
					tupleVar := computeFuncCallReturnedTupleWithDeps(service, callExpr, deps)
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
				tupleVar := computeFuncCallReturns(service, callExpr, parsedCall)
				logger.Logger.Infof("[CFG CALLS] found call (%s) to method in imported external package (%s) -- returned tuple: %s", parsedCall.CallStr, impt.PackageName, tupleVar.String())
				return tupleVar
			case types.BLUEPRINT:
				// ignore direct calls to blueprint package
				// we only care about backend calls to functions of well-defined interfaces (cache, queue, nosqldatabase)
				return nil
			case types.APP:
				if parsedMethod := pkg.GetParsedMethodIfExists(funcIdent.Name, ""); parsedMethod != nil {
					callInPackage = true
					callPkg = pkg

				}
			}
		}
	}

	// (a) call to method in current package
	if parsedMethod := service.GetPackage().GetParsedMethodIfExists(funcIdent.Name, ""); parsedMethod != nil {
		callInPackage = true
		callPkg = service.GetPackage()
	}

	if callInPackage && callPkg != nil {
		if parsedMethod := callPkg.GetParsedMethodIfExists(funcIdent.Name, ""); method != nil {
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
			tupleVar := computeFuncCallReturns(service, callExpr, parsedCall)
			if callPkg == service.GetPackage() {
				method.Calls = append(method.Calls, parsedCall)
				logger.Logger.Infof("[CFG CALLS] found call (%s) to method in current package (%s) -- returned tuple: %s", parsedCall.CallStr, callPkg.Name, tupleVar.String())
			} else {
				logger.Logger.Infof("[CFG CALLS] found call (%s) to method in imported app package (%s) -- returned tuple: %s", parsedCall.CallStr, callPkg.Name, tupleVar.String())
				if deps := getFuncCallDeps(service, method, block, callExpr); deps != nil {
					tupleVar := computeFuncCallReturnedTupleWithDeps(service, callExpr, deps)
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
				tupleVar := computeFuncCallReturns(service, callExpr, parsedCall)
				return tupleVar
			}
			return tupleVar
		}
	}

	// can be a type declaration e.g. []byte()
	v, t := lookupVariableFromAstExpr(service, method, block, callExpr.Fun, false)
	if v != nil && t != nil {
		logger.Logger.Warnf("FIXME: ADD CONTENT TO VAR!!!!")
		return v
	}

	logger.Logger.Fatalf("[TODO] unexpected call: %v (call in package = %t, call pkg = %s) -- idents types = %v", callExpr.Fun, callInPackage, callPkg, idents)
	return nil
}
