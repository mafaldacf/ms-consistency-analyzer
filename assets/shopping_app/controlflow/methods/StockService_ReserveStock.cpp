[] (-1) (PointerVariable PointerType) s (*shopping_app.StockServiceImpl struct{stock_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shopping_app.StockServiceImpl struct{stock_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) stock_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (12) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (6) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (-1) (BasicVariable BasicType) productID string // write(stock_db), 
[_] (13) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (9) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BasicVariable BasicType) quantity int // write(stock_db), 
[_] (14) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (10) (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = stock_database, collection = stock_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) stock shopping_app.Stock struct{ProductID string, Quantity int} // write(stock_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(stock_db), 
[__] (-1) (BasicVariable BasicType) quantity int // write(stock_db), 
[___] (14) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (10) (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) ProductID string // write(stock_db), 
[__] (-1) (BasicVariable BasicType) productID string // write(stock_db), 
[___] (13) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (9) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

