[] (-1) (PointerVariable PointerType) s (*threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (-1) (ServiceVariable ServiceType) order_service threechain2.OrderService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (11) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (4) (MapVariable MapType) event map[string]interface{} // read(shipment_queue), 
[_] (4) (Reference UserType) ref <message threechain2.ShipmentMessage struct{OrderID string, Username string}> @ ShipmentService // write(shipment_queue), read(shipment_queue), 
[__] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[___] (18) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[___] (-1) (BasicVariable BasicType) orderID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[____] (18) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[__] (-1) (FieldVariable FieldType) Username string // write(shipment_queue), read(shipment_queue), 
[___] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[___] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), 
[____] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (15) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[_] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 

[] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[_] (15) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (12) (StructVariable UserType) workerMessage threechain2.ShipmentMessage struct{OrderID string, Username string} 
[_] (16) (FieldVariable FieldType) OrderID string // write(shipment_db), read(order_db), 
[__] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[___] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (13) (FieldVariable FieldType) Username string // write(shipment_db), 
[__] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (15) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

