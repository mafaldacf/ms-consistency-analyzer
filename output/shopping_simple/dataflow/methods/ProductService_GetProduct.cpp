[] (PointerVariable PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}) 
[_] (StructVariable UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int} 
[__] (FieldVariable FieldType) product_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase 
[__] (FieldVariable FieldType) product_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ CartService 
[__] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) productID string 
[_] (Reference BasicType) ref <productID string> @ CartService // write(cart_db), 
[__] (Reference BasicType) ref <productID string> @ Frontend // write(cart_db), 

[] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "productid" string, Value string} 
[__] (FieldVariable FieldType) Key "productid" string 
[___] (BasicVariable BasicType) "productid" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) productID string 
[____] (Reference BasicType) ref <productID string> @ CartService // write(cart_db), 
[_____] (Reference BasicType) ref <productID string> @ Frontend // write(cart_db), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection} 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

