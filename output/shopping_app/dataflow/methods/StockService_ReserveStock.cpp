[] (PointerVariable PointerType) s (*shopping_app.StockServiceImpl struct{stock_db NoSQLDatabase}) 
[_] (StructVariable UserType) shopping_app.StockServiceImpl struct{stock_db NoSQLDatabase} 
[__] (FieldVariable FieldType) stock_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) stock_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) productID string // write(stock_db), 
[_] (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (BasicVariable BasicType) quantity int // write(stock_db), 
[_] (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = stock_database, collection = stock_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) stock shopping_app.Stock struct{ProductID string, Quantity int} // write(stock_db), 
[_] (FieldVariable FieldType) ProductID string // write(stock_db), 
[__] (BasicVariable BasicType) productID string // write(stock_db), 
[___] (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (FieldVariable FieldType) Quantity int // write(stock_db), 
[__] (BasicVariable BasicType) quantity int // write(stock_db), 
[___] (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

