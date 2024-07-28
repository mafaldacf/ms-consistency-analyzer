[] (-1) (PointerVariable PointerType) s (*threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (-1) (ServiceVariable ServiceType) order_service threechain2.OrderService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (18) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (12) (MapVariable MapType) event map[string]interface{} // read(shipment_queue), 
[_] (12) (Reference UserType) ref <message threechain2.ShipmentMessage struct{OrderID string, Username string}> @ ShipmentService // write(shipment_queue), read(shipment_queue), 
[__] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[___] (22) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[___] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[____] (2) (Reference BasicType) ref <cartID string> @ CartService // write(order_db), write(shipment_queue), read(shipment_queue), 
[____] (22) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[__] (-1) (FieldVariable FieldType) Username string // write(shipment_queue), read(shipment_queue), 
[___] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[___] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), write(billing_db), 
[____] (3) (Reference BasicType) ref <Username string> @ CartService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), 
[____] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (22) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (25) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (21) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[_] (22) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 

[] (24) (BasicVariable BasicType) Username string // write(shipment_db), 
[_] (25) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (19) (StructVariable UserType) workerMessage threechain2.ShipmentMessage struct{OrderID string, Username string} 
[_] (20) (FieldVariable FieldType) OrderID string // write(shipment_db), read(order_db), 
[__] (21) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[___] (22) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (23) (FieldVariable FieldType) Username string // write(shipment_db), 
[__] (24) (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (25) (InterfaceVariable InterfaceType) Username interface{} // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

