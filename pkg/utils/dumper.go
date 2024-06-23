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

	yamlStr := fixYamlStrings(string(yamlData))
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
func fixYamlStrings(yamlStr string) string {
	var sb strings.Builder
	inBraces := false   // { }
	inAngles := false   // < >
	inQuotes := false   // " " or ' '
	inParentheses := false // ( )

	for i, r := range yamlStr {
		if !inQuotes {
			switch r {
			// outside quotes: open braces
			case '{':
				inBraces = true
				sb.WriteRune(r)
				if i+1 < len(yamlStr) && !unicode.IsSpace(rune(yamlStr[i+1])) && yamlStr[i+1] != '{' && yamlStr[i+1] != '}' {
					sb.WriteRune(' ')
				}
				continue
			// outside quotes: close braces
			case '}':
				inBraces = false
				if sb.Len() > 0 && sb.String()[sb.Len()-1] != ' ' && sb.String()[sb.Len()-1] != '{' {
					sb.WriteRune(' ')
				}
				sb.WriteRune(r)
				continue
			// outside quotes: open angles
			case '<':
				inAngles = true
				sb.WriteRune(r)
				continue
			// outside quotes: close angles
			case '>':
				inAngles = false
				sb.WriteRune(r)
				continue
			// outside quotes: open parentheses
			case '(':
				inParentheses = true
				sb.WriteRune(r)
				continue
			// outside quotes: close parentheses
			case ')':
				inParentheses = false
				sb.WriteRune(r)
				continue
			// outside quotes: open quotes
			case '"', '\'':
				inQuotes = true
				sb.WriteRune(r)
				continue
			}
		} else {
			switch r {
			// inside quotes: close quotes
			case '"', '\'':
				inQuotes = false
			}
			sb.WriteRune(r)
			continue
		}

		if inBraces || inAngles || inParentheses {
			if r == '\n' {
				// replace newlines inside braces, angles, or parentheses with spaces
				sb.WriteRune(' ')
			} else if unicode.IsSpace(r) {
				// skip multiple spaces inside braces, angles, or parentheses
				if sb.Len() > 0 && sb.String()[sb.Len()-1] != ' ' {
					sb.WriteRune(' ')
				}
			} else {
				sb.WriteRune(r)
			}
		} else {
			sb.WriteRune(r)
		}
	}

	return sb.String()
}
