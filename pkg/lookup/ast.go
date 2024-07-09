package lookup

import (
	"go/ast"

	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/types/gotypes"
	"analyzer/pkg/utils"
)

func GetAllSelectorIdents(expr ast.Expr) ([]*ast.Ident, string) {
	if callExpr, ok := expr.(*ast.CallExpr); ok {
		return GetAllSelectorIdents(callExpr.Fun)
	}
	if selectorExpr, ok := expr.(*ast.SelectorExpr); ok {
		r1, r2 := GetAllSelectorIdents(selectorExpr.X)
		return append(r1, selectorExpr.Sel), r2 + "." + selectorExpr.Sel.Name
	}
	if arrayType, ok := expr.(*ast.ArrayType); ok {
		expr = arrayType.Elt
	}
	if ident, ok := expr.(*ast.Ident); ok {
		return []*ast.Ident{ident}, ident.Name
	}
	logger.Logger.Fatalf("[LOOKUP SELECTOR IDENTS] unexpected expression %v (type = %s)", expr, utils.GetType(expr))
	return nil, ""
}

func ComputeTypeForAstExpr(file *types.File, typeExpr ast.Expr) gotypes.Type {
	switch e := typeExpr.(type) {
	case *ast.Ident:
		if utils.IsBasicType(e.Name) {
			return &gotypes.BasicType{
				Name: e.Name,
			}
		}
		if namedType, ok := file.Package.GetNamedType(e.Name); ok {
			//logger.Logger.Debugf("[LOOKUP AST IDENT] got named type (%s) (type = %s)", namedType.String(), utils.GetType(namedType))
			return namedType
		}

		logger.Logger.Fatalf("[LOOKUP AST IDENT] cannot compute type for ident (%s)", e)
	case *ast.SelectorExpr:
		idents, _ := GetAllSelectorIdents(e.X)
		leftIdent := idents[0]

		//logger.Logger.Debugf("HERE WITH EXPR %v", e)
		
		// left ident is the package alias
		imptPath := file.GetImport(leftIdent.Name).PackagePath
		// import path does not always match the object impt path
		// e.g. in "bson.D", the bson code actually defines "D" as "type D = primitive.D"
		// so instead of the original imported path go.mongodb.org/mongo-driver/bson.D
		// we have go.mongodb.org/mongo-driver/bson/primitive.D
		// can be either e.Sel or just e
		goType := file.Package.GetTypeInfo(e.Sel)
		if goType.String() != imptPath {
			logger.Logger.Warnf("[LOOKUP AST SELECTOR] replacing imported package path (%s) with go type path (%s)", imptPath, goType.String())
			imptPath = goType.String()
		}
		if importedType, ok := file.Package.GetImportedTypeFromPath(imptPath); ok {
			return importedType
		} else {
			logger.Logger.Fatalf("[LOOKUP AST SELECTOR] unexpected nil import type for path (%s)", imptPath)
		}
		
		logger.Logger.Fatalf("[LOOKUP AST SELECTOR] cannot parse selector expr (%v)", e)
		return nil
	case *ast.ChanType:
		return &gotypes.ChanType{
			ChanType: ComputeTypeForAstExpr(file, e.Value),
		}
	case *ast.MapType:
		return &gotypes.MapType{
			KeyType:   ComputeTypeForAstExpr(file, e.Key),
			ValueType: ComputeTypeForAstExpr(file, e.Value),
		}
	case *ast.InterfaceType:
		return &gotypes.InterfaceType{Methods: make(map[string]string)}
	case *ast.ArrayType:
		return &gotypes.ArrayType{
			ElementsType: ComputeTypeForAstExpr(file, e.Elt),
		}
	case *ast.StructType:
		structType := &gotypes.StructType{Methods: make(map[string]string)}
		for _, f := range e.Fields.List {
			if len(f.Names) != 1 {
				logger.Logger.Fatalf("[LOOKUP AST STRUCT] unexpected number of fields (%d) for %s", len(f.Names), typeExpr)
			}
			name := f.Names[0].Name
			fieldType := &gotypes.FieldType{
				Origin:      structType,
				SubType:     ComputeTypeForAstExpr(file, f.Type),
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
	case *ast.StarExpr:
		return &gotypes.PointerType{
			PointerTo: ComputeTypeForAstExpr(file, e.X),
		}
	}
	logger.Logger.Fatalf("[LOOKUP AST] could not compute type for expr %v (type = %s) \n\npkg: %s \n\nimportMap: %v", typeExpr, utils.GetType(typeExpr), file.Package.Name, file.Imports)
	return nil
}

func ComputeFuncDeclFields(file *types.File, funcDecl *ast.FuncDecl) ([]*types.MethodField, []*types.MethodField, *types.MethodField) {
	parser := func(fieldsList []*ast.Field) []*types.MethodField {
		var params []*types.MethodField
		for _, field := range fieldsList {
			paramType := ComputeTypeForAstExpr(file, field.Type)
			// returns with types only, which is usually the most frequent scenario
			if len(field.Names) == 0 {
				param := &types.MethodField{
					FieldInfo: types.FieldInfo{
						Ast:  field,
						Type: paramType,
					},
				}
				params = append(params, param)
			}
			for _, ident := range field.Names {
				param := &types.MethodField{
					FieldInfo: types.FieldInfo{
						Ast:  field,
						Type: paramType,
						Name: ident.Name,
					},
				}
				params = append(params, param)
			}
		}
		return params
	}
	var receiver *types.MethodField
	if funcDecl.Recv != nil {
		receiverLst := parser(funcDecl.Recv.List)
		if len(receiverLst) > 0 {
			receiver = receiverLst[0]
		}
	}
	return parser(funcDecl.Type.Params.List), parser(funcDecl.Type.Results.List), receiver
}
