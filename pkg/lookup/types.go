package lookup

import (
	"strings"

	"analyzer/pkg/frameworks/blueprint"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/types/variables"
	"analyzer/pkg/utils"
)

func CreateVariableFromType(name string, t gotypes.Type) variables.Variable {
	info := &variables.VariableInfo{
		Name: name,
		Type: t,
		Id:   variables.VARIABLE_UNASSIGNED_ID,
	}
	if name == "" {
		info.Id = variables.VARIABLE_INLINE_ID
	}

	switch e := t.(type) {
	case *gotypes.UserType:
		if e.UserType != nil {
			underlyingVariable := CreateVariableFromType(name, e.UserType)
			e.UserType = underlyingVariable.GetType()
			underlyingVariable.GetVariableInfo().Type = e
			//logger.Logger.Warnf("[LOOKUP] returning user type variable (%s) with underlying type (%s)", underlyingVariable.String(), utils.GetType(underlyingVariable.GetType()))
			return underlyingVariable
		}
		// e.g. context.Context is nil
		logger.Logger.Warnf("[LOOKUP] user type (%s) with nil underlying type", e.String())
		return &variables.GenericVariable{VariableInfo: info}
	case *gotypes.ChanType:
		return &variables.ChanVariable{VariableInfo: info}
	case *gotypes.BasicType:
		return &variables.BasicVariable{VariableInfo: info}
	case *gotypes.InterfaceType:
		return &variables.InterfaceVariable{VariableInfo: info}
	case *gotypes.ArrayType:
		return &variables.ArrayVariable{VariableInfo: info}
	case *gotypes.AddressType:
		v := &variables.AddressVariable{
			VariableInfo: info, AddressOf: CreateVariableFromType("", e.AddressOf),
		}
		return v
	case *gotypes.PointerType:
		v := &variables.PointerVariable{
			VariableInfo: info, PointerTo: CreateVariableFromType("", e.PointerTo),
		}
		return v
	case *gotypes.StructType:
		return &variables.StructVariable{VariableInfo: info, Fields: make(map[string]variables.Variable)}
	case *gotypes.MapType:
		return &variables.MapVariable{VariableInfo: info, KeyValues: make(map[variables.Variable]variables.Variable, 0)}
	case *gotypes.FieldType:
		info.Name = e.FieldName
		return &variables.FieldVariable{
			VariableInfo: info,
			Underlying:   CreateVariableFromType(name, e.SubType),
		}
	case *blueprint.BlueprintBackendType:
		info.Type = e.DeepCopy()
		if e.IsNoSQLCollection() {
			// blueprint NoSQL type (blueprint.NoSQLCollectionType) is later assigned
			return &blueprint.BlueprintBackendVariable{VariableInfo: info}
		}
		if e.IsNoSQLCursor() {
			// blueprint NoSQL type (blueprint.NoSQLCursorType) is later assigned
			return &blueprint.BlueprintBackendVariable{VariableInfo: info}
		}
		return &blueprint.BlueprintBackendVariable{VariableInfo: info}
	case *gotypes.ServiceType:
		return &variables.ServiceVariable{VariableInfo: info}
	}
	logger.Logger.Fatalf("[LOOKUP] could not create variable with name (%s) for type (%v) (type = %s)", name, t, utils.GetType(t))
	return nil
}

func ParseImports(file *types.File) {
	for _, imp := range file.Ast.Imports {
		path := imp.Path.Value
		// remove quotes
		path = path[1 : len(path)-1]
		items := strings.Split(path, "/")
		pkgName := items[len(items)-1]

		// get alias
		// e.g. blueprintbackend in "github.com/blueprint-uservices/blueprint/runtime/core/backend"
		var alias string
		if imp.Name != nil {
			alias = imp.Name.Name
		} else {
			// if alias is not defined then we extract it as the last "member"
			alias = items[len(items)-1]
		}

		impt := &types.Import{
			Alias:      alias,
			ImportPath: path,
			//FIXME: dev can use a dummy path and replace with the original in the go.mod file
			PackagePath: path,
			PackageName: pkgName,
		}
		file.Imports[alias] = impt
	}
}
