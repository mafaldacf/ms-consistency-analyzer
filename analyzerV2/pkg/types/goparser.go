package types

import (
	"fmt"
	"go/ast"
	golangtypes "go/types"
	"strings"

	"golang.org/x/tools/go/packages"

	"analyzer/pkg/logger"
	"analyzer/pkg/types/objects"
	"analyzer/pkg/utils"
)

func ParseGoType(pkg *Package, gotype golangtypes.Type, depth int) objects.Type {
	var padding string
	for i := 0; i < depth; i++ {
		padding += "-"
	}
	prefix := fmt.Sprintf("[TYPE] \t%s %s:", padding, strings.ToUpper(utils.GetType(gotype)))
	if gotype != nil {
		depth++
		logger.Logger.Warnf("%s %s", prefix, gotype.String())
		switch e := gotype.(type) {

		case *golangtypes.Basic:
			return objects.NewBasic(e.Name(), e.Kind(), e.Info())

		case *golangtypes.Named:
			named, exists := pkg.GetNamedTypeIfExists(e)
			if !exists {
				underlying := ParseGoType(pkg, e.Underlying(), depth)
				var pkgName, pkgPath string
				if e.Obj().Pkg() != nil {
					pkgName = e.Obj().Pkg().Name()
					pkgPath = e.Obj().Pkg().Path()
				}
				var external bool
				if pkgPath == "" || !strings.Contains(pkgPath, "github.com/blueprint-uservices/blueprint") {
					external = true
				}
				named = objects.NewNamed(e.Obj().Name(), pkgName, pkgPath, underlying, external)
				pkg.AddNamedType(e, named)
			}
			return named

		case *golangtypes.Pointer:
			elem := ParseGoType(pkg, e.Elem(), depth)
			return objects.NewPointer(elem)

		case *golangtypes.Chan:
			elem := ParseGoType(pkg, e.Elem(), depth)
			return objects.NewChan(elem, e.Dir())

		case *golangtypes.Map:
			key := ParseGoType(pkg, e.Key(), depth)
			elem := ParseGoType(pkg, e.Elem(), depth)
			return objects.NewMap(key, elem)

		case *golangtypes.Array:
			elem := ParseGoType(pkg, e.Elem(), depth)
			return objects.NewArray(elem, e.Len())

		case *golangtypes.Slice:
			elem := ParseGoType(pkg, e.Elem(), depth)
			return objects.NewSlice(elem)

		case *golangtypes.Struct:
			var fields []*objects.Variable
			var tags []string
			for i := 0; i < e.NumFields(); i++ {
				field := ParseGoObject(pkg, e.Field(i), depth)
				tag := e.Tag(i)
				fields = append(fields, field.(*objects.Variable))
				tags = append(tags, tag)
			}
			return objects.NewStruct(fields, tags)

		case *golangtypes.Interface:
			var methods []*objects.Func
			var embeddeds []objects.Type
			for i := 0; i < e.NumEmbeddeds(); i++ {
				embedded := ParseGoType(pkg, e.EmbeddedType(i), depth)
				embeddeds = append(embeddeds, embedded)
			}
			for i := 0; i < e.NumMethods(); i++ {
				method := ParseGoObject(pkg, e.Method(i), depth)
				methods = append(methods, method.(*objects.Func))
			}
			return objects.NewInterface(methods, embeddeds)

		case *golangtypes.Signature:
			var recv *objects.Variable

			if e.Recv() != nil {
				var isIface bool
				if named, ok := e.Recv().Type().(*golangtypes.Named); ok {
					if _, ok := named.Underlying().(*golangtypes.Interface); ok {
						isIface = true
					}
				}
				if !isIface || e.Recv().Embedded() {
					recv = ParseGoObject(pkg, e.Recv(), depth).(*objects.Variable)
				}
			}

			var paramsVars []*objects.Variable
			for i := 0; i < e.Params().Len(); i++ {
				paramVar := ParseGoObject(pkg, e.Params().At(i), depth)
				paramsVars = append(paramsVars, paramVar.(*objects.Variable))
			}

			var resultsVars []*objects.Variable
			for i := 0; i < e.Results().Len(); i++ {
				resultVar := ParseGoObject(pkg, e.Results().At(i), depth)
				resultsVars = append(resultsVars, resultVar.(*objects.Variable))
			}

			return objects.NewSignature(recv, objects.NewTuple(paramsVars), objects.NewTuple(resultsVars))

		default:
			logger.Logger.Fatalf("%s unexpected type for %s", prefix, e.String())
		}
	}
	return nil
}

func ParseGoObject(pkg *Package, obj golangtypes.Object, depth int) objects.Object {
	var padding string
	for i := 0; i < depth; i++ {
		padding += "-"
	}
	prefix := fmt.Sprintf("[OBJ] \t%s %s:", padding, strings.ToUpper(utils.GetType(obj)))
	if obj != nil {
		depth++
		logger.Logger.Infof("%s %s", prefix, obj.String())
		switch e := obj.(type) {
		case *golangtypes.Var:
			t := ParseGoType(pkg, e.Type(), depth)
			return objects.NewVariable(e.Name(), t)

		case *golangtypes.Const:
			t := ParseGoType(pkg, e.Type(), depth)
			return objects.NewConstant(e.Name(), t, e.Val())

		case *golangtypes.Func:
			t := ParseGoType(pkg, e.Type(), depth)
			return objects.NewFunc(e.Name(), t)

		case *golangtypes.TypeName:
			t := ParseGoType(pkg, e.Type(), depth)
			return objects.NewTypeName(e.Name(), t)

		case *golangtypes.PkgName:
			t := ParseGoType(pkg, e.Type(), depth)
			return objects.NewTypeName(e.Name(), t)

		default:
			logger.Logger.Fatalf("%s unexpected type for %s", prefix, e.String())
		}
	}
	return nil
}

func ParsePackageTypes(pkg *Package, goPackage *packages.Package) {
	if pkg.Name != "shopping_simple" {
		return
	}

	logger.Logger.Infof("[APP PACKAGE PARSER] parsing named types for app go package (%s)", goPackage)

	for _, obj := range goPackage.TypesInfo.Defs {
		if obj != nil {
			ParseGoObject(pkg, obj, 1)
		}
	}
	for i, t := range namedTypes {
		logger.Logger.Debugf("[NAMED %d] %s", i, t.String())
	}
	logger.Logger.Tracef("[APP PACKAGE PARSER] parsed named types app package %s", pkg.Name)
}

func (pkg *Package) SaveMethods() {
	for _, file := range pkg.GetFiles() {
		for _, decl := range file.Ast.Decls {
			if funcDecl, ok := decl.(*ast.FuncDecl); ok {
				goObj := pkg.GetTypeInfo(funcDecl.Name)
				object := ParseGoObject(pkg, goObj, 1)
				//ParseGoObject(obj, 1)
				method := NewMethod(funcDecl, object, pkg)
				pkg.AddMethod(method)
			}
		}
	}
}
