[0] (PointerObject PointerType) s (*cart.cartImpl struct{db NoSQLDatabase})
[_1] (StructObject UserType) cart.cartImpl struct{db NoSQLDatabase}
[__2] (FieldObject FieldType) db NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) customerID string

[0] (StructObject UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32}

[0] (PointerObject PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}})
[_1] (StructObject UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}
[__2] (FieldObject FieldType) ID string
[___3] (BasicObject BasicType) customerID string
[__2] (FieldObject FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}
[___3] (ArrayObject ArrayType) []cart.Item struct{ID string, Quantity int, UnitPrice float32}
[____4] (StructObject UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32}

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts}

[0] (InterfaceObject UserType) _ .error

