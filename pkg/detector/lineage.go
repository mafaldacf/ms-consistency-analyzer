package detector

import "fmt"

type Lineage struct {
	ID         int          `json:"id"`
	Operations []*Operation `json:"operations"`
	Previous   *Lineage     `json:"-"`
}

func (l *Lineage) String() string {
	opsStr := "{"
	for i, op := range l.Operations {
		opsStr += op.String()
		if i < len(l.Operations)-1 {
			opsStr += ", "
		}
	}
	opsStr += "}"
	return fmt.Sprintf("lineage #%d operations = %s", l.ID, opsStr)
}

func (l *Lineage) AddOperation(op *Operation) {
	l.Operations = append(l.Operations, op)
}

func (l *Lineage) IsRoot() bool {
	return l.Previous == nil
}

func (l *Lineage) GetDependencies() []*Operation {
	var dependencies []*Operation
	// reverse - start from most recent
	for i := len(l.Operations) - 1; i >= 0; i-- {
		if l.Operations[i].Write {
			dependencies = append(dependencies, l.Operations[i])
		}
	}
	if !l.IsRoot() {
		dependencies = append(dependencies, l.Previous.GetDependencies()...)
	}
	return dependencies
}

