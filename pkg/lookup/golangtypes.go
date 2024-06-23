package lookup

import (
	golangtypes "go/types"

	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

func ComputeTypesForGoTypes(p *types.Package, goType golangtypes.Type) gotypes.Type {
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
		if importedType, ok := p.ImportedTypes[types.ImportedTypeKey(path, name)]; ok {
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
				SubType:     ComputeTypesForGoTypes(p, f.Type()),
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
			signatureType.ReturnTypes = append(signatureType.ReturnTypes, ComputeTypesForGoTypes(p, v.Type()))
		}
		return signatureType
	case *golangtypes.Tuple:
		tupleType := &gotypes.TupleType{}
		for i := 0; i < e.Len(); i++ {
			var v *golangtypes.Var = e.At(i)
			tupleType.Types = append(tupleType.Types, ComputeTypesForGoTypes(p, v.Type()))
		}
		return tupleType
	default:
		if goType != nil {
			logger.Logger.Fatalf("unknown gotype %s for %v", utils.GetType(goType), goType)
		}
	}
	return nil
}
