[] (-1) (PointerVariable PointerType) s (*threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (-1) (ServiceVariable ServiceType) order_service threechain2.OrderService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (11) (Reference UserType) ref <ctx context.Context> @ ShipmentService 

[] (-1) (StructVariable UserType) shipmentMessage threechain2.ShipmentMessage struct{OrderID string, Username string} 
[_] (12) (Reference UserType) ref <workerMessage threechain2.ShipmentMessage struct{OrderID string, Username string}> @ ShipmentService 
[__] (16) (FieldVariable FieldType) OrderID string // write(shipment_db), read(order_db), 
[___] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[____] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[__] (13) (FieldVariable FieldType) Username string // write(shipment_db), 
[___] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[____] (15) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) OrderID string 
[__] (16) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(order_db), 
[___] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[____] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[__] (0) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[___] (16) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(order_db), 
[____] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[_____] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (0) (FieldVariable FieldType) Username string 
[__] (13) (Reference FieldType) ref <Username string> @ ShipmentService // write(shipment_db), 
[___] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[____] (15) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[__] (0) (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (13) (Reference FieldType) ref <Username string> @ ShipmentService // write(shipment_db), 
[____] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[_____] (15) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipment_database, collection = shipment_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) shipment threechain2.Shipment struct{OrderID string, Username string, Status string} // write(shipment_db), 
[_] (0) (FieldVariable FieldType) OrderID string // write(shipment_db), 
[__] (0) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[___] (16) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(order_db), 
[____] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[_____] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (0) (FieldVariable FieldType) Username string // write(shipment_db), 
[__] (0) (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (13) (Reference FieldType) ref <Username string> @ ShipmentService // write(shipment_db), 
[____] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[_____] (15) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) Status "pending" string // write(shipment_db), 
[__] (0) (BasicVariable BasicType) "pending" string // write(shipment_db), 

