[] (-1) (PointerVariable PointerType) c (*threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue}) 
[_] (0) (StructVariable UserType) threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (ServiceVariable ServiceType) stock_service threechain2.StockService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) orderID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[_] (18) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 

[] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), 
[_] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (2) (BasicVariable BasicType) product string // write(order_db), write(stock_db), 

[] (3) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) order threechain2.Order struct{OrderID string, Username string, Product string, Quantity int, Timestamp int64} // write(order_db), 
[_] (0) (FieldVariable FieldType) OrderID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) orderID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (18) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (0) (FieldVariable FieldType) Username string // write(order_db), 
[__] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) Product string // write(order_db), 
[__] (2) (BasicVariable BasicType) product string // write(order_db), write(stock_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(order_db), 
[__] (3) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), 
[_] (0) (FieldVariable FieldType) Timestamp 1 int // write(order_db), 
[__] (0) (BasicVariable BasicType) 1 int // write(order_db), 

[] (4) (StructVariable UserType) message threechain2.ShipmentMessage struct{OrderID string, Username string} // write(shipment_queue), read(shipment_queue), 
[_] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[__] (18) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[__] (-1) (BasicVariable BasicType) orderID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (18) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (-1) (FieldVariable FieldType) Username string // write(shipment_queue), read(shipment_queue), 
[__] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[__] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

