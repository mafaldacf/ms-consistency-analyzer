[] (PointerVariable PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}) 
[_] (StructVariable UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int} 
[__] (FieldVariable FieldType) product_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase 
[__] (FieldVariable FieldType) product_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) productID string // read(product_db), 
[_] (Reference BasicType) ref <productID string> @ Frontend // read(product_db), 

[] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string} // read(product_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D // read(product_db), 
[_] (StructVariable StructType) struct{Key "productid" string, Value string} // read(product_db), 
[__] (FieldVariable FieldType) Key "productid" string // read(product_db), 
[___] (BasicVariable BasicType) "productid" string // read(product_db), 
[__] (FieldVariable FieldType) Value string // read(product_db), 
[___] (BasicVariable BasicType) productID string // read(product_db), 
[____] (Reference BasicType) ref <productID string> @ Frontend // read(product_db), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection} // read(product_db), 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) exists bool // read(product_db), 

[] (InterfaceVariable UserType) err .error 

