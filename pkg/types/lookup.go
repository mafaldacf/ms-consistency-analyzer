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
	/* case *StructType:
		return &StructVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
			Fields: make(map[string]Variable),
		} */
	case *MapType:
		return &MapVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
			KeyValues: make(map[Variable]Variable, 0),
		}
	/* case *ArrayType:
		return &ArrayVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
		} */
	}
	logger.Logger.Fatalf("could not create variable %s for type %s", name, t)
	return nil
}

func computeUserType(name string, importedPkg string) Type {
	return nil
}

func ComputeType(typeExpr ast.Expr, pkg string, importMap map[string]string) Type {
	switch e := typeExpr.(type) {
	case *ast.Ident:
		if utils.IsBasicType(e.Name) {
			return &BasicType{
				Name: e.Name,
			}
		}
		return &UserType{
			Name:    e.Name,
			Package: pkg,
		}
	case *ast.SelectorExpr:
		if pkgIdent, ok := e.X.(*ast.Ident); ok {
			if fullImpt, ok := importMap[pkgIdent.Name]; ok {
				return &UserType{
					Name:    e.Sel.Name,
					Package: pkgIdent.Name,
					Type:    computeUserType(e.Sel.Name, fullImpt),
				}
			}
		}
	case *ast.ChanType:
		return &ChanType{
			ChanType: ComputeType(e.Value, pkg, importMap),
		}
	case *ast.MapType:
		return &MapType{
			KeyType:   ComputeType(e.Key, pkg, importMap),
			ValueType: ComputeType(e.Value, pkg, importMap),
		}
	case *ast.InterfaceType:
		return &InterfaceType{}
	case *ast.ArrayType:
		return &ArrayType{
			ElementsType: ComputeType(e.Elt, pkg, importMap),
		}
	case *ast.StructType:
		return &StructType{
			// FIXME: struct type must not have a name, only a user type can have it
		}
	}
	logger.Logger.Fatalf("could not compute type for expr %v (type = %s), pkg %s, importMap %v", typeExpr, utils.GetType(typeExpr), pkg, importMap)
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

func GetDeclaredUserType(expr ast.Expr, pkg string, typesMap map[string]*UserType, importMap map[string]string) (*UserType, bool) {
	if typesMap == nil {
		// FIX THIS HARDCODED CODE
		typesMap = make(map[string]*UserType)
		typesMap["Post"] = &UserType{
			Name: "Post",
			Package: pkg,
			UserType: &StructType{},
		}
		typesMap["Message"] = &UserType{
			Name: "Message",
			Package: pkg,
			UserType: &StructType{},
		}
	}
	switch e := expr.(type) {
	case *ast.Ident:
		if userType, ok := typesMap[e.Name]; ok {
			return userType, true
		}
	}
	logger.Logger.Fatalf("could not get declared type for expr %s (type = %s)", expr, utils.GetType(expr))
	return nil, false
}

func LookupVariables(blockVars []Variable, expr ast.Expr, pkg string, importMap map[string]string) (variable Variable) {
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
			if userType, found := GetDeclaredUserType(ident, pkg, nil, importMap); found {
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
						eltVar := LookupVariables(blockVars, keyvalue.Value, pkg, importMap)
						if eltVar.GetVariableInfo().Name == "" {
							eltVar.GetVariableInfo().SetName(key.Name)
						}
						variable.(*StructVariable).AddField(key.Name, eltVar)
					}
				}
			}
		} else if arrayTypeAst, ok := e.Type.(*ast.ArrayType); ok {
			arrayType := &ArrayType{
				ElementsType: ComputeType(arrayTypeAst.Elt, pkg, importMap),
			}
			variable = &ArrayVariable{
				VariableInfo: &VariableInfo{
					Type: arrayType,
					Id:   VARIABLE_INLINE_ID,
				},
			}
			for _, elt := range e.Elts {
				eltVar := LookupVariables(blockVars, elt, pkg, importMap)
				variable.(*ArrayVariable).AddElement(eltVar)
			}
		}

	case *ast.SelectorExpr:
		variable = LookupVariables(blockVars, e.X, pkg, importMap)
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
			argVar := LookupVariables(blockVars, arg, pkg, importMap)
			genVar.Params = append(genVar.Params, argVar)
		}
		variable = genVar
	case *ast.TypeAssertExpr:
		variable = LookupVariables(blockVars, e.X, pkg, importMap)
	case *ast.IndexExpr:
		variable = LookupVariables(blockVars, e.X, pkg, importMap)
		if arrayVar, ok := variable.(*ArrayVariable); ok {
			variable = arrayVar.Elements[computeArrayIndex(e.Index)]
		}
		if mapVar, ok := variable.(*MapVariable); ok {
			key := LookupVariables(blockVars, e.Index, pkg, importMap)
			variable, ok = mapVar.KeyValues[key]
			if !ok {
				logger.Logger.Warnf("got map %v with unassigned value for key %s", mapVar.String(), key.String())
				variable = mapVar
			}
		}
	case *ast.UnaryExpr:
		if e.Op == token.AND { // e.g. &post
			variable = LookupVariables(blockVars, e.X, pkg, importMap)
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
			variable = LookupVariables(blockVars, e.X, pkg, importMap)
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
			variable = LookupVariables(blockVars, e.X, pkg, importMap)
		}
	default:
		logger.Logger.Fatalf("unknown type in LookupVariables for type %s: %v", utils.GetType(e), e)
	}
	return variable
}

func IsVarDeclOrAssign(blockVars []Variable, node ast.Node, pkg string, importMap map[string]string) []Variable {
	var vars []Variable
	switch n := node.(type) {
	case *ast.DeclStmt:
		for _, spec := range n.Decl.(*ast.GenDecl).Specs {
			v := IsVarDeclOrAssign(blockVars, spec, pkg, importMap)
			vars = append(vars, v...)
		}
	case *ast.ValueSpec:
		t := ComputeType(n.Type, pkg, importMap)
		for _, ident := range n.Names {
			decl := CreateTypeVariable(ident.Name, t)
			vars = append(vars, decl)
		}
	case *ast.AssignStmt:
		for i, rvalue := range n.Rhs {
			field := LookupVariables(blockVars, rvalue, pkg, importMap)
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
