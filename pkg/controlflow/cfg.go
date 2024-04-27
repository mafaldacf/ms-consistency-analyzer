package controlflow

import (
	log "analyzer/pkg/logger"
	"analyzer/pkg/models"
	"analyzer/pkg/service"
	"analyzer/pkg/analyzer"

	"golang.org/x/tools/go/cfg"
)

func GenParsedCfg(cfg *cfg.CFG, method *service.ParsedFuncDecl, filepath string) *models.ParsedCFG {
	log.Logger.Debug("generating parsed config")
	parsedCfg := models.ParsedCFG{
		Cfg:        cfg,
		BlocksInfo: make([]*models.BlockInfo, 0, len(cfg.Blocks)),
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
			Name:          param,
			IsBlockParam:  true,
			BlockParamIdx: i + 1, // we are considering idexes > 0 due to the json representation
		})
	}
	log.Logger.Debug("Variables")
	for _, v := range parsedCfg.Vars {
		log.Logger.Debugf("\t%s [%d], ", v.Name, v.Lineno)
	}
	log.Logger.Debugln()
	return &parsedCfg

}
