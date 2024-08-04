[] (PointerVariable PointerType) s (*shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase}) 
[_] (StructVariable UserType) shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase} 
[__] (FieldVariable FieldType) product_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) productID string 

[] (BasicVariable BasicType) description string 

[] (BasicVariable BasicType) pricePerUnit int 

[] (BasicVariable BasicType) category string 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (FieldVariable FieldType) Category string 
[__] (BasicVariable BasicType) category string 
[_] (FieldVariable FieldType) Description string 
[__] (BasicVariable BasicType) description string 
[_] (FieldVariable FieldType) PricePerUnit int 
[__] (BasicVariable BasicType) pricePerUnit int 
[_] (FieldVariable FieldType) ProductID string 
[__] (BasicVariable BasicType) productID string 

[] (InterfaceVariable UserType) err .error 

