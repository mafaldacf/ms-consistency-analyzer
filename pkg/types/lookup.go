package types

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"go/ast"
	"go/token"
	"strconv"
	"strings"
)

func GetDeclaredVariable(name string, variables []Variable) Variable {
	for i := len(variables) - 1; i >= 0; i-- {
		v := variables[i]
		if name == v.GetVariableInfo().GetName() {
			return v
		}
	}
	logger.Logger.Fatalf("variable '%s' not found in declared blockVars: %v", name, variables)
	return nil
}

// FIXME!!!!! this is just temporary
func createInlineVariable(typeName string) *GenericVariable {
	return &GenericVariable{
		VariableInfo: &VariableInfo{
			Type: &GenericType{
				Name: typeName,
			},
			Id: VARIABLE_INLINE_ID,
		},
	}
}

func CreateTypeVariable(name string, t Type) Variable {
	switch e := t.(type) {
	case *UserType, *BasicType, *ChanType, *InterfaceType:
		return &GenericVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
		}
	case *StructType:
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

func computeUserType(impt *Import, name string) Type {
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
		return &UserType{
			Name:    e.Name,
			Package: file.Package.Name,
		}
	case *ast.SelectorExpr:
		if pkgIdent, ok := e.X.(*ast.Ident); ok {
			if impt, ok := file.GetImport(pkgIdent.Name); ok {
				return &UserType{
					Name:    e.Sel.Name,
					Package: pkgIdent.Name,
					Type:    computeUserType(impt, e.Sel.Name),
				}
			}
		}
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

func computeArrayIndex(expr ast.Expr) int {
	switch e := expr.(type) {
	case *ast.BasicLit:
		index, err := strconv.Atoi(e.Value)
		if err != nil {
			logger.Logger.Fatalf("error converting index %s: %s", e.Value, err.Error())
		}
		return index
	}
	logger.Logger.Fatalf("could not compute index for expr %s (type = %s)", expr, utils.GetType(expr))
	return 0
}

func computeFunctionCallName(expr ast.Expr) string { 
	switch e := expr.(type) {
	case *ast.Ident:
		return e.Name
	case *ast.SelectorExpr:
		return computeFunctionCallName(e.X) + "." + e.Sel.Name
	}
	logger.Logger.Fatalf("could not compute function call name for expr %s (type = %s)", expr, utils.GetType(expr))
	return ""
}

func GetDeclaredUserType(file *File, expr ast.Expr) (*UserType, bool) {
	// FIX THIS HARDCODED CODE
	file.Package.DeclaredTypes["Post"] = &StructType{}
	file.Package.DeclaredTypes["Message"] = &StructType{}

	switch e := expr.(type) {
	case *ast.Ident:
		if t, ok := file.Package.DeclaredTypes[e.Name]; ok {
			return &UserType{
				Name: e.Name,
				Package: file.Package.Name,
				UserType: t,
			}, true
		}
	}
	logger.Logger.Fatalf("could not get declared type for expr %s (type = %s)", expr, utils.GetType(expr))
	return nil, false
}

func LookupVariables(file *File, blockVars []Variable, expr ast.Expr) (variable Variable) {
	switch e := expr.(type) {
	case *ast.Ident:
		variable = GetDeclaredVariable(e.Name, blockVars)
	case *ast.BasicLit:
		basicType := &BasicType{
			Name:  strings.ToLower(e.Kind.String()),
			Value: e.Value,
		}
		variable = &GenericVariable{
			VariableInfo: &VariableInfo{
				Type: basicType,
				Id:   VARIABLE_INLINE_ID,
			},
		}
	// FIXME: ACTUALLY THE TYPE OF A STRUCT SHOULD REFERENCE A USER TYPE THAT WAS PREVIOUSLY DEFINED
	case *ast.CompositeLit:
		if ident, ok := e.Type.(*ast.Ident); ok {
			if userType, found := GetDeclaredUserType(file, ident); found {

				if _, ok := userType.UserType.(*StructType); ok {
					variable = &StructVariable{
						VariableInfo: &VariableInfo{
							Type: userType,
							Id:   VARIABLE_INLINE_ID,
						},
						Fields: make(map[string]Variable),
					}
					for _, elt := range e.Elts {
						keyvalue := elt.(*ast.KeyValueExpr)
						key := keyvalue.Key.(*ast.Ident)
						eltVar := LookupVariables(file, blockVars, keyvalue.Value)
						if eltVar.GetVariableInfo().Name == "" {
							eltVar.GetVariableInfo().SetName(key.Name)
						}
						variable.(*StructVariable).AddField(key.Name, eltVar)
					}
				}
			}
		} else if arrayTypeAst, ok := e.Type.(*ast.ArrayType); ok {
			arrayType := &ArrayType{
				ElementsType: ComputeType(arrayTypeAst.Elt, file),
			}
			variable = &ArrayVariable{
				VariableInfo: &VariableInfo{
					Type: arrayType,
					Id:   VARIABLE_INLINE_ID,
				},
			}
			for _, elt := range e.Elts {
				eltVar := LookupVariables(file, blockVars, elt)
				variable.(*ArrayVariable).AddElement(eltVar)
			}
		}

	case *ast.SelectorExpr:
		variable = LookupVariables(file, blockVars, e.X)
		if structVar, ok := variable.(*StructVariable); ok {
			variable = structVar.Fields[e.Sel.Name]
		}
		//FIXME: this is happening for function parameters!!
		if genericVar, ok := variable.(*GenericVariable); ok {
			logger.Logger.Warnf("got generic variable %v for selector %s", genericVar.String(), e.Sel.Name)
		}
	case *ast.CallExpr:
		callStr := computeFunctionCallName(e.Fun) + "()"
		genVar := createInlineVariable(callStr)
		for _, arg := range e.Args {
			argVar := LookupVariables(file, blockVars, arg)
			genVar.Params = append(genVar.Params, argVar)
		}
		variable = genVar
	case *ast.TypeAssertExpr:
		variable = LookupVariables(file, blockVars, e.X)
	case *ast.IndexExpr:
		variable = LookupVariables(file, blockVars, e.X)
		if arrayVar, ok := variable.(*ArrayVariable); ok {
			variable = arrayVar.Elements[computeArrayIndex(e.Index)]
		}
		if mapVar, ok := variable.(*MapVariable); ok {
			key := LookupVariables(file, blockVars, e.Index)
			variable, ok = mapVar.KeyValues[key]
			if !ok {
				logger.Logger.Warnf("got map %v with unassigned value for key %s", mapVar.String(), key.String())
				variable = mapVar
			}
		}
	case *ast.UnaryExpr:
		if e.Op == token.AND { // e.g. &post
			variable = LookupVariables(file, blockVars, e.X)
			addrType := &AddressType{
				AddressOf: variable.GetVariableInfo().Type,
			}
			variable = &AddressVariable{
				AddressOf: variable,
				VariableInfo: &VariableInfo{
					Type: addrType,
					Id:   VARIABLE_INLINE_ID,
					Name: variable.GetVariableInfo().Name,
				},
			}
		} else if e.Op == token.MUL { // e.g. *post
			variable = LookupVariables(file, blockVars, e.X)
			addrType := &AddressType{
				AddressOf: variable.GetVariableInfo().Type,
			}
			variable = &PointerVariable{
				PointerTo: variable,
				VariableInfo: &VariableInfo{
					Type: addrType,
					Id:   VARIABLE_INLINE_ID,
					Name: variable.GetVariableInfo().Name,
				},
			}

		} else {
			variable = LookupVariables(file, blockVars, e.X)
		}
	default:
		logger.Logger.Fatalf("unknown type in LookupVariables for type %s: %v", utils.GetType(e), e)
	}
	return variable
}

func IsVarDeclOrAssign(file *File, blockVars []Variable, node ast.Node) []Variable {
	var vars []Variable
	switch n := node.(type) {
	case *ast.DeclStmt:
		for _, spec := range n.Decl.(*ast.GenDecl).Specs {
			v := IsVarDeclOrAssign(file, blockVars, spec)
			vars = append(vars, v...)
		}
	case *ast.ValueSpec:
		t := ComputeType(n.Type, file)
		for _, ident := range n.Names {
			decl := CreateTypeVariable(ident.Name, t)
			vars = append(vars, decl)
		}
	case *ast.AssignStmt:
		for i, rvalue := range n.Rhs {
			field := LookupVariables(file, blockVars, rvalue)
			lvalue := n.Lhs[i]

			field.GetVariableInfo().SetName(lvalue.(*ast.Ident).Name)
			field.GetVariableInfo().SetUnassigned()

			vars = append(vars, field)
		}
	case *ast.ExprStmt: // ignore expressions from function calls
	case *ast.ReturnStmt: // ignore return statements
	case *ast.BinaryExpr: // ignore e.g. if err != nil
	case *ast.IfStmt:
	case *ast.IncDecStmt:
		//TODO
	case *ast.DeferStmt:
		//TODO

	default:
		logger.Logger.Fatalf("unknown type in isVarDeclOrAssign for type %s: %v", utils.GetType(node), node)
	}
	return vars
}
