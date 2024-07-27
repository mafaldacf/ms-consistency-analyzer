[] (-1) (PointerVariable PointerType) s (*threechain2.StockServiceImpl struct{stock_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) threechain2.StockServiceImpl struct{stock_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) stock_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ OrderService 

[] (-1) (BasicVariable BasicType) product string // write(stock_db), 
[_] (2) (Reference BasicType) ref <product string> @ OrderService // write(order_db), write(stock_db), 

[] (-1) (BasicVariable BasicType) quantity int // write(stock_db), 
[_] (3) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = stock_database, collection = stock_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) stock threechain2.Stock struct{Product string, Quantity int} // write(stock_db), 
[_] (0) (FieldVariable FieldType) Product string // write(stock_db), 
[__] (-1) (BasicVariable BasicType) product string // write(stock_db), 
[___] (2) (Reference BasicType) ref <product string> @ OrderService // write(order_db), write(stock_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(stock_db), 
[__] (-1) (BasicVariable BasicType) quantity int // write(stock_db), 
[___] (3) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), 

