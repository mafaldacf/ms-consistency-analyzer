package types

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"go/ast"
)

func CreateTypeVariable(name string, t Type) Variable {
	switch e := t.(type) {
	case *UserType, *BasicType, *ChanType, *InterfaceType:
		return &CompositeVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
		}
	case *StructType:
		e.FieldTypes = make(map[string]Type)
		return &StructVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
			Fields: make(map[string]Variable),
		}
	case *MapType:
		return &MapVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
			KeyValues: make(map[Variable]Variable, 0),
		}
	case *ArrayType:
		return &ArrayVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
		}
	}
	logger.Logger.Fatalf("could not create variable %s for type %s", name, t)
	return nil
}

func ComputeType(typeExpr ast.Expr, file *File) Type {
	switch e := typeExpr.(type) {
	case *ast.Ident:
		if utils.IsBasicType(e.Name) {
			return &BasicType{
				Name: e.Name,
			}
		}
		if namedType, ok := file.Package.GetNamedType(e.Name); ok {
			return namedType
		}

		logger.Logger.Fatalf("cannot compute type for ident: %s", e)
	case *ast.SelectorExpr:
		if xIdent, ok := e.X.(*ast.Ident); ok {
			// e.X is the package alias
			if impt, ok := file.GetImport(xIdent.Name); ok {
				imptPath := impt.PackagePath
				// import path does not always match the object impt path
				// e.g. in "bson.D", the bson code actually defines "D" as "type D = primitive.D"
				// so instead of the original imported path go.mongodb.org/mongo-driver/bson.D
				// we have go.mongodb.org/mongo-driver/bson/primitive.D
				// can be either e.Sel or just e
				goType := file.Package.GetTypeInfo(e.Sel)
				if goType.String() != imptPath {
					logger.Logger.Warnf("replacing imported package path '%s' with go type path '%s'", imptPath, goType.String())
					imptPath = goType.String()
				}
				if importedType, ok := file.Package.GetImportedTypeFromPath(imptPath); ok {
					return importedType
				}
			}
			//TODO: user can be trying to select a field or something?
		}
		logger.Logger.Fatalf("cannot compute type for selector expr (e.X type = %s): %s", utils.GetType(e.X), e)
	case *ast.ChanType:
		return &ChanType{
			ChanType: ComputeType(e.Value, file),
		}
	case *ast.MapType:
		return &MapType{
			KeyType:   ComputeType(e.Key, file),
			ValueType: ComputeType(e.Value, file),
		}
	case *ast.InterfaceType:
		return &InterfaceType{}
	case *ast.ArrayType:
		return &ArrayType{
			ElementsType: ComputeType(e.Elt, file),
		}
	case *ast.StructType:
		return &StructType{
			// FIXME: struct type must not have a name, only a user type can have it
		}
	}
	logger.Logger.Fatalf("could not compute type for expr %v (type = %s), pkg %s, importMap %v", typeExpr, utils.GetType(typeExpr), file.Package.Name, file.Imports)
	return nil
}

func GetOrCreateVariableFromType(name string, t Type) Variable {
	info := &VariableInfo{
		Name: name,
		Type: t,
	}
	if name == "" {
		info.Id = VARIABLE_INLINE_ID
	} else {
		info.Id = VARIABLE_UNASSIGNED_ID
	}
	switch e := t.(type) {
	case *BasicType:
		return &BasicVariable{VariableInfo: info}
	case *ChanType:
		return &ChanVariable{VariableInfo: info}
	case *MapType:
		return &MapVariable{VariableInfo: info}
	case *InterfaceType:
		return &InterfaceVariable{VariableInfo: info}
	case *ArrayType:
		return &ArrayVariable{VariableInfo: info}
	case *StructType:
		// if we are here due to a recursive call (e.g. from UserType)
		// then we want to make sure we are not reseting the map
		if e.FieldTypes == nil {
			e.FieldTypes = make(map[string]Type)
		}
		return &StructVariable{
			VariableInfo: info,
			Fields:       make(map[string]Variable),
		}
	case *UserType:
		if e.UserType != nil {
			variable := GetOrCreateVariableFromType(name, e.UserType)
			variable.GetVariableInfo().Type = e
			return variable
		}
		// e.g. context.Context is nil
		return &GenericVariable{VariableInfo: info}
	case *ImportedType:
		return &GenericVariable{VariableInfo: info}
	}
	logger.Logger.Fatalf("could not create variable from type %v", t)
	return nil
}
