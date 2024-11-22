[] (PointerObject PointerType) s (*cart.cartImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) cart.cartImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService

[] (BasicObject BasicType) customerID string
[_] (Reference BasicType) ref <sessionID string> @ FrontendService

[] (StructObject UserType) item cart.Item struct{ID string, Quantity int, UnitPrice float32}
[_] (Reference UserType) ref <cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ FrontendService
[__] (FieldObject FieldType) ID string
[___] (BasicObject BasicType) ID string
[__] (FieldObject FieldType) Quantity 1 int
[___] (BasicObject BasicType) 1 int
[__] (FieldObject FieldType) UnitPrice float32
[___] (BasicObject BasicType) Price float32

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart, collection = carts}

[] (InterfaceObject UserType) _ .error

[] (PointerObject PointerType) cart (*cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}})
[_] (StructObject UserType) cart.cart struct{ID string, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}}
[__] (FieldObject FieldType) ID string
[___] (BasicObject BasicType) customerID string
[____] (Reference BasicType) ref <sessionID string> @ FrontendService

