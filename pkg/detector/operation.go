package detector

import (
	"encoding/json"
	"fmt"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types/variables"
)

type Operation struct {
	ID        int
	LineageID int
	Service   string
	Method    string
	Key       variables.Variable
	Object    variables.Variable
	Database  datastores.DatabaseInstance
	Write     bool
}

func (op *Operation) MarshalJSON() ([]byte, error) {
	return json.Marshal(&struct {
		Service  string `json:"service"`
		Method   string `json:"method"`
		Key      string `json:"key"`
		Object   string `json:"object"`
		Database string `json:"database"`
	}{
		Service:  op.Service,
		Method:   op.Method,
		Key:      fmt.Sprintf("%s %s", op.Key.GetVariableInfo().GetName(), op.Key.GetVariableInfo().GetType().GetLongName()),
		Object:   fmt.Sprintf("%s %s", op.Object.GetVariableInfo().GetName(), op.Object.GetVariableInfo().GetType().GetLongName()),
		Database: fmt.Sprintf("%s %s", op.Database.GetName(), op.Database.GetTypeLongName()),
	})
}

func (op *Operation) String() string {
	if op.Key == nil {
		logger.Logger.Fatalf("nil key in %s", op.Method)
	}
	if op.Object == nil {
		logger.Logger.Fatalf("nil object in %s", op.Method)
	}
	opType := "write"
	if !op.Write {
		opType = "read"
	}
	return fmt.Sprintf("(%d, %d) %s(%s, %s, %s) @ %s",
		op.LineageID,
		op.ID,
		opType,
		op.Database.GetName(),
		op.Key.GetVariableInfo().GetName(),
		op.Object.GetVariableInfo().GetName(),
		op.Service,
	)
}
