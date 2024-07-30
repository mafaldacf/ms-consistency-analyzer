package detection

import (
	"fmt"
	"slices"
	"strings"

	"gopkg.in/yaml.v2"

	"analyzer/pkg/detection/xcy"
	"analyzer/pkg/utils"
)

func (detector *Detector) dumpOperationYaml(operation *xcy.Operation) map[string]interface{} {
	data := make(map[string]interface{})
	data["_operation"] = operation.String()
	data["visible_dependency_set"] = operation.GetVisibleDependenciesString()

	if detector.HasDetectionMode(DEBUG_XCY_MINIMIZE_DEPENDENCIES) && operation.Write {
		lenVisible := len(operation.GetVisibleDependencies())
		lenMinimized := len(operation.GetMinimizedDependencySet())
		data[fmt.Sprintf("minimized_dependency_set (%d --> %d)", lenVisible, lenMinimized)] = operation.GetMinimizedDependencySetString()
	}
	return data
}

func (detector *Detector) dumpInconsistencyYaml(inconsistency *xcy.Inconsistency) map[string]interface{} {
	data := make(map[string]interface{})
	data["write"] = inconsistency.Write.String()
	data["read"] = inconsistency.Read.String()
	if detector.HasDetectionMode(DEBUG_XCY_MISSING_DEPENDENCIES) { // include missing dependencies
		data["missing_dependency"] = inconsistency.MissingDependency
		data["visible_dependency_set"] = inconsistency.Read.GetVisibleDependenciesString()
	}
	return data
}

func (detector *Detector) dumpLineageYaml(request *xcy.Request, lineage *xcy.Lineage) map[string]interface{} {
	data := make(map[string]interface{})
	data["_id"] = lineage.ID
	var dataOperations []interface{}
	for _, op := range lineage.GetOperations() {
		if detector.HasDetectionMode(DEBUG_LINEAGES) || detector.HasDetectionMode(DEBUG_XCY_MINIMIZE_DEPENDENCIES) { // include visible dependencies
			dataOperations = append(dataOperations, detector.dumpOperationYaml(op))
		} else {
			dataOperations = append(dataOperations, op.String())
		}
	}
	data["_operations"] = dataOperations

	if detector.HasDetectionMode(DEBUG_LINEAGES) {
		var dataDependencies []string
		lineageDependencies := lineage.GetDependenciesByMostRecent()
		for _, op := range lineageDependencies {
			dataDependencies = append(dataDependencies, op.String())
		}
		data["lineage_dependencies"] = dataDependencies

		var dataMissingDependencies []string
		allReqOps := request.Operations
		if len(lineage.Operations) > 0 {
			firstLineageOp := lineage.Operations[0]
			for _, op := range allReqOps {
				if op.LineageID < firstLineageOp.LineageID && !slices.Contains(lineageDependencies, op) {
					dataMissingDependencies = append(dataMissingDependencies, op.String())
				}
			}
		}
		data["missing_dependencies"] = dataMissingDependencies
	}

	return data
}

func (detector *Detector) dumpRequestYaml(request *xcy.Request, includeLineages bool) map[string]interface{} {
	data := make(map[string]interface{})
	data["mode"] = detector.DetectionModeName()
	data["number_inconsistencies"] = len(request.Inconsistencies)

	var dataInconsistencies []map[string]interface{}
	for _, inconsistency := range request.Inconsistencies {
		result := detector.dumpInconsistencyYaml(inconsistency)
		//result["number"] = i+1
		dataInconsistencies = append(dataInconsistencies, result)
	}
	data["xcy_inconsistencies"] = dataInconsistencies

	if includeLineages {
		var dataLineages []map[string]interface{}
		for _, lineage := range request.Lineages {
			dataLineages = append(dataLineages, detector.dumpLineageYaml(request, lineage))
		}
		data["xcy_lineages"] = dataLineages
	}
	return data
}

func (detector *Detector) PrintResults() {
	for _, request := range detector.Requests {
		if len(request.Inconsistencies) > 0 {
			data, _ := yaml.Marshal(detector.dumpRequestYaml(request, false))
			fmt.Println(string(data))
			fmt.Println("----------------------------------------------------------")
		}
	}
}

func (detector *Detector) DumpYaml(app string) {
	for _, request := range detector.Requests {
		filename := fmt.Sprintf("detection/%s_%s_%s", strings.ToLower(request.EntryNode.GetCallee()), strings.ToLower(request.EntryNode.GetName()), strings.ToLower(detector.DetectionModeName()))
		data := detector.dumpRequestYaml(request, true)
		utils.DumpToYamlFile(data, app, filename)
	}
}
