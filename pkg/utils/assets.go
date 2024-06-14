package utils

import (
	"analyzer/pkg/logger"
	"fmt"
	"os"
	"regexp"

	"gopkg.in/yaml.v2"
)

func SaveToYamlFile(data interface{}, appname string, filename string){
	yamlData, err := yaml.Marshal(data)
	if err != nil {
		logger.Logger.Fatalf("error marshalling yaml data")
	}

	// remove unwanted new lines within items of struct types
	yamlStr := string(yamlData)
	// \{[^\{\}]* matches the opening brace { and all chars until the new line
	// \n\s+ matches the unwanted new line and spaces
	// [^\{\}]*\} matches all chars up to the closing brace }
	// $1 $2 replaces the matched new lines with a space, combining the content within the braces into a single line
	re := regexp.MustCompile(`(\{[^\{\}]*)\n\s+([^\{\}]*\})`)
	for {
		newYamlStr := re.ReplaceAllString(yamlStr, "$1 $2")
		if newYamlStr == yamlStr {
			break
		}
		yamlStr = newYamlStr
	}
	// \{[^\{\}]* matches the opening brace { and all chars until the new line
	// \n\s+ matches the unwanted new line and spaces
	// [^\{\}]*\} matches all chars up to the closing brace }
	// $1 $2 replaces the matched new lines with a space, combining the content within the braces into a single line
	re = regexp.MustCompile(`(\([^\(\)]*)\n\s+([^\(\)]*\))`)
	for {
		newYamlStr := re.ReplaceAllString(yamlStr, "$1 $2")
		if newYamlStr == yamlStr {
			break
		}
		yamlStr = newYamlStr
	}


	path := fmt.Sprintf("assets/%s/%s.yaml", appname, filename)
	err = os.WriteFile(path, []byte(yamlStr), 0644)
	if err != nil {
		logger.Logger.Fatalf("error writing yaml data to %s", path)
	}
}
