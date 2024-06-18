package types

import (
	"go/ast"
	golangtypes "go/types"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

// -------------------------
// ------- AST TYPES -------
// -------------------------

func (file *File) ComputeTypeForAstExpr(typeExpr ast.Expr) gotypes.Type {
	switch e := typeExpr.(type) {
	case *ast.Ident:
		if utils.IsBasicType(e.Name) {
			return &gotypes.BasicType{
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
			logger.Logger.Warnf("FIXME: cannot compute type for selector expr (e.X type = %s): %s", utils.GetType(e.X), e)
			return nil

		}
		logger.Logger.Fatalf("cannot compute type for selector expr (e.X type = %s): %s", utils.GetType(e.X), e)
	case *ast.ChanType:
		return &gotypes.ChanType{
			ChanType: file.ComputeTypeForAstExpr(e.Value),
		}
	case *ast.MapType:
		return &gotypes.MapType{
			KeyType:   file.ComputeTypeForAstExpr(e.Key),
			ValueType: file.ComputeTypeForAstExpr(e.Value),
		}
	case *ast.InterfaceType:
		return &gotypes.InterfaceType{}
	case *ast.ArrayType:
		return &gotypes.ArrayType{
			ElementsType: file.ComputeTypeForAstExpr(e.Elt),
		}
	case *ast.StructType:
		structType := &gotypes.StructType{}
		for _, f := range e.Fields.List {
			if len(f.Names) != 1 {
				logger.Logger.Fatalf("unexpected number of fields (%d) for %s", len(f.Names), typeExpr)
			}
			name := f.Names[0].Name
            fieldType := &gotypes.FieldType{
				Origin:      structType,
				SubType:     file.ComputeTypeForAstExpr(f.Type),
				StructField: true,
				FieldName:   name,
				FieldTag:    f.Tag.Value,
			}
            if _, ok := fieldType.SubType.(*gotypes.StructType); ok {
                fieldType.SetEmbedded()
            }
            structType.AddFieldType(fieldType)
		}
		return structType
	}
	logger.Logger.Fatalf("could not compute type for expr %v (type = %s), pkg %s, importMap %v", typeExpr, utils.GetType(typeExpr), file.Package.Name, file.Imports)
	return nil
}

// ----------------------------
// ------- GOLANG TYPES -------
// ----------------------------

func (p *Package) ComputeTypesForGoTypes(goType golangtypes.Type) gotypes.Type {
	switch e := goType.(type) {
	case *golangtypes.Named:
		name := e.Obj().Name()
		path := ""
		if e.Obj().Pkg() != nil { // error never has an object
			path = e.Obj().Pkg().Path()
		}
		if namedType, ok := p.DeclaredTypes[name]; ok {
			return namedType
		}
		if serviceType, ok := p.ServiceTypes[name]; ok {
			return serviceType
		}
		if datastoreType, ok := p.DatastoreTypes[name]; ok {
			return datastoreType
		}
		if importedType, ok := p.ImportedTypes[importedTypeKey(path, name)]; ok {
			return importedType
		}
		logger.Logger.Fatalf("named type %s not declared in package %s", e.String(), p.String())
	case *golangtypes.Struct:
		structType := &gotypes.StructType{}
		for i := 0; i < e.NumFields(); i++ {
			f := e.Field(i)
			name := f.Name()
            fieldType := &gotypes.FieldType{
				Origin:      structType,
				SubType:     p.ComputeTypesForGoTypes(f.Type()),
				StructField: true,
				Embedded:    f.Embedded(),
				FieldName:   name,
				FieldTag:    e.Tag(i),
			}
			structType.AddFieldType(fieldType)
		}
		return structType
	case *golangtypes.Basic:
		return &gotypes.BasicType{
			Name: e.Name(),
		}
	case *golangtypes.Interface:
		return &gotypes.InterfaceType{
			Content: goType.String(),
		}
	case *golangtypes.Signature:
		signatureType := &gotypes.SignatureType{}
		for i := 0; i < e.Results().Len(); i++ {
			var v *golangtypes.Var = e.Results().At(i)
			signatureType.ReturnTypes = append(signatureType.ReturnTypes, p.ComputeTypesForGoTypes(v.Type()))
		}
		return signatureType
	case *golangtypes.Tuple:
		tupleType := &gotypes.TupleType{}
		for i := 0; i < e.Len(); i++ {
			var v *golangtypes.Var = e.At(i)
			tupleType.Types = append(tupleType.Types, p.ComputeTypesForGoTypes(v.Type()))
		}
		return tupleType
	default:
		if goType != nil {
			logger.Logger.Fatalf("unknown gotype %s for %v", utils.GetType(goType), goType)
		}
	}
	return nil
}
