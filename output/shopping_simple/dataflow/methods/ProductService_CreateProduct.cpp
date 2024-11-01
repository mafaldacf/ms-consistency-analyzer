[] (PointerVariable PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}) 
[_] (StructVariable UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int} 
[__] (FieldVariable FieldType) product_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase 
[__] (FieldVariable FieldType) product_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) productID string // write(product_db), 
[_] (Reference BasicType) ref <productID string> @ Frontend // write(product_db), 

[] (BasicVariable BasicType) description string // write(product_db), 
[_] (Reference BasicType) ref <description string> @ Frontend // write(product_db), 

[] (BasicVariable BasicType) pricePerUnit int // write(product_db), 
[_] (Reference BasicType) ref <pricePerUnit int> @ Frontend // write(product_db), 

[] (BasicVariable BasicType) category string // write(product_db), 
[_] (Reference BasicType) ref <category string> @ Frontend // write(product_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string} // write(product_db), 
[_] (FieldVariable FieldType) Category string // write(product_db), 
[__] (BasicVariable BasicType) category string // write(product_db), 
[___] (Reference BasicType) ref <category string> @ Frontend // write(product_db), 
[_] (FieldVariable FieldType) Description string // write(product_db), 
[__] (BasicVariable BasicType) description string // write(product_db), 
[___] (Reference BasicType) ref <description string> @ Frontend // write(product_db), 
[_] (FieldVariable FieldType) PricePerUnit int // write(product_db), 
[__] (BasicVariable BasicType) pricePerUnit int // write(product_db), 
[___] (Reference BasicType) ref <pricePerUnit int> @ Frontend // write(product_db), 
[_] (FieldVariable FieldType) ProductID string // write(product_db), 
[__] (BasicVariable BasicType) productID string // write(product_db), 
[___] (Reference BasicType) ref <productID string> @ Frontend // write(product_db), 

[] (InterfaceVariable UserType) err .error 

