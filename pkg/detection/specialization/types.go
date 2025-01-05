package specialization

import (
	"fmt"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
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

type mandatoryField struct {
	field        datastores.Field
	mandatoryRef datastores.Field
}

type RemovedMandatoryEntity struct {
	dbCall          *types.ParsedDatabaseCall
	mandatoryFields []*mandatoryField
}

func newMandatoryField(field datastores.Field, mandatoryRef datastores.Field) *mandatoryField {
	return &mandatoryField{
		field:        field,
		mandatoryRef: mandatoryRef,
	}
}

func newRemovedMandatoryEntity(dbCall *types.ParsedDatabaseCall, mandatoryFields []*mandatoryField) *RemovedMandatoryEntity {
	return &RemovedMandatoryEntity{
		dbCall:          dbCall,
		mandatoryFields: mandatoryFields,
	}
}

func (rme *RemovedMandatoryEntity) String() string {
	return fmt.Sprintf("%s \n\t@ %s", rme.dbCall.DbInstance.GetDatastore().Schema.GetRootUnfoldedField().GetFullName(), rme.dbCall.String())
}
