package controlflow

import (
	frameworks "analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"fmt"
	"go/ast"

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

func visitBasicBlock(node *service.ServiceNode, method *service.ParsedFuncDecl, parsedBlock *types.ParsedBlock, visited map[int32]bool) {
	if visited[parsedBlock.GetIndex()] {
		return
	}
	visited[parsedBlock.GetIndex()] = true
	for _, blockNode := range parsedBlock.GetNodes() {
		parseExpressions(node, method, parsedBlock, blockNode)
	}

	for _, succ := range parsedBlock.GetSuccs() {
		parsedSucc := method.ParsedCfg.GetParsedBlockAtIndex(succ.Index)
		parsedSucc.CopyVarsFromPredecessor(parsedBlock)
		visitBasicBlock(node, method, parsedSucc, visited)
	}
}

func saveCalls(service *service.ServiceNode, method *service.ParsedFuncDecl, parsedBlock *types.ParsedBlock, node ast.Node) {
	logger.Logger.Infof("---------- %v", utils.GetType(node))
	switch e := node.(type) {
	case *ast.CallExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD CALL EXPR %v", e)
		saveCallIfValid(service, method, parsedBlock, e)
	case *ast.CompositeLit:
		// e.g. creating a structure where a field is obtained from a function call
		logger.Logger.Infof("FFFOOOOUNNDDD COMPOSITE LITE %v", e)
		for _, elt := range e.Elts {
			saveCalls(service, method, parsedBlock, elt)
		}
	case *ast.KeyValueExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD KEYYY VALLUEEEEE EXPR %v", e)
		saveCalls(service, method, parsedBlock, e.Key)
		saveCalls(service, method, parsedBlock, e.Value)
	case *ast.SelectorExpr:
		logger.Logger.Infof("FFFOOOOUNNDDD SELECTOR EXPR %v", e)
		saveCalls(service, method, parsedBlock, e.X)
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

func saveCallIfValid(service *service.ServiceNode, method *service.ParsedFuncDecl, parsedBlock *types.ParsedBlock, callExpr *ast.CallExpr) bool {
	parsedCall := saveFuncCallIfValid(service, method, callExpr)
	if parsedCall == nil {
		return false
	}
	for i, arg := range callExpr.Args {
		param := getOrCreateVariable(service, method, parsedBlock, arg, false)

		// upgrade variable with known type from function method
		if _, ok := param.GetVariableInfo().Type.(*types.GenericType); ok {
			param.GetVariableInfo().Type = parsedCall.GetMethod().GetParams()[i].GetType()
			logger.Logger.Warnf("upgrading variable %s with new type %s", param.GetVariableInfo().Name, param.GetVariableInfo().Type.String())
		}
		parsedCall.AddParam(param)
	}
	logger.Logger.Infof("[CFG] found call %s", parsedCall.String())
	return true
}

func hasCurrentServiceRecvIdent(selectorExpr *ast.SelectorExpr, expectedRecvIdent *ast.Ident) (bool, *ast.Ident) {
	if serviceRecvIdent, ok := selectorExpr.X.(*ast.Ident); ok {
		if serviceRecvIdent.Name == expectedRecvIdent.Name {
			return true, serviceRecvIdent
		}
	}
	return false, nil
}

func getFuncCallIfSelectedServiceField(node ast.Node, expectedRecvIdent *ast.Ident) (ok bool, funcCall *ast.CallExpr, methodIdent *ast.Ident, fieldIdent *ast.Ident, serviceRecvIdent *ast.Ident) {
	// e.g. f.queue.Push
	//    ^ident2 ^ident ^method
	// e.g. f.storageService.StorePost
	//      ^ident2  ^ident    ^method
	if funcCall, ok := node.(*ast.CallExpr); ok {		
		if methodSel, ok := funcCall.Fun.(*ast.SelectorExpr); ok {
			// get first selector (e.g. storageService)
			if fieldSel, ok := methodSel.X.(*ast.SelectorExpr); ok {
				if ok, serviceRecvIdent := hasCurrentServiceRecvIdent(fieldSel, expectedRecvIdent); ok {
					return true, funcCall, methodSel.Sel, fieldSel.Sel, serviceRecvIdent
				}
			} else if ok, serviceRecvIdent := hasCurrentServiceRecvIdent(methodSel, expectedRecvIdent); ok {
				return true, funcCall, methodSel.Sel, nil, serviceRecvIdent
			}
		}
	}
	return false, nil, nil, nil, nil
}

func saveFuncCallIfValid(node *service.ServiceNode, method *service.ParsedFuncDecl, callExpr *ast.CallExpr) service.Call {
	ok, funcCall, methodIdent, fieldIdent, serviceRecvIdent := getFuncCallIfSelectedServiceField(callExpr, method.Recv)
	if !ok {
		return nil
	}
	if fieldIdent != nil {
		// if the targeted variable corresponds to a service field
		if field, ok := node.Fields[fieldIdent.Name]; ok {
			// store function call either as service call or database call
			// if the field corresponds to a service field
			if serviceField, ok := field.(*types.ServiceField); ok {
				// 1. extract the service field from the current service
				// 2. get the target node service for the type
				// 3. add the targeted method of the other service for the current call expression
				targetServiceType := serviceField.GetTypeName()
				targetServiceNode := node.Services[targetServiceType]
				targetMethod := targetServiceNode.ExposedMethods[methodIdent.Name]
				svcParsedCallExpr := &service.ServiceParsedCallExpr{
					ParsedCallExpr: service.ParsedCallExpr{
						Ast:         funcCall,
						Receiver:    serviceRecvIdent.Name,
						TargetField: fieldIdent.Name,
						Name:        methodIdent.Name,
						Pos:         funcCall.Pos(),
						Method:      targetMethod,
					},
					CallerTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
					CalleeTypeName: serviceField.GetType(),
				}
				method.Calls = append(method.Calls, svcParsedCallExpr)
				logger.Logger.Warnf("[CFG] found new service call %s", svcParsedCallExpr.Name)
				return svcParsedCallExpr
			}
			// if the field corresponds to a database field
			if databaseField, ok := field.(*types.DatabaseField); ok {
				// 1. extract the service field from the current service
				// 2. get the target database node
				// 3. add the target method for the current call expression
				targetDatabaseType := databaseField.GetTypeName()
				dbParsedCallExpr := &service.DatabaseParsedCallExpr{
					ParsedCallExpr: service.ParsedCallExpr{
						Ast:         funcCall,
						Receiver:    serviceRecvIdent.Name,
						TargetField: fieldIdent.Name,
						Name:        methodIdent.Name,
						Pos:         funcCall.Pos(),
						Method:      frameworks.GetBackendMethod(fmt.Sprintf("%s.%s", targetDatabaseType, methodIdent.Name)),
					},
					CallerTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
					DbInstance:     databaseField.DbInstance,
				}
				method.Calls = append(method.Calls, dbParsedCallExpr)
				logger.Logger.Warnf("[CFG] found new database call %s", dbParsedCallExpr.Name)
				return dbParsedCallExpr
			}
		}
	} else if funcDecl, ok := node.InternalMethods[methodIdent.Name]; ok {
		internalCall := &service.InternalTempParsedCallExpr{
			ParsedCallExpr: service.ParsedCallExpr{
				Ast:      funcCall,
				Receiver: serviceRecvIdent.Name,
				Name:     methodIdent.Name,
				Method:   funcDecl,
				Pos:      funcCall.Pos(),
			},
			ServiceTypeName: &types.ServiceType{Name: node.Name, Package: node.GetPackageName()},
		}
		method.Calls = append(method.Calls, internalCall)
		logger.Logger.Warnf("[CFG] found new internal call %s", internalCall.Name)
		return internalCall
	}
	return nil
}
