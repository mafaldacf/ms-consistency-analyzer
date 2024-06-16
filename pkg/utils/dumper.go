package utils

import (
	"fmt"
	"os"
	"strings"
	"unicode"

	"gopkg.in/yaml.v2"

	"analyzer/pkg/logger"
)

// -----------------------
// Yaml Formatting Helpers
// -----------------------

type OrderedProperties []map[string]interface{}
type OrderedPropertyList struct {
	// helper structure for saving properties while ordered
	// if we use a map (instead of a list entry with a single map)
	// then properties are ordered by their keys and not by insertion
	list OrderedProperties
}

func NewOrderedPropertyList() OrderedPropertyList {
	return OrderedPropertyList{}
}
func (lst *OrderedPropertyList) Result() OrderedProperties {
	return lst.list
}
func (lst *OrderedPropertyList) AddOrderedProperty(name string, prop interface{}) {
	fieldsMap := make(map[string]interface{})
	fieldsMap[name] = prop
	lst.list = append(lst.list, fieldsMap)
}

// -------
// Dumpers
// -------

func DumpToYamlFile(data interface{}, appname string, filename string) {
	yamlData, err := yaml.Marshal(data)
	if err != nil {
		logger.Logger.Fatalf("error marshalling yaml data")
	}

	yamlStr := fixBraces(string(yamlData))
	path := fmt.Sprintf("assets/%s/%s.yaml", appname, filename)
	err = os.WriteFile(path, []byte(yamlStr), 0644)
	if err != nil {
		logger.Logger.Fatalf("error writing yaml data to %s", path)
	}
}

// remove unwanted new lines within items with braces
// all of this still applies to nested braces
// ensure there is always a space between an open brace and next char or a prev char and close brace
// exception goes for when there is just "interface{}"", where we maintain the lack of space
func fixBraces(yamlStr string) string {
	var sb strings.Builder
	stack := []rune{}
	inBraces := false
	inQuotes := false

	for i, r := range yamlStr {
		if r == '{' && !inQuotes {
			inBraces = true
			stack = append(stack, r)
			
			sb.WriteRune(r)
			// ensure space after opening brace if next character is not a space, brace, or end of string
			if i+1 < len(yamlStr) && !unicode.IsSpace(rune(yamlStr[i+1])) && yamlStr[i+1] != '{' && yamlStr[i+1] != '}' {
				sb.WriteRune(' ')
			}
			continue
		} else if r == '}' && !inQuotes {
			if len(stack) > 0 {
				stack = stack[:len(stack)-1]
			}
			if len(stack) == 0 {
				inBraces = false
			}
			// ensure space before closing brace if previous character is not a space or opening brace
			if sb.Len() > 0 && sb.String()[sb.Len()-1] != ' ' && sb.String()[sb.Len()-1] != '{' {
				sb.WriteRune(' ')
			}
			sb.WriteRune(r)
			continue
		} else if r == '"' || r == '\'' {
			if inQuotes {
				if len(stack) > 0 && stack[len(stack)-1] == r {
					inQuotes = false
					stack = stack[:len(stack)-1]
				}
			} else {
				inQuotes = true
				stack = append(stack, r)
			}
		}

		if inBraces && r == '\n' {
			// replace newlines inside braces with spaces
			sb.WriteRune(' ')
		} else if inBraces && unicode.IsSpace(r) {
			// skip multiple spaces inside braces
			if sb.Len() > 0 && sb.String()[sb.Len()-1] != ' ' {
				sb.WriteRune(' ')
			}
		} else {
			sb.WriteRune(r)
		}
	}

	return sb.String()
}
