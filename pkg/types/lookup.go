package types

import (
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
	"go/ast"
	"go/token"
	"slices"
	"strconv"
	"strings"
)

func GetDeclaredVariableReverse(name string, variables []Variable) Variable {
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
func createCompositeVariable(typeName string) *CompositeVariable {
	return &CompositeVariable{
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
		return &CompositeVariable{
			VariableInfo: &VariableInfo{
				Name: name,
				Type: e,
				Id:   VARIABLE_UNASSIGNED_ID,
			},
		}
	case *StructType:
		e.FieldTypes = make(map[string]Type)
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

func ComputeType(typeExpr ast.Expr, file *File) Type {
	switch e := typeExpr.(type) {
	case *ast.Ident:
		if utils.IsBasicType(e.Name) {
			return &BasicType{
				Name: e.Name,
			}
		}
		if userType, ok := GetDeclaredUserType(file, typeExpr); ok {
			return userType
		}
	case *ast.SelectorExpr:
		if pkgIdent, ok := e.X.(*ast.Ident); ok {
			if impt, ok := file.GetImport(pkgIdent.Name); ok {
				userType := &UserType{
					Name:     e.Sel.Name,
					Package:  impt.Alias,
					UserType: nil,
				}
				return userType
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

func CreateVariableFromType(name string, t Type) Variable {
	info := &VariableInfo{
		Id:   VARIABLE_UNASSIGNED_ID,
		Name: name,
		Type: t,
	}
	switch e := t.(type) {
	case *BasicType:
		return &BasicVariable{VariableInfo: info}
	case *ChanType:
		return &ChanVariable{VariableInfo: info}
	case *MapType:
		return &MapVariable{VariableInfo: info}
	case *InterfaceType:
		return &InterfaceVariable{VariableInfo: info}
	case *ArrayType:
		return &ArrayVariable{VariableInfo: info}
	case *StructType:
		// if we are here due to a recursive call (e.g. from UserType)
		// then we want to make sure we are not reseting the map
		if e.FieldTypes == nil {
			e.FieldTypes = make(map[string]Type)
		}
		return &StructVariable{
			VariableInfo: info,
			Fields:       make(map[string]Variable),
		}
	case *UserType:
		if e.UserType != nil {
			variable := CreateVariableFromType(name, e.UserType)
			variable.GetVariableInfo().Type = e
			return variable
		}
		// e.g. context.Context is nil
		return &GenericVariable{VariableInfo: info}
	case *ImportedType:
		return &GenericVariable{VariableInfo: info}
	}
	logger.Logger.Fatalf("could not create variable from type %v", t)
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
	file.Package.DeclaredTypes["Post"] = &StructType{
		FieldTypes: map[string]Type{
			"ReqID":     &BasicType{Name: "int64"},
			"PostID":    &BasicType{Name: "int64"},
			"Text":      &BasicType{Name: "string"},
			"Timestamp": &BasicType{Name: "int64"},
			"Creator":   &BasicType{Name: "string"},
		},
	}
	file.Package.DeclaredTypes["Message"] = &StructType{
		FieldTypes: map[string]Type{
			"ReqID":     &BasicType{Name: "int64"},
			"PostID":    &BasicType{Name: "int64"},
			"Timestamp": &BasicType{Name: "int64"},
		},
	}
	services := []string{"StorageService", "NotifyService", "UploadService"}

	switch e := expr.(type) {
	case *ast.Ident:
		if t, ok := file.Package.DeclaredTypes[e.Name]; ok || slices.Contains(services, e.Name) {
			return &UserType{
				Name:     e.Name,
				Package:  file.Package.Name,
				UserType: t,
			}, true
		}
	}
	logger.Logger.Fatalf("could not get declared type for expr %s (type = %s)", expr, utils.GetType(expr))
	return nil, false
}

func LookupVariables(file *File, blockVars []Variable, expr ast.Expr, assign bool) (variable Variable) {
	switch e := expr.(type) {
	case *ast.Ident:
		variable = GetDeclaredVariableReverse(e.Name, blockVars)
	case *ast.BasicLit:
		basicType := &BasicType{
			Name:  strings.ToLower(e.Kind.String()),
			Value: e.Value,
		}
		variable = &BasicVariable{
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
					structVariable := &StructVariable{
						VariableInfo: &VariableInfo{
							Type: userType,
							Id:   VARIABLE_INLINE_ID,
						},
						Fields: make(map[string]Variable),
					}
					for _, elt := range e.Elts {
						keyvalue := elt.(*ast.KeyValueExpr)
						key := keyvalue.Key.(*ast.Ident)
						eltVar := LookupVariables(file, blockVars, keyvalue.Value, false)
						if eltVar.GetVariableInfo().Name == "" {
							eltVar.GetVariableInfo().SetName(key.Name)
						}
						structVariable.AddFieldIfNotExists(key.Name, eltVar)
					}
					variable = structVariable
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
				eltVar := LookupVariables(file, blockVars, elt, false)
				variable.(*ArrayVariable).AddElement(eltVar)
			}
		}

	case *ast.SelectorExpr:
		variable = LookupVariables(file, blockVars, e.X, assign)
		switch v := variable.(type) {
		case *StructVariable:
			logger.Logger.Warnf("GOT SELECTOR FOR %s", e.Sel.Name)
			variable = v.GetOrCreateField(e.Sel.Name)
			//variable = v
		default:
			logger.Logger.Fatalf("could not find variable for selector %s with type %s", variable.String(), utils.GetType(variable))
		}
	case *ast.CallExpr:
		// NOTE: for now we only care about known functions that return a new object
		// e.g. we don't care about direct transformations like obj2 := common.StringToInt64(obj1)

		//FIXME: we need to try to find methods that are declared in this package with known return type
		callStr := computeFunctionCallName(e.Fun) + "(...)"
		genericVariable := createCompositeVariable(callStr)
		/* if len(e.Args) == 1 {
			argVar := LookupVariables(file, blockVars, e.Args[0], false)
			if !slices.Contains(blockVars, argVar) {
				logger.Logger.Warnf("ignoring undeclared variable %v in function call %s", argVar, callStr)
				return argVar
			}
		} */
		for _, arg := range e.Args {
			argVar := LookupVariables(file, blockVars, arg, false)
			genericVariable.Params = append(genericVariable.Params, argVar)

			// a direct transformation from one or more existing variables
			/* if slices.Contains(blockVars, argVar) {
				genericVariable.Params = append(genericVariable.Params, argVar)
			} else {
				logger.Logger.Warnf("ignoring undeclared variable %s in function call %s", argVar.String(), callStr)
			} */
		}
		variable = genericVariable
		//variable = &PlaceholderVariable{VariableInfo: &VariableInfo{Name: "placeholder", Type: &PlaceholderType{}}}

	case *ast.TypeAssertExpr:
		variable = LookupVariables(file, blockVars, e.X, assign)
	case *ast.IndexExpr:
		variable = LookupVariables(file, blockVars, e.X, assign)
		if arrayVar, ok := variable.(*ArrayVariable); ok {
			variable = arrayVar.Elements[computeArrayIndex(e.Index)]
		}
		if mapVar, ok := variable.(*MapVariable); ok {
			key := LookupVariables(file, blockVars, e.Index, false)
			variable, ok = mapVar.KeyValues[key]
			if !ok {
				logger.Logger.Warnf("got map %v with unassigned value for key %s", mapVar.String(), key.String())
				variable = mapVar
			}
		}
	case *ast.UnaryExpr:
		if e.Op == token.AND { // e.g. &post
			variable = LookupVariables(file, blockVars, e.X, assign)
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
			variable = LookupVariables(file, blockVars, e.X, assign)
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
			variable = LookupVariables(file, blockVars, e.X, assign)
		}
	default:
		logger.Logger.Fatalf("unknown type in LookupVariables for type %s: %v", utils.GetType(e), e)
	}
	if variable == nil {
		logger.Logger.Fatalf("nil variable for %s: %v", utils.GetType(expr), expr)
	}
	return variable
}

func IsVarDeclOrAssign(file *File, blockVars []Variable, node ast.Node) ([]Variable, bool) {
	var vars []Variable
	switch n := node.(type) {
	case *ast.DeclStmt:
		for _, spec := range n.Decl.(*ast.GenDecl).Specs {
			v, _ := IsVarDeclOrAssign(file, blockVars, spec)
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
			field := LookupVariables(file, blockVars, rvalue, true)
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
	return vars, len(vars) != 0
}
