package foreign_key

import (
	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
)

// --------------------
// FOREIGN KEY DETECTOR
// --------------------

type ForeignKeyDetector struct {
	app   *app.App
	graph *abstractgraph.AbstractGraph
	reads []*ForeignKeyRead
}

func (detector *ForeignKeyDetector) getApp() *app.App {
	return detector.app
}

func (detector *ForeignKeyDetector) getGraph() *abstractgraph.AbstractGraph {
	return detector.graph
}

func (detector *ForeignKeyDetector) addForeignKeyRead(read *ForeignKeyRead) {
	detector.reads = append(detector.reads, read)
}

type ForeignKeyRead struct {
	originField *datastores.Entry // field that is being referenced
	refField *datastores.Entry // field that is referencing
}

func newForeignKeyRead(originField *datastores.Entry, refField *datastores.Entry) *ForeignKeyRead {
	return &ForeignKeyRead{
		originField: originField,
		refField: refField,
	}
}
