[] (-1) (PointerVariable PointerType) s (*threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) threechain2.ShipmentServiceImpl struct{order_service threechain2.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (ServiceVariable ServiceType) order_service threechain2.OrderService 

[] (8) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (1) (MapVariable MapType) event map[string]interface{} // read(shipment_queue), 
[_] (1) (Reference UserType) ref <message threechain2.ShipmentMessage struct{OrderID string, Username string}> @ ShipmentService // write(shipment_queue), read(shipment_queue), 
[__] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[___] (12) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[___] (-1) (BasicVariable BasicType) orderID string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[____] (12) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[__] (-1) (FieldVariable FieldType) Username string // write(shipment_queue), read(shipment_queue), 
[___] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[___] (-1) (BasicVariable BasicType) username string // write(stock_db), write(shipment_queue), read(shipment_queue), 
[____] (15) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (12) (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (15) (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (11) (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[_] (12) (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 

[] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[_] (15) (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (9) (StructVariable UserType) workerMessage threechain2.ShipmentMessage struct{OrderID string, Username string} 
[_] (10) (FieldVariable FieldType) OrderID string // write(shipment_db), read(stock_db), 
[__] (11) (BasicVariable BasicType) OrderID string // write(shipment_db), read(stock_db), 
[___] (12) (InterfaceVariable InterfaceType) OrderID interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(stock_db), 
[_] (13) (FieldVariable FieldType) Username string // write(shipment_db), 
[__] (14) (BasicVariable BasicType) Username string // write(shipment_db), 
[___] (15) (InterfaceVariable InterfaceType) Username interface{} // write(stock_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

