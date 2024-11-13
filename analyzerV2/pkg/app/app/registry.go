package app

import (
	"path/filepath"
	"slices"

	"golang.org/x/tools/go/packages"

	"analyzer/pkg/app/datastores"
	"analyzer/pkg/app/services"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
)

type packageGoInfo struct {
	Package   *types.Package
	GoPackage *packages.Package
}

func (app *App) registerPackages() {
	packagesPattern := app.PackagePath + "/..."
	pkgs, err := packages.Load(&packages.Config{Mode: packages.NeedName | packages.NeedModule | packages.NeedFiles | packages.NeedTypes | packages.NeedTypesInfo | packages.NeedSyntax | packages.NeedImports}, packagesPattern)
	if err != nil {
		logger.Logger.Fatalf("[APP PACKAGES] error loading packages from %s: %s", app.PackagePath, err.Error())
	}

	packagesInfo := make(map[string]*packageGoInfo)

	for _, goPackage := range pkgs {
		if _, exists := packagesInfo[goPackage.PkgPath]; !exists {
			packageInfo := app.saveNewPackageGoInfo(packagesInfo, goPackage)
			for k, imptgoPackage := range goPackage.Imports {
				importedPackageInfo, exists := packagesInfo[imptgoPackage.PkgPath]
				if !exists {
					importedPackageInfo = app.saveNewPackageGoInfo(packagesInfo, imptgoPackage)
				}
				packageInfo.Package.Imports[k] = importedPackageInfo.Package
				logger.Logger.Debugf("[APP PACKAGES] [%s] added import: %s", packageInfo.Package.GetName(), importedPackageInfo.Package.GetPath())
			}
		}
	}

	for _, pkg := range app.GetAppPackages() {
		pkg.SaveMethods()
	}
}

func (app *App) createPackage(goPkg *packages.Package) *types.Package {
	modulePath := ""
	if goPkg.Module != nil {
		modulePath = goPkg.Module.Path
	}

	pkg := types.NewPackage(goPkg.Name, goPkg.PkgPath, modulePath, goPkg.TypesInfo)
	for i, file := range goPkg.Syntax {
		pkg.Files = append(pkg.Files, &types.File{
			Ast:     file,
			Path:    goPkg.GoFiles[i],
			Name:    filepath.Base(goPkg.GoFiles[i]),
			Package: pkg,
		})
	}

	if goPkg.Name == "" {
		logger.Logger.Infof("[APP PACKAGE FINDER] found buil-in package %s", goPkg.String())
		pkg.Type = types.BUILTIN
	} else if utils.IsAppPackage(app.PackagePath, goPkg.PkgPath) {
		logger.Logger.Infof("[APP PACKAGE FINDER] found internal package %s", goPkg.String())
		pkg.Type = types.APP
	} else if utils.IsBlueprintBackendPath(goPkg.PkgPath) {
		logger.Logger.Infof("[APP PACKAGE FINDER] found blueprint package %s", goPkg.String())
		pkg.Type = types.BLUEPRINT
	} else {
		logger.Logger.Infof("[APP PACKAGE FINDER] found external package %s", goPkg.String())
		pkg.Type = types.EXTERNAL
	}
	app.AddPackage(pkg.Path, pkg)

	return pkg
}

func (app *App) saveNewPackageGoInfo(packagesInfo map[string]*packageGoInfo, goPkg *packages.Package) *packageGoInfo {
	pkg := app.createPackage(goPkg)
	packageInfo := &packageGoInfo{
		Package:   pkg,
		GoPackage: goPkg,
	}
	packagesInfo[goPkg.PkgPath] = packageInfo
	return packageInfo
}

func (app *App) registerDatastores(instances []*datastores.Datastore) {
	for _, instance := range instances {
		app.Datastores[instance.GetName()] = instance
		logger.Logger.Infof("[APP] registered datastore instance %s", instance.String())
	}
}

func (app *App) attachPackageMethodsToServices(servicesInfo map[string]*frameworks.ServiceInfo) {
	logger.Logger.Tracef("[APP] attaching app package methods to services")
	for _, pkg := range app.GetAppPackages() {
		for serviceName, service := range app.Services {
			if pkg.Equals(service.Package()) {
				for _, method := range pkg.Methods() {
					if method.Name() == service.ConstructorName() {
						logger.Logger.Debugf("[CONSTRUCTOR] [%s] attaching method (%s)", serviceName, method.Name())
						service.SetConstructor(method)
					} else if slices.Contains(servicesInfo[serviceName].Methods, method.Name()) {
						logger.Logger.Debugf("[METHOD] [%s] attaching method (%s)", serviceName, method.Name())
						service.AddMethod(method)
					}
				}
			}
		}
		
	}
}

func (app *App) registerServices(servicesInfo map[string]*frameworks.ServiceInfo) {
	logger.Logger.Tracef("[APP] loading #%d specs", len(servicesInfo))
	// services also include blueprint backends
	for _, info := range servicesInfo {
		pkg := app.GetPackage(info.PackagePath)
		service := services.NewService(info.Name, info.ConstructorName, pkg)
		app.Services[service.Name()] = service
		logger.Logger.Infof("[APP] created service node %s", service.Name())
	}

	for _, info := range servicesInfo {
		for _, edgeName := range info.Edges {
			service := app.GetService(info.Name)
			other := app.GetService(edgeName)
			service.AddService(edgeName, other)
		}
	}
	for _, info := range servicesInfo {
		for _, entity := range info.ServiceArgs {
			if !app.HasService(entity) && app.HasDatastore(entity) {
				service := app.GetService(info.Name)
				datastore := app.GetDatastore(entity)
				service.AddDatastore(entity, datastore)
			}
		}
	}
}
