[] (-1) (PointerVariable PointerType) s (*shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase 

[] (12) (InterfaceVariable UserType) ctx context.Context 
[_] (4) (Reference UserType) ref <ctx context.Context> @ CartService 
[__] (1) (Reference UserType) ref <ctx context.Context> @ Frontend 
[_] (12) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (6) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (13) (BasicVariable BasicType) productID string 
[_] (5) (Reference BasicType) ref <productID string> @ CartService 
[__] (3) (Reference BasicType) ref <productID string> @ Frontend 
[_] (13) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (9) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "productID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "productID" string 
[___] (0) (BasicVariable BasicType) "productID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (13) (BasicVariable BasicType) productID string 
[____] (5) (Reference BasicType) ref <productID string> @ CartService 
[_____] (3) (Reference BasicType) ref <productID string> @ Frontend 
[____] (13) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[_____] (9) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (BasicVariable BasicType) _ bool 

[] (-1) (InterfaceVariable UserType) err .error 

