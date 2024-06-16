package types

import (
	"go/ast"

	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

// ---------------------
// -------- File -------
// ---------------------
type File struct {
	Ast     *ast.File
	Package *Package
	Name    string
	AbsPath string
	Imports map[string]*Import // key is the alias of the import
}

func (f *File) GetImport(alias string) (*Import, bool) {
	impt, ok := f.Imports[alias]
	return impt, ok
}

func (f *File) String() string {
	return f.AbsPath
}

// ---------------------
// ------- Types -------
// ---------------------

func (file *File) ComputeTypeForExpr(typeExpr ast.Expr) Type {
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
			ChanType: file.ComputeTypeForExpr(e.Value),
		}
	case *ast.MapType:
		return &MapType{
			KeyType:   file.ComputeTypeForExpr(e.Key),
			ValueType: file.ComputeTypeForExpr(e.Value),
		}
	case *ast.InterfaceType:
		return &InterfaceType{}
	case *ast.ArrayType:
		return &ArrayType{
			ElementsType: file.ComputeTypeForExpr(e.Elt),
		}
	case *ast.StructType:
		structType := &StructType{
			FieldTypes: make(map[string]Type),
		}
		for _, f := range e.Fields.List {
			name := f.Names[0].Name
			structType.FieldTypes[name] = file.ComputeTypeForExpr(f.Type)
			structType.FieldNames = append(structType.FieldNames, name)
		}
		return structType
	}
	logger.Logger.Fatalf("could not compute type for expr %v (type = %s), pkg %s, importMap %v", typeExpr, utils.GetType(typeExpr), file.Package.Name, file.Imports)
	return nil
}
