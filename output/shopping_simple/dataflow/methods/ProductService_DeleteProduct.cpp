[] (PointerObject PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructObject UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}
[__] (FieldObject FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) product_db NoSQLDatabase
[__] (FieldObject FieldType) product_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) product_queue Queue

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

[] (BasicObject BasicType) productID string
[_] (Reference BasicType) ref <productID string> @ Frontend

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "productid" string, Value string}
[__] (FieldObject FieldType) Key "productid" string
[___] (BasicObject BasicType) "productid" string
[__] (FieldObject FieldType) Value string
[___] (BasicObject BasicType) productID string
[____] (Reference BasicType) ref <productID string> @ Frontend

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) val bool

