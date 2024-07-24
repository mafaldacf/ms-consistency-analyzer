package lookup

import (
	golangtypes "go/types"

	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

const (
	PACKAGE_PATH_POST_NOTIFICATION string = "github.com/blueprint-uservices/blueprint/examples/postnotification/workflow/postnotification"
	PACKAGE_PATH_FOOBAR            string = "github.com/blueprint-uservices/blueprint/examples/foobar/workflow/foobar"
	PACKAGE_PATH_SOCKSHOP          string = "github.com/blueprint-uservices/blueprint/examples/sockshop/workflow"
	PACKAGE_PATH_TRAIN_TICKET      string = "github.com/blueprint-uservices/blueprint/examples/train_ticket/workflow"
	PACKAGE_PATH_BLUEPRINT         string = "github.com/blueprint-uservices/blueprint/runtime/core/backend"
)

func isBlueprintPackagePath(name string) bool {
	return name == PACKAGE_PATH_BLUEPRINT
}

func getEmbeddedGolangNamedTypeIfExists(goType golangtypes.Type) (*golangtypes.Named, bool) {
	namedGoType, ok := goType.(*golangtypes.Named)
	stop := false
	for !stop {
		switch e := goType.(type) {
		case *golangtypes.Slice:
			goType = e.Elem()
		case *golangtypes.Pointer:
			goType = e.Elem()
		case *golangtypes.Chan:
			goType = e.Elem()
		case *golangtypes.Named:
			namedGoType = e
			ok = true
			stop = true
		case *golangtypes.Signature, *golangtypes.Struct, *golangtypes.Basic, *golangtypes.Map:
			// ignore
			stop = true
		default:
			logger.Logger.Fatalf("unknown go type (%s) for (%v)", utils.GetType(goType), goType)
		}
	}
	return namedGoType, ok
}

func FindDefTypesAndAddToPackage(pkg *types.Package, goType golangtypes.Type, visitedNamedTypes map[*golangtypes.Named]bool, typeNameToFuncs map[string][]*golangtypes.Func, servicesPkgPath map[string]string) gotypes.Type {
	namedGoType, ok := getEmbeddedGolangNamedTypeIfExists(goType)
	if !ok {
		logger.Logger.Tracef("[APP GOTYPES] skipping %v with type %s", goType, utils.GetType(goType))
		return nil
	}

	if visitedNamedTypes != nil {
		if visitedNamedTypes[namedGoType] {
			return nil
		}
		visitedNamedTypes[namedGoType] = true
	}

	logger.Logger.Tracef("[APP GOTYPES] [%s] %s", utils.GetType(namedGoType), namedGoType)

	typeName := namedGoType.Obj().Name()
	objectPackage := namedGoType.Obj().Pkg()
	objectPackagePath := ""

	// built-in (e.g. error, make, println) golang types have no package
	if objectPackage != nil {
		objectPackagePath = objectPackage.Path()
	}

	if pkg.IsAppPackage() {
		// different package implies imported object
		if !pkg.HasPath(objectPackagePath) {
			if isBlueprintPackagePath(objectPackagePath) {
				bpPackage := pkg.GetImportedPackage(objectPackagePath)
				declaredType := bpPackage.GetDeclaredType(typeName)
				pkg.AddImportedType(declaredType)
				pkg.AddDatastoreType(declaredType)

				logger.Logger.Infof("[APP GOTYPES] added imported blueprint type (%s)", declaredType.String())
				return declaredType
			} else if servicePkgPath, ok := servicesPkgPath[typeName]; ok && servicePkgPath == objectPackagePath {
				serviceType := &gotypes.ServiceType{
					Name:    typeName,
					Package: objectPackagePath,
				}
				pkg.AddImportedType(serviceType)
				pkg.AddServiceType(serviceType)

				logger.Logger.Infof("[APP GOTYPES] added imported service type (%s)", serviceType.String())
				return serviceType
			} else {
				userType := &gotypes.UserType{
					Name:    typeName,
					Package: objectPackagePath, // this is the real package name
				}
				pkg.AddImportedType(userType)

				userType.UserType = ComputeTypesForGoTypes(pkg, namedGoType.Underlying(), true, visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
				addMethodsIfStructOrInterface(userType, namedGoType)
				logger.Logger.Infof("[APP GOTYPES] added imported user type (%s)", userType.String())
				return userType
			}
		} else if servicePkgPath, ok := servicesPkgPath[typeName]; ok && servicePkgPath == objectPackagePath {
			serviceType := &gotypes.ServiceType{
				Name:    typeName,
				Package: objectPackagePath,
			}
			pkg.AddDeclaredType(serviceType)
			pkg.AddServiceType(serviceType)
			logger.Logger.Infof("[APP GOTYPES] added declared service type (%s)", serviceType.String())
			return serviceType
		} else {
			// new type defined in the current package
			userType := &gotypes.UserType{
				Name:    typeName,
				Package: pkg.Name,
			}
			// since we can have nested structures with definitions out of order
			// there, here we only add an entry and latter we generate the subtypes
			pkg.AddDeclaredType(userType)

			userType.UserType = ComputeTypesForGoTypes(pkg, namedGoType.Underlying(), true, visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
			addMethodsIfStructOrInterface(userType, namedGoType)
			logger.Logger.Infof("[APP GOTYPES] added declared named type (%s)", userType.String())
			return userType
		}
	} else if pkg.HasPath(objectPackagePath) {
		// new type defined in the current package
		userType := &gotypes.UserType{
			Name:    typeName,
			Package: pkg.Name,
		}
		// since we can have nested structures with definitions out of order
		// there, here we only add an entry and latter we generate the subtypes
		pkg.AddDeclaredType(userType)

		userType.UserType = ComputeTypesForGoTypes(pkg, namedGoType.Underlying(), true, visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
		addMethodsIfStructOrInterface(userType, namedGoType)
		logger.Logger.Infof("[APP GOTYPES] added declared named type %s", userType.String())
		return userType
	}
	return nil
}

func getPkgPathForGolangFuncType(funcType *golangtypes.Func) string {
	path := ""
	if funcType.Pkg() != nil { // e.g. "error" never has an object
		path = funcType.Pkg().Path()
	}
	return path
}

func addMethodsIfStructOrInterface(userType *gotypes.UserType, namedGoType *golangtypes.Named) {

	switch e := userType.UserType.(type) {
	case *gotypes.StructType:
		// in struct types, methods are directly defined for the named type
		for i := 0; i < namedGoType.NumMethods(); i++ {
			funcType := namedGoType.Method(i)
			funcTypePkgPath := getPkgPathForGolangFuncType(funcType)
			e.AddMethod(funcType.Name(), funcTypePkgPath)
			logger.Logger.Debugf("[COMPUTE GOTYPES STRUCT] saved struct function %s.%s(...) in package (%s)", userType.GetName(), funcType.Name(), funcTypePkgPath)
		}
	case *gotypes.InterfaceType:
		// in interface types, methods are defined for the underlying type of the named type
		for i := 0; i < namedGoType.Underlying().(*golangtypes.Interface).NumMethods(); i++ {
			funcType := namedGoType.Underlying().(*golangtypes.Interface).Method(i)
			funcTypePkgPath := getPkgPathForGolangFuncType(funcType)
			e.AddMethod(funcType.Name(), funcTypePkgPath)
			logger.Logger.Debugf("[COMPUTE GOTYPES STRUCT] saved interface function %s.%s(...) in package (%s)", userType.GetName(), funcType.Name(), funcTypePkgPath)
		}
	}
}

func LookupTypesForGoTypes(p *types.Package, goType golangtypes.Type) gotypes.Type {
	return ComputeTypesForGoTypes(p, goType, false, nil, nil, nil)
}

func LookupAndComputeTypesForGoTypes(p *types.Package, goType golangtypes.Type) gotypes.Type {
	// note that variable can be either inline and thus we need to compute if type not found
	// in case of declarations with assignments, we don't reach this function
	// e.g. inline "bson.D{{"id", payment.ID}}" in coll.FindOne(ctx, bson.D{{"id", payment.ID}})
	return ComputeTypesForGoTypes(p, goType, true, nil, nil, nil)
}

// + Compute
func ComputeTypesForGoTypes(p *types.Package, goType golangtypes.Type, computeIfNotFound bool, visitedNamedTypes map[*golangtypes.Named]bool, typeNameToFuncs map[string][]*golangtypes.Func, servicesPkgPath map[string]string) gotypes.Type {
	logger.Logger.Tracef("[LOOKUP GOTYPES] [%s] %v", utils.GetType(goType), goType)
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

		if computeIfNotFound {
			return FindDefTypesAndAddToPackage(p, e, visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
		}
	case *golangtypes.Struct:
		structType := &gotypes.StructType{Methods: make(map[string]string)}
		for i := 0; i < e.NumFields(); i++ {
			f := e.Field(i)
			name := f.Name()
			fieldType := &gotypes.FieldType{
				Origin:      structType,
				WrappedType: ComputeTypesForGoTypes(p, f.Type(), computeIfNotFound, visitedNamedTypes, typeNameToFuncs, servicesPkgPath),
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
			Methods: make(map[string]string),
		}
	case *golangtypes.Signature:
		signatureType := &gotypes.SignatureType{}
		for i := 0; i < e.Results().Len(); i++ {
			var v *golangtypes.Var = e.Results().At(i)
			signatureType.ReturnTypes = append(signatureType.ReturnTypes, ComputeTypesForGoTypes(p, v.Type(), computeIfNotFound, visitedNamedTypes, typeNameToFuncs, servicesPkgPath))
		}
		return signatureType
	case *golangtypes.Tuple:
		tupleType := &gotypes.TupleType{}
		for i := 0; i < e.Len(); i++ {
			var v *golangtypes.Var = e.At(i)
			tupleType.Types = append(tupleType.Types, ComputeTypesForGoTypes(p, v.Type(), computeIfNotFound, visitedNamedTypes, typeNameToFuncs, servicesPkgPath))
		}
		return tupleType
	case *golangtypes.Slice:
		sliceType := &gotypes.SliceType{}
		sliceType.UnderlyingType = ComputeTypesForGoTypes(p, e.Elem(), computeIfNotFound, visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
		return sliceType
	case *golangtypes.Pointer:
		pointerType := &gotypes.PointerType{}
		pointerType.PointerTo = ComputeTypesForGoTypes(p, e.Elem(), computeIfNotFound, visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
		return pointerType
	case *golangtypes.Chan:
		chanType := &gotypes.ChanType{}
		chanType.ChanType = ComputeTypesForGoTypes(p, e.Elem(), computeIfNotFound, visitedNamedTypes, typeNameToFuncs, servicesPkgPath)
		return chanType
	default:
		if goType != nil {
			logger.Logger.Fatalf("unknown gotype %s for %v", utils.GetType(goType), goType)
		}
	}
	logger.Logger.Fatalf("unknown gotype (%s) for %v", utils.GetType(goType), goType)
	return nil
}
