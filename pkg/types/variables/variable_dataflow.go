package variables

import (
	"fmt"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

type Dataflow struct {
	Datastore      string
	Service        string
	DirectWrite    bool
	Variable       Variable
	IndirectSource Variable
	Field          datastores.Field
}

func (df *Dataflow) String() string {
	if df.DirectWrite {
		return fmt.Sprintf("direct write <%s> @ (%s, %s)", df.Variable.String(), df.Service, df.Datastore)
	}
	return fmt.Sprintf("indirect write <%s> by <%s> @ (%s, %s)", df.Variable.String(), df.IndirectSource.String(), df.Service, df.Datastore)
}

func (df *Dataflow) DeepCopy() *Dataflow {
	return &Dataflow{
		Datastore:      df.Datastore,
		Service:        df.Service,
		DirectWrite:    df.DirectWrite,
		Variable:       df.Variable.DeepCopy(),
		IndirectSource: df.Variable.DeepCopy(),
		Field:          df.Field, //FIXME: deep copy
	}
}

func (df *Dataflow) ShortString() string {
	if df.DirectWrite {
		return fmt.Sprintf("write <%s (%s)>", df.Variable.String(), utils.GetType(df.Variable))
	}
	return fmt.Sprintf("write <%s (%s)> from <%s (%s)>", df.Variable.String(), utils.GetType(df.Variable), df.IndirectSource.String(), utils.GetType(df.IndirectSource))
}

func (df *Dataflow) GetVariable() Variable {
	if df.DirectWrite {
		return df.Variable
	}
	return df.IndirectSource
}

func (df *Dataflow) GetDatastore() string {
	return df.Datastore
}

func (v *VariableInfo) SetDirectDataflow(datastore string, service string, variable Variable, field datastores.Field) {
	df := &Dataflow{
		DirectWrite: true,
		Variable:    variable,
		Datastore:   datastore,
		Service:     service,
		Field:       field,
	}
	v.Dataflows = append(v.Dataflows, df)
	logger.Logger.Warnf("[DIRECT DATAFLOW %d] %s", variable.GetId(), df.ShortString())
}

func (v *VariableInfo) SetIndirectDataflow(datastore string, service string, current Variable, source Variable, field datastores.Field) {
	df := &Dataflow{
		Variable:       current,
		IndirectSource: source,
		Datastore:      datastore,
		Service:        service,
		Field:          field,
	}
	current.GetVariableInfo().IndirectDataflows = append(current.GetVariableInfo().IndirectDataflows, df)
	logger.Logger.Debugf("\t\t[INDIRECT DATAFLOW %d] %s", current.GetId(), df.ShortString())
	v.Dataflows = append(v.Dataflows, df)
}

func (v *VariableInfo) GetForeignDataflows(currentDS *datastores.Datastore) []*Dataflow {
	var dataflows []*Dataflow
	for _, df := range v.GetDataflows() {
		// only append if it a different datastore
		if df.Datastore != currentDS.Name {
			dataflows = append(dataflows, df)
		}
	}
	return dataflows
}
