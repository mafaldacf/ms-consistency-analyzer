[] (PointerVariable PointerType) s (*shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int})
[_] (StructVariable UserType) shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int}
[__] (FieldVariable FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldVariable FieldType) num_workers 4 int
[___] (BasicVariable BasicType) 4 int
[__] (FieldVariable FieldType) product_queue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue
[__] (FieldVariable FieldType) product_service shopping_simple.ProductService
[___] (ServiceVariable ServiceType) product_service shopping_simple.ProductService

[] (InterfaceVariable UserType) ctx context.Context

[] (StructVariable UserType) message shopping_simple.ProductQueueMessage struct{ProductID string, Remove bool}
[_] (FieldVariable FieldType) ProductID string
[__] (BasicVariable BasicType) ProductID string

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_database}

[] (InterfaceVariable UserType) _ .error

[] (SliceVariable UserType) filter primitive.D

[] (SliceVariable UserType) update primitive.D
[_] (StructVariable StructType) struct{Key "$dec" string, Value primitive.D}
[__] (FieldVariable FieldType) Key "$dec" string
[___] (BasicVariable BasicType) "$dec" string
[__] (FieldVariable FieldType) Value primitive.D
[___] (SliceVariable UserType) primitive.D
[____] (StructVariable StructType) struct{Key "totalquantity" string, Value 1 int}
[_____] (FieldVariable FieldType) Key "totalquantity" string
[______] (BasicVariable BasicType) "totalquantity" string
[_____] (FieldVariable FieldType) Value 1 int
[______] (BasicVariable BasicType) 1 int
[_] (StructVariable StructType) struct{Key "$pull" string, Value primitive.D}
[__] (FieldVariable FieldType) Key "$pull" string
[___] (BasicVariable BasicType) "$pull" string
[__] (FieldVariable FieldType) Value primitive.D
[___] (SliceVariable UserType) primitive.D
[____] (StructVariable StructType) struct{Key "products" string, Value string}
[_____] (FieldVariable FieldType) Key "products" string
[______] (BasicVariable BasicType) "products" string
[_____] (FieldVariable FieldType) Value string
[______] (BasicVariable BasicType) ProductID string

[] (BasicVariable BasicType) updated int

[] (InterfaceVariable UserType) err .error

