[] (PointerVariable PointerType) s (*threechain2.StockServiceImpl struct{stock_db NoSQLDatabase}) 
[_] (StructVariable UserType) threechain2.StockServiceImpl struct{stock_db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) stock_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) product string 

[] (BasicVariable BasicType) quantity int 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = stock_database, collection = stock_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) stock threechain2.Stock struct{Product string, Quantity int} 
[_] (FieldVariable FieldType) Product string 
[__] (BasicVariable BasicType) product string 
[_] (FieldVariable FieldType) Quantity int 
[__] (BasicVariable BasicType) quantity int 

