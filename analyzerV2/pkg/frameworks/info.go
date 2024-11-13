package frameworks

import (
	"fmt"
	"go/ast"

	"analyzer/pkg/logger"
)

type ServiceInfo struct {
	Name            string
	Filepath        string
	PackageName     string
	PackagePath     string
	ConstructorName string
	ServiceArgs     []string
	Methods         []string
	Edges           []string
	AstInterface    *ast.InterfaceType
	AstConstructor  *ast.FuncType
}

func (info *ServiceInfo) String() string {
	return fmt.Sprintf("Name: %s, Filepath: %s, ConstructorName: %s, ServiceArgs: %v, Methods: %v", info.Name, info.Filepath, info.ConstructorName, info.ServiceArgs, info.Methods)
}

func (info *ServiceInfo) GetArgumentAt(idx int) string {
	if idx < len(info.ServiceArgs) {
		return info.ServiceArgs[idx]
	}
	logger.Logger.Fatalf("[SERVICE INFO] [%s] index %d out of bounds for service info with %d arguments: %v", info.Name, idx, len(info.ServiceArgs), info.ServiceArgs)
	return ""
}
