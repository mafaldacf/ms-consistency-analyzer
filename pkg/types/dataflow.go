package types

import (
	"analyzer/pkg/datastores"
)

type Dataflow struct {
	DirectWrite    bool
	Datastore      string
	Service        string
	DirectVariable Variable
	IndirectSource Variable
}

func (df *Dataflow) GetVariable() Variable {
	if df.DirectWrite {
		return df.DirectVariable
	}
	return df.IndirectSource
}

func (df *Dataflow) GetDatastore() string{
	return df.Datastore
}

func (v *VariableInfo) SetDirectDataflow(datastore string, service string, variable Variable) {
	v.Dataflows = append(v.Dataflows, &Dataflow{
		DirectWrite:    true,
		DirectVariable: variable,
		Datastore:      datastore,
		Service:        service,
	})
}

func (v *VariableInfo) SetIndirectDataflow(source Variable) {
	for _, df := range source.GetVariableInfo().Dataflows {
		v.Dataflows = append(v.Dataflows, &Dataflow{
			IndirectSource: source,
			Datastore:      df.Datastore,
			Service:        df.Service,
		})
	}
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
