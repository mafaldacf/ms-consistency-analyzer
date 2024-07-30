[] (-1) (PointerVariable PointerType) s (*shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase 

[] (14) (InterfaceVariable UserType) ctx context.Context 
[_] (6) (Reference UserType) ref <ctx context.Context> @ CartService 
[__] (3) (Reference UserType) ref <ctx context.Context> @ Frontend 
[_] (14) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (8) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (15) (BasicVariable BasicType) productID string 
[_] (7) (Reference BasicType) ref <productID string> @ CartService 
[__] (5) (Reference BasicType) ref <productID string> @ Frontend 
[_] (15) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (11) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "productID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "productID" string 
[___] (0) (BasicVariable BasicType) "productID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (15) (BasicVariable BasicType) productID string 
[____] (7) (Reference BasicType) ref <productID string> @ CartService 
[_____] (5) (Reference BasicType) ref <productID string> @ Frontend 
[____] (15) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[_____] (11) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

