package detector

import (
	"fmt"
	"strings"

	"analyzer/pkg/utils"
)

import (
	"gopkg.in/yaml.v2"
)

func (request *Request) MarshalYAML() ([]byte, error) {
	return yaml.Marshal(&struct {
		Mode                  string           `yaml:"detection_mode"`
		NumberInconsistencies int              `yaml:"number_inconsistencies"`
		Inconsistencies       []*Inconsistency `yaml:"xcy_inconsistencies"`
		Lineages              []*Lineage       `yaml:"lineages"`
	}{
		Mode:                  request.DetectionModeName(),
		NumberInconsistencies: len(request.Inconsistencies),
		Inconsistencies:       request.Inconsistencies,
		Lineages:              request.Lineages,
	})
}

func (request *Request) DumpToJSONFile(app string) {
	filename := fmt.Sprintf("detection/xcy_%s_%s_%s.json", strings.ToLower(request.DetectionModeName()), strings.ToLower(request.EntryNode.GetCallee()), strings.ToLower(request.EntryNode.GetName()))
	utils.DumpToJSONFile(request, app, filename)
}

func (operation *Operation) DumpYaml() map[string]interface{} {
	data := make(map[string]interface{})
	data["_repr"] = operation.String()
	data["service"] = operation.Service
	data["method"] = operation.Method
	data["key"] = fmt.Sprintf("%s %s", operation.Key.GetVariableInfo().GetName(), operation.Key.GetVariableInfo().GetType().GetLongName())
	data["object"] = fmt.Sprintf("%s %s", operation.Object.GetVariableInfo().GetName(), operation.Object.GetVariableInfo().GetType().GetLongName())
	data["datastore"] = fmt.Sprintf("%s %s", operation.Database.GetName(), operation.Database.GetTypeLongName())
	return data
}

func (inconsistency *Inconsistency) DumpYaml() map[string]interface{} {
	data := make(map[string]interface{})
	//data["write"] = inconsistency.Write.DumpYaml()
	//data["read"] = inconsistency.Read.DumpYaml()
    data["write"] = inconsistency.Write.String()
    data["read"] = inconsistency.Read.String()
	return data
}

func (lineage *Lineage) DumpYaml() map[string]interface{} {
	data := make(map[string]interface{})
    data["_id"] = lineage.ID
	var dataOperations []string
	for _, op := range lineage.Operations {
		dataOperations = append(dataOperations, op.String())
	}
	data["operations"] = dataOperations

	return data
}

func (request *Request) DumpYaml(includeLineages bool) map[string]interface{} {
	data := make(map[string]interface{})
	data["mode"] = request.DetectionModeName()
	data["number_inconsistencies"] = len(request.Inconsistencies)

	var dataInconsistencies []map[string]interface{}
	for i, inconsistency := range request.Inconsistencies {
        result := inconsistency.DumpYaml()
        result["_id"] = i
		dataInconsistencies = append(dataInconsistencies, result)
	}
	data["xcy_inconsistencies"] = dataInconsistencies

    if includeLineages {
        var dataLineages []map[string]interface{}
        for _, lineage := range request.Lineages {
            dataLineages = append(dataLineages, lineage.DumpYaml())
        }
        data["xcy_lineages"] = dataLineages
    }
    return data
}

func (request *Request) DumpToYAMLFile(app string) {
	filename := fmt.Sprintf("detection/%s_%s_xcy_%s.yaml", strings.ToLower(request.EntryNode.GetCallee()), strings.ToLower(request.EntryNode.GetName()), strings.ToLower(request.DetectionModeName()))
	data := request.DumpYaml(true)
	utils.DumpToYamlFile(data, app, filename)
}
