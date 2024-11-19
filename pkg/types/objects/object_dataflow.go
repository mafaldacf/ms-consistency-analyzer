package objects

import (
	"fmt"
	"strings"

	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

type Dataflow struct {
	Datastore      string
	Service        string
	Write          bool
	Direct         bool
	Variable       Object
	IndirectSource Object
	Field          datastores.Field
}

func (df *Dataflow) GetOpString() string {
	if df.Write {
		return "write"
	}
	return "read"
}

func (df *Dataflow) HasVariable(variable Object) bool {
	return df.Variable == variable
}

func (df *Dataflow) HasAnyVariable(variables []Object) bool {
	for _, v := range variables {
		if df.Variable == v {
			return true
		}
		if df.IndirectSource == v {
			return true
		}
	}
	return false
}

func (df *Dataflow) IsWriteOp() bool {
	return df.Write
}

func (df *Dataflow) IsOpInDatastore(datastore string) bool {
	return df.Datastore == datastore
}

func (df *Dataflow) String() string {
	prefix := fmt.Sprintf("%s %s", 
    	func() string { if df.Direct { return "direct" } else { return "indirect" } }(),
    	func() string { if df.Write { return "write" } else { return "read" } }(),
	)
	if df.Direct {
		return fmt.Sprintf("%s <%s> @ (%s, %s)", prefix, df.Variable.String(), df.Service, df.Datastore)
	}
	return fmt.Sprintf("%s <%s> by <%s> @ (%s, %s)", prefix, df.Variable.String(), df.IndirectSource.String(), df.Service, df.Datastore)
}

func (df *Dataflow) Copy(force bool) *Dataflow {
	return df
}

func (df *Dataflow) DeepCopy() *Dataflow {
	return df
}

func (df *Dataflow) ShortString() string {
	if df.Direct {
		return fmt.Sprintf("%s <%s (%s)>", df.GetOpString(), df.Variable.String(), utils.GetType(df.Variable))
	}
	return fmt.Sprintf("%s <%s (%s)> from <%s (%s)>", df.GetOpString(), df.Variable.String(), utils.GetType(df.Variable), df.IndirectSource.String(), utils.GetType(df.IndirectSource))
}

func (df *Dataflow) GetVariable() Object {
	if df.Direct {
		return df.Variable
	}
	return df.IndirectSource
}

func (df *Dataflow) GetDatastore() string {
	return df.Datastore
}

func (v *ObjectInfo) SetDirectDataflow(datastore string, service string, variable Object, field datastores.Field, write bool) *Dataflow {
	df := &Dataflow{
		Direct:    true,
		Variable:  variable,
		Datastore: datastore,
		Service:   service,
		Field:     field,
		Write:     write,
	}
	v.Dataflows = append(v.Dataflows, df)
	logger.Logger.Warnf("[DIRECT DATAFLOW - %s] (%d) %s", strings.ToUpper(df.GetOpString()), df.Variable.GetId(), df.Variable.String())
	return df
}

func (v *ObjectInfo) SetIndirectDataflow(datastore string, service string, current Object, source Object, field datastores.Field, write bool) *Dataflow {
	df := &Dataflow{
		Variable:       current,
		IndirectSource: source,
		Datastore:      datastore,
		Service:        service,
		Field:          field,
		Write:          write,
	}
	current.GetVariableInfo().IndirectDataflows = append(current.GetVariableInfo().IndirectDataflows, df)
	v.Dataflows = append(v.Dataflows, df)
	logger.Logger.Warnf("\t\t[INDIRECT DATAFLOW - %s] (%d) %s", strings.ToUpper(df.GetOpString()), df.Variable.GetId(), df.Variable.String())
	return df
}

func (v *ObjectInfo) GetForeignDataflows(currentDS *datastores.Datastore) []*Dataflow {
	var dataflows []*Dataflow
	for _, df := range v.GetDataflows() {
		// only append if it a different datastore
		if df.Datastore != currentDS.Name {
			dataflows = append(dataflows, df)
		}
	}
	return dataflows
}
