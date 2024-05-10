package controlflow

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/service"
	"analyzer/pkg/types"
	"go/ast"
	"go/parser"
	"go/token"

	"golang.org/x/tools/go/cfg"
)

func ParseCFG(node *service.ServiceNode, method *service.ParsedFuncDecl) (*types.ParsedCFG, error) {
	basicCfg, err := GenerateBasicCFG(method, node.Filepath)
	if err != nil {
		logger.Logger.Errorf("error generating CFG for target method %s in %s: %s\n", method.Name, node.Filepath, err.Error())
		return nil, err
	}
	parsedCfg := BuildParsedCFG(node, basicCfg, method)
	return parsedCfg, nil
}

func BuildParsedCFG(node *service.ServiceNode, basicCfg *cfg.CFG, method *service.ParsedFuncDecl) *types.ParsedCFG {
	logger.Logger.Debug("generating parsed config")
	parsedCfg := &types.ParsedCFG{
		Cfg:        basicCfg,
		BlocksInfo: make([]*types.BlockInfo, 0, len(basicCfg.Blocks)),
		Vars:       make([]*types.Variable, 0),
		FullMethod: 	method.String(),
	}
	for _, info := range parsedCfg.BlocksInfo {
		info.Gen = make([]*types.Variable, 0)
		info.In = make([]*types.Variable, 0)
		info.Out = make([]*types.Variable, 0)
	}
	pos := parsedCfg.Cfg.Blocks[0].Stmt.Pos()
	for i, param := range method.Params {
		parsedCfg.Vars = append(parsedCfg.Vars, &types.Variable{
			Id:            types.VARIABLE_UNASSIGNED_ID,
			Lineno:        pos,
			Name:          param.Name,
			Type:          param.Type,
			IsBlockParam:  true,
			BlockParamIdx: i,
		})
	}
	logger.Logger.Debug("Variables")
	for _, v := range parsedCfg.Vars {
		logger.Logger.Debugf("PARSED CFG VARS \t%s [%d], ", v.Name, v.Lineno)
	}
	logger.Logger.Debugln()
	node.ParsedCFGs[method.Name] = parsedCfg
	return parsedCfg
}

func GenerateBasicCFG(method *service.ParsedFuncDecl, filepath string) (*cfg.CFG, error) {
	fset := token.NewFileSet()
	file, err := parser.ParseFile(fset, filepath, nil, 0)
	if err != nil {
		logger.Logger.Error(err)
		return nil, err
	}

	for _, decl := range file.Decls {
		if funcDecl, ok := decl.(*ast.FuncDecl); ok {
			if funcDecl.Name.Name == method.Name && funcDecl.Body != nil {
				return cfg.New(funcDecl.Body, mayReturn), nil
			}
		}
	}
	return nil, nil
}

// https://github.com/coder/go-tools/blob/master/go/analysis/passes/ctrlflow/ctrlflow_test.go
func mayReturn(call *ast.CallExpr) bool {
	switch fun := call.Fun.(type) {
	case *ast.Ident:
		return fun.Name != "panic"
	case *ast.SelectorExpr:
		return fun.Sel.Name != "Fatal"
	}
	return true
}
