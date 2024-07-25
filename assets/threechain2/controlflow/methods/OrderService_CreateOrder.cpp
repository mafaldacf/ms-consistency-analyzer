[] (PointerVariable PointerType) c (*threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue}) 
[_] (StructVariable UserType) threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue} 
[__] (ServiceVariable ServiceType) stock_service threechain2.StockService 
[__] (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 
[__] (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) orderID string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[_] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 

[] (BasicVariable BasicType) username string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[_] (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (BasicVariable BasicType) product string // write(stock_db), 

[] (BasicVariable BasicType) quantity int // write(stock_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) order threechain2.Order struct{OrderID string, Username string, Product string, Quantity int, Timestamp int64} // write(stock_db), 
[_] (FieldVariable FieldType) Timestamp 1 int // write(stock_db), 
[__] (BasicVariable BasicType) 1 int // write(stock_db), 
[_] (FieldVariable FieldType) OrderID string // write(stock_db), 
[__] (BasicVariable BasicType) orderID string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (FieldVariable FieldType) Username string // write(stock_db), 
[__] (BasicVariable BasicType) username string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[___] (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) Product string // write(stock_db), 
[__] (BasicVariable BasicType) product string // write(stock_db), 
[_] (FieldVariable FieldType) Quantity int // write(stock_db), 
[__] (BasicVariable BasicType) quantity int // write(stock_db), 

[] (StructVariable UserType) message threechain2.ShipmentMessage struct{OrderID string, Username string} // write(shipment_queue), read(shipment_queue), 
[_] (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[__] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[__] (BasicVariable BasicType) orderID string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (FieldVariable FieldType) Username string // write(shipment_queue), read(shipment_queue), 
[__] (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[__] (BasicVariable BasicType) username string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[___] (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

