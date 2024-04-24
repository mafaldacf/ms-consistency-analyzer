package parser

import (
	"static_analyzer/logger"

	"static_analyzer/models"

	"golang.org/x/tools/go/cfg"
)

func GenParsedCfg(cfg *cfg.CFG, method *models.ParsedFuncDecl) *models.ParsedCFG {
	logger.Logger.Info("generating parsed config")
	parsedCfg := models.ParsedCFG{
		Cfg:        cfg,
		BlocksInfo: make([]*models.BlockInfo, 0, len(cfg.Blocks)),
		Vars:       make([]*models.Variable, 0),
	}
	for _, info := range parsedCfg.BlocksInfo {
		info.Gen = make([]*models.Variable, 0)
		info.In = make([]*models.Variable, 0)
		info.Out = make([]*models.Variable, 0)
	}

	pos := parsedCfg.Cfg.Blocks[0].Stmt.Pos()
	for _, param := range method.Params {
		parsedCfg.Vars = append(parsedCfg.Vars, &models.Variable{
			Id:     len(parsedCfg.Vars),
			Lineno: pos,
			Name:   param,
		})
	}
	logger.Logger.Debug("Variables")
	for _, v := range parsedCfg.Vars {
		logger.Logger.Debugf("\t%s [%d], ", v.Name, v.Lineno)
	}
	return &parsedCfg

}
