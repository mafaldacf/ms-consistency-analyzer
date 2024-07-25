[] (PointerVariable PointerType) s (*threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (StructVariable UserType) threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (ServiceVariable ServiceType) order_service threechain2.OrderService 
[__] (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 
[__] (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (BasicVariable BasicType) num_workers 4 int 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ ShipmentService 

[] (StructVariable UserType) shipmentMessage threechain2.ShipmentMessage struct{OrderID string, Username string} 
[_] (Reference UserType) ref <workerMessage threechain2.ShipmentMessage struct{OrderID string, Username string}> @ ShipmentService 
[__] (FieldVariable FieldType) OrderID string // write(shipment_db), read(stock_db), 
[___] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[____] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[__] (FieldVariable FieldType) Username string // write(shipment_db), 
[___] (BasicVariable BasicType) Username string // write(shipment_db), 
[____] (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) OrderID string 
[__] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(stock_db), 
[___] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[____] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[__] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[___] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(stock_db), 
[____] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[_____] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (FieldVariable FieldType) Username string 
[__] (Reference FieldType) ref <Username string> @ ShipmentService // write(shipment_db), 
[___] (BasicVariable BasicType) Username string // write(shipment_db), 
[____] (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[__] (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (Reference FieldType) ref <Username string> @ ShipmentService // write(shipment_db), 
[____] (BasicVariable BasicType) Username string // write(shipment_db), 
[_____] (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipment_database, collection = shipment_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) shipment threechain2.Shipment struct{OrderID string, Username string, Status string} // write(shipment_db), 
[_] (FieldVariable FieldType) OrderID string // write(shipment_db), 
[__] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[___] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(stock_db), 
[____] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[_____] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (FieldVariable FieldType) Username string // write(shipment_db), 
[__] (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (Reference FieldType) ref <Username string> @ ShipmentService // write(shipment_db), 
[____] (BasicVariable BasicType) Username string // write(shipment_db), 
[_____] (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) Status "pending" string // write(shipment_db), 
[__] (BasicVariable BasicType) "pending" string // write(shipment_db), 

