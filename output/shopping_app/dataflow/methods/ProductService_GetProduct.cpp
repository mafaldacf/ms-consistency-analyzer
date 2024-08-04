[] (PointerVariable PointerType) s (*shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase}) 
[_] (StructVariable UserType) shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase} 
[__] (FieldVariable FieldType) product_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ CartService 
[__] (Reference UserType) ref <ctx context.Context> @ Frontend 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) productID string 
[_] (Reference BasicType) ref <productID string> @ CartService 
[__] (Reference BasicType) ref <productID string> @ Frontend 
[_] (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "productID" string, Value string} 
[__] (FieldVariable FieldType) Key "productID" string 
[___] (BasicVariable BasicType) "productID" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) productID string 
[____] (Reference BasicType) ref <productID string> @ CartService 
[_____] (Reference BasicType) ref <productID string> @ Frontend 
[____] (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[_____] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (BasicVariable BasicType) _ bool 

[] (InterfaceVariable UserType) err .error 

