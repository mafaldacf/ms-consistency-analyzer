package types

import (
	"fmt"
	golangtypes "go/types"
	"slices"
	"strings"

	"golang.org/x/tools/go/packages"

	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

var namedTypes []*golangtypes.Named

func CheckGoType(gotype golangtypes.Type, depth int) {
	var padding string
	for i := 0; i < depth; i++ {
		padding += "-"
	}
	prefix := fmt.Sprintf("[TYPE] \t%s %s:", padding, strings.ToUpper(utils.GetType(gotype)))
	if gotype != nil {
		depth++
		logger.Logger.Warnf("%s %s", prefix, gotype.String())
		switch e := gotype.(type) {
		case *golangtypes.Named:
			if !slices.Contains(namedTypes, e) {
				namedTypes = append(namedTypes, e)
				CheckGoType(e.Underlying(), depth)
			}

		case *golangtypes.Pointer:
			CheckGoType(e.Elem(), depth)

		case *golangtypes.Chan:
			CheckGoType(e.Elem(), depth)

		case *golangtypes.Map:
			CheckGoType(e.Key(), depth)
			CheckGoType(e.Elem(), depth)

		case *golangtypes.Array:
			CheckGoType(e.Elem(), depth)

		case *golangtypes.Slice:
			CheckGoType(e.Elem(), depth)

		case *golangtypes.Basic:

		case *golangtypes.Interface:
			for i := 0; i < e.NumEmbeddeds(); i++ {
				embedded := e.EmbeddedType(i)
				CheckGoType(embedded, depth)
			}
			for i := 0; i < e.NumExplicitMethods(); i++ {
				explicitMethod := e.ExplicitMethod(i)
				CheckGoObject(explicitMethod, depth)
			}
			for i := 0; i < e.NumMethods(); i++ {
				method := e.Method(i)
				CheckGoObject(method, depth)
			}

		case *golangtypes.Struct:
			for i := 0; i < e.NumFields(); i++ {
				field := e.Field(i)
				CheckGoObject(field, depth)
			}

		case *golangtypes.Signature:
			if e.Recv() != nil {
				var isIface bool
				if named, ok := e.Recv().Type().(*golangtypes.Named); ok {
					if _, ok := named.Underlying().(*golangtypes.Interface); ok {
						isIface = true
					}
				}
				if !isIface || e.Recv().Embedded() {
					CheckGoObject(e.Recv(), depth)
				}
			}
			for i := 0; i < e.Params().Len(); i++ {
				param := e.Params().At(i)
				CheckGoObject(param, depth)
			}
			for i := 0; i < e.Results().Len(); i++ {
				result := e.Results().At(i)
				CheckGoObject(result, depth)
			}

		default:
			logger.Logger.Fatalf("%s unexpected type for %s", prefix, e.String())
		}
	}
}

func CheckGoObject(obj golangtypes.Object, depth int) {
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
			CheckGoType(e.Type(), depth)

		case *golangtypes.Const:
			CheckGoType(e.Type(), depth)

		case *golangtypes.Func:
			CheckGoType(e.Type(), depth)

		case *golangtypes.TypeName:
			CheckGoType(e.Type(), depth)

		case *golangtypes.PkgName:
			CheckGoType(e.Type(), depth)

		default:
			logger.Logger.Fatalf("%s unexpected type for %s", prefix, e.String())
		}
	}
}

func CheckPackageTypes(pkg *Package, goPackage *packages.Package) {
	if pkg.Name != "shopping_simple" {
		return
	}

	logger.Logger.Infof("[APP PACKAGE PARSER] parsing named types for app go package (%s)", goPackage)

	for _, obj := range goPackage.TypesInfo.Defs {
		if obj != nil {
			CheckGoObject(obj, 1)
		}
	}
	for i, t := range namedTypes {
		logger.Logger.Debugf("[NAMED %d] %s", i, t.String())
	}
	logger.Logger.Tracef("[APP PACKAGE PARSER] parsed named types app package %s", pkg.Name)
}
