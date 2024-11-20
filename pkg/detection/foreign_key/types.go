package foreign_key

import (
	"fmt"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/types"
)

// --------------------
// FOREIGN KEY DETECTOR
// --------------------

type ForeignKeyDetector struct {
	app   *app.App
	graph *abstractgraph.AbstractGraph
	reads []*ForeignKeyRead
}

func (detector *ForeignKeyDetector) getGraph() *abstractgraph.AbstractGraph {
	return detector.graph
}

func (detector *ForeignKeyDetector) addForeignKeyRead(read *ForeignKeyRead) {
	detector.reads = append(detector.reads, read)
}

type ForeignKeyRead struct {
	refField     *datastores.Entry // field that is referencing
	originField  *datastores.Entry // field that is being referenced
	refDbCall    *types.ParsedDatabaseCall
	originDbCall *types.ParsedDatabaseCall
}

func newForeignKeyRead(refField *datastores.Entry, originField *datastores.Entry, refDbCall *types.ParsedDatabaseCall, originDbCall *types.ParsedDatabaseCall) *ForeignKeyRead {
	return &ForeignKeyRead{
		refField:        refField,
		originField:     originField,
		refDbCall:       refDbCall,
		originDbCall:    originDbCall,
	}
}

func (read *ForeignKeyRead) String() string {
	ref := fmt.Sprintf("- ref:\t%s\n\t@ %s", read.refField.GetFullName(), read.refDbCall.String())
	dst := fmt.Sprintf("- dst:\t%s\n\t@ %s", read.originField.GetFullName(), read.originDbCall.String())
	return ref + "\n" + dst
}
