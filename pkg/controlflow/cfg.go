package controlflow

import (
	log "analyzer/pkg/logger"
	"analyzer/pkg/models"
	"analyzer/pkg/abstree"

	"golang.org/x/tools/go/cfg"
)


func GenParsedCfg(cfg *cfg.CFG, method *abstree.ParsedFuncDecl, filepath string) *models.ParsedCFG {
	log.Logger.Debug("generating parsed config")
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
	for i, param := range method.Params {
		parsedCfg.Vars = append(parsedCfg.Vars, &models.Variable{
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
