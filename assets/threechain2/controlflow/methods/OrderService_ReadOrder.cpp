[] (PointerVariable PointerType) c (*threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue}) 
[_] (StructVariable UserType) threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue} 
[__] (ServiceVariable ServiceType) stock_service threechain2.StockService 
[__] (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 
[__] (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ ShipmentService 
[__] (Reference UserType) ref <ctx context.Context> @ ShipmentService 

[] (BasicVariable BasicType) orderID string // read(stock_db), 
[_] (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(stock_db), 
[__] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(stock_db), 
[___] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[____] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 

[] (StructVariable UserType) order threechain2.Order struct{OrderID string, Username string, Product string, Quantity int, Timestamp int64} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D // read(stock_db), 
[_] (StructVariable StructType) struct{Key "orderID" string, Value string} // read(stock_db), 
[__] (FieldVariable FieldType) Key "orderID" string // read(stock_db), 
[___] (BasicVariable BasicType) "orderID" string // read(stock_db), 
[__] (FieldVariable FieldType) Value string // read(stock_db), 
[___] (BasicVariable BasicType) orderID string // read(stock_db), 
[____] (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(stock_db), 
[_____] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(stock_db), 
[______] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[_______] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = order_database, collection = order_collection} // read(stock_db), 

[] (InterfaceVariable UserType) _ .error 

