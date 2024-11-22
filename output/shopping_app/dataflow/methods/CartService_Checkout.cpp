[] (PointerObject PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase})
[_] (StructObject UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}
[__] (FieldObject FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldObject FieldType) order_service shopping_app.OrderService
[___] (ServiceObject ServiceType) order_service shopping_app.OrderService
[__] (FieldObject FieldType) product_service shopping_app.ProductService
[___] (ServiceObject ServiceType) product_service shopping_app.ProductService

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) cartID string

[] (StructObject UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string}
[_] (FieldObject FieldType) PricePerUnit int
[__] (BasicObject BasicType) PricePerUnit int
[_] (FieldObject FieldType) ProductID string
[__] (BasicObject BasicType) ProductID string
[_] (FieldObject FieldType) Quantity int
[__] (BasicObject BasicType) Quantity int
[_] (FieldObject FieldType) UserID string
[__] (BasicObject BasicType) UserID string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "cartID" string, Value string}
[__] (FieldObject FieldType) Key "cartID" string
[___] (BasicObject BasicType) "cartID" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) cartID string

[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection}
[_] (StructObject UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string}
[__] (FieldObject FieldType) PricePerUnit int
[___] (BasicObject BasicType) PricePerUnit int
[__] (FieldObject FieldType) ProductID string
[___] (BasicObject BasicType) ProductID string
[__] (FieldObject FieldType) Quantity int
[___] (BasicObject BasicType) Quantity int
[__] (FieldObject FieldType) UserID string
[___] (BasicObject BasicType) UserID string

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "cartID" string, Value string}
[__] (FieldObject FieldType) Key "cartID" string
[___] (BasicObject BasicType) "cartID" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) cartID string

[] (SliceObject UserType) update primitive.D
[_] (StructObject StructType) struct{Key "status" string, Value "completed" string}
[__] (FieldObject FieldType) Key "status" string
[___] (BasicObject BasicType) "status" string
[__] (FieldObject FieldType) Value "completed" string
[___] (BasicObject BasicType) "completed" string

