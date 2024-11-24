package xcy

import (
	"fmt"
	"os"
	"path/filepath"
	"slices"
	"strings"

	"gopkg.in/yaml.v2"

	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

func (detector *Detector) dumpOperationYaml(operation *Operation) map[string]interface{} {
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

func (detector *Detector) dumpInconsistencyYaml(inconsistency *Inconsistency) map[string]interface{} {
	data := make(map[string]interface{})
	data["write"] = inconsistency.Write.String()
	data["read"] = inconsistency.Read.String()
	if detector.HasDetectionMode(DEBUG_XCY_MISSING_DEPENDENCIES) { // include missing dependencies
		data["missing_dependency"] = inconsistency.MissingDependency
		data["visible_dependency_set"] = inconsistency.Read.GetVisibleDependenciesString()
	}
	return data
}

func (detector *Detector) dumpLineageYaml(request *Request, lineage *Lineage) map[string]interface{} {
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

func (detector *Detector) dumpRequestYaml(request *Request, includeLineages bool) map[string]interface{} {
	data := make(map[string]interface{})
	data["entry"] = detector.EntryNode.ShortString()
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

func (set *DetectorSet) Results() string {
	results := "------------------------------------------------------------\n"
	results += "----------------------- XCY ANALYSIS -----------------------\n"
	results += "------------------------------------------------------------\n"

	for _, detector := range set.detectors {
		if detector.HasInconsistencies() {
			for _, request := range detector.Requests {
				data, _ := yaml.Marshal(detector.dumpRequestYaml(request, false))
				results += string(data)
				results += "----------------------------------------------------------\n"
			}
		}
	}
	set.save(results)
	return results
}

func (set *DetectorSet) save(results string) {
	path := fmt.Sprintf("output/%s/analysis/xcy.txt", set.app.Name)

	dir := filepath.Dir(path)
	err := os.MkdirAll(dir, 0755)
	if err != nil {
		logger.Logger.Fatalf("[XCY] error creating directory %s: %s", dir, err.Error())
	}

	err = os.WriteFile(path, []byte(results), 0644)
	if err != nil {
		logger.Logger.Fatalf("[XCY] error writing data to %s: %s", path, err.Error())
	}
	logger.Logger.Tracef("[XCY] saved cascading detection results to %s", path)
}

func (set *DetectorSet) DumpYaml(results string) {
	for _, detector := range set.detectors {
		for _, request := range detector.Requests {
			filename := fmt.Sprintf("analysis/xcy/%s_%s_%s", strings.ToLower(request.EntryNode.GetCallee()), strings.ToLower(request.EntryNode.GetName()), strings.ToLower(detector.DetectionModeName()))
			data := detector.dumpRequestYaml(request, true)
			utils.DumpToYamlFile(data, set.app.Name, filename)
		}
	}
}
