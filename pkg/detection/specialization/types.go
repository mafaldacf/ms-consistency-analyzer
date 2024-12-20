package specialization

import (
	"fmt"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/types"
)

// -----------------------
// SPECIALIZATION DETECTOR
// -----------------------

type SpecializationDetector struct {
	app   *app.App
	graph *abstractgraph.AbstractGraph
	rmes  []*RemovedMandatoryEntity
}

func (detector *SpecializationDetector) getGraph() *abstractgraph.AbstractGraph {
	return detector.graph
}

func (detector *SpecializationDetector) addRemovedMandatoryEntity(rme *RemovedMandatoryEntity) {
	detector.rmes = append(detector.rmes, rme)
}

type RemovedMandatoryEntity struct {
	dbCall *types.ParsedDatabaseCall
}

func newRemovedMandatoryEntity(dbCall *types.ParsedDatabaseCall) *RemovedMandatoryEntity {
	return &RemovedMandatoryEntity{
		dbCall: dbCall,
	}
}

func (rme *RemovedMandatoryEntity) String() string {
	return fmt.Sprintf("%s \n\t@ %s", rme.dbCall.DbInstance.GetDatastore().Schema.GetRootUnfoldedField().GetFullName(), rme.dbCall.String())
}
