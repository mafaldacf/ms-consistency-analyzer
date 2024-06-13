package types

import "fmt"

type ServiceInfo struct {
	Name 			string
	Filepath 		string
	PackageName 	string
	ConstructorName string
	// maps the parameters in constructors to the corresponding database instance name passed in the wiring
	ConstructorDBs	map[string]string
	Methods 		[]string
	Edges 		    []string
}

func (si *ServiceInfo) String() string {
	return fmt.Sprintf("Name: %s, Filepath: %s, ConstructorName: %s, ConstructorDBs: %v, Methods: %v", si.Name, si.Filepath, si.ConstructorName, si.ConstructorDBs, si.Methods)
}
