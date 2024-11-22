[] (PointerObject PointerType) s (*cart.cartImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) cart.cartImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) customerID string

[] (BasicObject BasicType) itemID string

[] (PointerObject PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}})
[_] (StructObject UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}
[__] (FieldObject FieldType) ID string
[___] (BasicObject BasicType) customerID string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts}

[] (InterfaceObject UserType) _ .error

