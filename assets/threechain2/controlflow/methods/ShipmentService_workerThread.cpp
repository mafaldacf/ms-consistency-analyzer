[] (PointerVariable PointerType) s (*threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (StructVariable UserType) threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (BasicVariable BasicType) num_workers 4 int 
[__] (ServiceVariable ServiceType) order_service threechain2.OrderService 
[__] (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ChanVariable ChanType) forever chan struct{} 

[] (MapVariable MapType) event map[string]interface{} // read(shipment_queue), 
[_] (Reference UserType) ref <message threechain2.ShipmentMessage struct{OrderID string, Username string}> @ ShipmentService // write(shipment_queue), read(shipment_queue), 
[__] (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[___] (BasicVariable BasicType) orderID string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[____] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[__] (FieldVariable FieldType) Username string // write(shipment_queue), read(shipment_queue), 
[___] (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[___] (BasicVariable BasicType) username string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[____] (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[_] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 

[] (BasicVariable BasicType) Username string // write(shipment_db), 
[_] (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (StructVariable UserType) workerMessage threechain2.ShipmentMessage struct{OrderID string, Username string} 
[_] (FieldVariable FieldType) OrderID string // write(shipment_db), read(stock_db), 
[__] (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[___] (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (FieldVariable FieldType) Username string // write(shipment_db), 
[__] (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

