package controlflow

import (
	"analyzer/pkg/analyzer"
	"analyzer/pkg/logger"
	"analyzer/pkg/models"
	"analyzer/pkg/service"
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"

	"golang.org/x/tools/go/cfg"
)

func ParseCFG(node *service.ServiceNode, method *service.ParsedFuncDecl) (*models.ParsedCFG, error) {
	basic_cfg, err := GenerateMethodCFG(method, node.Filepath)
	if err != nil {
		logger.Logger.Errorf("error generating CFG for target method %s in %s: %s\n", method.Name, node.Filepath, err.Error())
		return nil, err
	}
	if basic_cfg == nil {
		msg := fmt.Sprintf("basic cfg is nil for target method %s in %s\n", method.Name, node.Filepath)
		logger.Logger.Errorf(msg)
		return nil, fmt.Errorf(msg)
	}

	logger.Logger.Debug("generating parsed config")
	parsedCfg := &models.ParsedCFG{
		Cfg:        basic_cfg,
		BlocksInfo: make([]*models.BlockInfo, 0, len(basic_cfg.Blocks)),
		Vars:       make([]*analyzer.Variable, 0),
	}
	for _, info := range parsedCfg.BlocksInfo {
		info.Gen = make([]*analyzer.Variable, 0)
		info.In = make([]*analyzer.Variable, 0)
		info.Out = make([]*analyzer.Variable, 0)
	}
	pos := parsedCfg.Cfg.Blocks[0].Stmt.Pos()
	for i, param := range method.Params {
		parsedCfg.Vars = append(parsedCfg.Vars, &analyzer.Variable{
			//Id:     		len(parsedCfg.Vars),
			Id:            -1,
			Lineno:        pos,
			Name:          param.Name,
			Type: 		   param.Type,
			IsBlockParam:  true,
			BlockParamIdx: i + 1, // we are considering idexes > 0 due to the json representation
		})
	}
	logger.Logger.Debug("Variables")
	for _, v := range parsedCfg.Vars {
		logger.Logger.Debugf("\t%s [%d], ", v.Name, v.Lineno)
	}
	logger.Logger.Debugln()
	node.ParsedCFGs[method.Name] = parsedCfg
	return parsedCfg, nil

}

func GenerateMethodCFG(method *service.ParsedFuncDecl, filepath string) (*cfg.CFG, error) {
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
