package abstractgraph

import (
	"encoding/json"
	"fmt"
	"os"

	"analyzer/pkg/logger"
)

func (graph *AbstractGraph) Dump() {
	// print in JSON format
	// https://omute.net/editor
	path := fmt.Sprintf("assets/%s/abstractgraph.json", graph.AppName)
	file, err := os.Create(path)
	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}
	defer file.Close()
	for _, node := range graph.Nodes {
		data, err := json.MarshalIndent(node, "", "  ")
		if err != nil {
			logger.Logger.Error("error marshaling json:", err)
			return
		}
		file.Write(data)
	}
	logger.Logger.Infof("[JSON] graph saved at %s", path)
}
