[] (PointerObject PointerType) s (*shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructObject UserType) shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int}
[__] (FieldObject FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldObject FieldType) num_workers 4 int
[___] (BasicObject BasicType) 4 int
[__] (FieldObject FieldType) product_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) product_queue Queue
[__] (FieldObject FieldType) product_service shopping_simple.ProductService
[___] (ServiceObject ServiceType) product_service shopping_simple.ProductService

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) message shopping_simple.ProductQueueMessage struct{ProductID string, Remove bool}
[_] (FieldObject FieldType) ProductID string
[__] (BasicObject BasicType) ProductID string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_database}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D

[] (SliceObject UserType) update primitive.D
[_] (StructObject StructType) struct{Key "$dec" string, Value primitive.D}
[__] (FieldObject FieldType) Key "$dec" string
[___] (BasicObject BasicType) "$dec" string
[__] (FieldObject FieldType) Value primitive.D
[___] (SliceObject UserType) primitive.D
[____] (StructObject StructType) struct{Key "totalquantity" string, Value 1 int}
[_____] (FieldObject FieldType) Key "totalquantity" string
[______] (BasicObject BasicType) "totalquantity" string
[_____] (FieldObject FieldType) Value 1 int
[______] (BasicObject BasicType) 1 int
[_] (StructObject StructType) struct{Key "$pull" string, Value primitive.D}
[__] (FieldObject FieldType) Key "$pull" string
[___] (BasicObject BasicType) "$pull" string
[__] (FieldObject FieldType) Value primitive.D
[___] (SliceObject UserType) primitive.D
[____] (StructObject StructType) struct{Key "products" string, Value string}
[_____] (FieldObject FieldType) Key "products" string
[______] (BasicObject BasicType) "products" string
[_____] (FieldObject FieldType) Value string
[______] (BasicObject BasicType) ProductID string

[] (BasicObject BasicType) updated int

[] (InterfaceObject UserType) err .error

