[] (-1) (PointerVariable PointerType) s (*threechain2.StockServiceImpl struct{stock_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) threechain2.StockServiceImpl struct{stock_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) stock_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (7) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (1) (Reference UserType) ref <ctx context.Context> @ CartService 

[] (-1) (BasicVariable BasicType) productID string // write(stock_db), 
[_] (8) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (4) (Reference BasicType) ref <ProductID string> @ CartService // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BasicVariable BasicType) quantity int // write(stock_db), 
[_] (9) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (5) (Reference BasicType) ref <Quantity int> @ CartService // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = stock_database, collection = stock_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) stock threechain2.Stock struct{ProductID string, Quantity int} // write(stock_db), 
[_] (0) (FieldVariable FieldType) ProductID string // write(stock_db), 
[__] (-1) (BasicVariable BasicType) productID string // write(stock_db), 
[___] (8) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (4) (Reference BasicType) ref <ProductID string> @ CartService // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(stock_db), 
[__] (-1) (BasicVariable BasicType) quantity int // write(stock_db), 
[___] (9) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (5) (Reference BasicType) ref <Quantity int> @ CartService // write(order_db), write(stock_db), write(billing_db), 

