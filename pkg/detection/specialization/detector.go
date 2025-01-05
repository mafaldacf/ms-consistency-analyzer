package specialization

import (
	"fmt"
	"os"
	"path/filepath"

	"analyzer/pkg/abstractgraph"
	"analyzer/pkg/app"
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

func NewDetector(app *app.App, graph *abstractgraph.AbstractGraph) *SpecializationDetector {
	return &SpecializationDetector{
		app:   app,
		graph: graph,
	}
}

func (detector *SpecializationDetector) Run() {
	detector.app.ResetAllDataflows()
	for requestIdx, entry := range detector.getGraph().Nodes {
		detector.analyzeNodes(entry.(*abstractgraph.AbstractServiceCall), entry, requestIdx)
		detector.app.ResetAllDataflows()
	}
}

func (detector *SpecializationDetector) schemaHasMandatoryField(datastore *datastores.Datastore) (bool, []*mandatoryField) {
	var mandatoryFields []*mandatoryField
	for _, field := range datastore.Schema.GetAllFields() {
		for _, mandatoryRef := range field.GetMandatoryReferences(){
			mandatoryFields = append(mandatoryFields, newMandatoryField(field, mandatoryRef))
		}
	}
	return len(mandatoryFields) > 0, mandatoryFields
}

func (detector *SpecializationDetector) analyzeNodes(lastServiceCallNode *abstractgraph.AbstractServiceCall, node abstractgraph.AbstractNode, requestIdx int) {
	if dbCall, ok := node.(*abstractgraph.AbstractDatabaseCall); ok {
		logger.Logger.Infof("[SPECIALIZATION] analyzing %s @ %s: %s", utils.GetType(dbCall), dbCall.DbInstance.GetName(), dbCall.String())
		datastore := dbCall.DbInstance.GetDatastore()
		/* params := dbCall.GetParams() */
		if /* dbCall.ParsedCall.Method.IsWrite() {
			switch datastore.Type {
			case datastores.Queue:
				msg := params[1]
				abstractgraph.TaintDataflowWrite(detector.app, msg, dbCall, datastore, "", true, requestIdx)
				
			case datastores.NoSQL:
				doc := params[1]
				abstractgraph.TaintDataflowWrite(detector.app, doc, dbCall, datastore, "", true, requestIdx)

			case datastores.Cache:
				key, value := params[1], params[2]
				abstractgraph.TaintDataflowWrite(detector.app, key, dbCall, datastore, datastores.ROOT_FIELD_NAME_CACHE_KEY, false, requestIdx)
				abstractgraph.TaintDataflowWrite(detector.app, value, dbCall, datastore, datastores.ROOT_FIELD_NAME_CACHE_VALUE, false, requestIdx)

			default:
				logger.Logger.Fatalf("[SPECIALIZATION > WRITE] TODO: %s", dbCall.String())
			}
		} else if */ dbCall.ParsedCall.Method.IsDelete() {
			switch datastore.Type {
			case datastores.NoSQL:
				/* doc := params[1]
				abstractgraph.TaintDataflowWrite(detector.app, doc, dbCall, datastore, "", true, requestIdx) */
				hasMandatoryFields, _ := detector.schemaHasMandatoryField(datastore)
				if hasMandatoryFields {
					detector.addRemovedMandatoryEntity(newRemovedMandatoryEntity(dbCall.ParsedCall, nil)) // FIXME: IN THE FUTURE, REPLACE NIL MANDATORY FIELDS
				}
			default:
				logger.Logger.Fatalf("[SPECIALIZATION > DELETE] TODO: %s", dbCall.String())
			}
		}
	}
	for _, child := range node.GetChildren() {
		detector.analyzeNodes(lastServiceCallNode, child, requestIdx)
	}
}

func (detector *SpecializationDetector) Results() string {
	results := "------------------------------------------------------------\n"
	results += "------------------ SPECIALIZATION ANALYSIS -----------------\n"
	results += "------------------------------------------------------------\n"
	if len(detector.rmes) > 0 {
		results += "removed mandatory entities:\n"
	}
	for i, rme := range detector.rmes {
		results += fmt.Sprintf("- (#%d) %s", i, rme.String())
		for _, mandatoryField := range rme.mandatoryFields { // AT THE MOMENT MANDATORY FIELDS IS ALWAYS NIL SO WE NEVER PRINT THIS
			results += fmt.Sprintf("\t\t %s REFERENCES %s * {MANDATORY}", mandatoryField.field.GetFullName(), mandatoryField.mandatoryRef.GetFullName())
		}
		if i < len(detector.rmes)-1 {
			results += "\n" // enforce empty line between each foreign key read result
		}
	}
	detector.save(results)
	return results
}

func (detector *SpecializationDetector) save(results string) {
	path := fmt.Sprintf("output/%s/analysis/specialization.txt", detector.app.Name)

	dir := filepath.Dir(path)
	err := os.MkdirAll(dir, 0755)
	if err != nil {
		logger.Logger.Fatalf("[SPECIALIZATION] error creating directory %s: %s", dir, err.Error())
	}

	err = os.WriteFile(path, []byte(results), 0644)
	if err != nil {
		logger.Logger.Fatalf("[SPECIALIZATION] error writing data to %s: %s", path, err.Error())
	}
	logger.Logger.Tracef("[SPECIALIZATION] saved cascading detection results to %s", path)
}
