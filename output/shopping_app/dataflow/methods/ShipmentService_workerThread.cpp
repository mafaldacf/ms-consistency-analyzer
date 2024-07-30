[] (-1) (PointerVariable PointerType) s (*shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 

[] (38) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (31) (MapVariable MapType) event map[string]interface{} 
[_] (31) (Reference UserType) ref <shipmentMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}> @ ShipmentService // write(shipment_queue), 
[__] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), 
[___] (42) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[___] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[____] (9) (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[____] (42) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (-1) (FieldVariable FieldType) UserID string // write(shipment_queue), 
[___] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[___] (-1) (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[____] (10) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[____] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[____] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[_] (42) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (45) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (41) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_] (42) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 

[] (44) (BasicVariable BasicType) UserID string // write(shipment_db), 
[_] (45) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (39) (StructVariable UserType) workerMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string} 
[_] (40) (FieldVariable FieldType) OrderID string // write(shipment_db), 
[__] (41) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[___] (42) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (43) (FieldVariable FieldType) UserID string // write(shipment_db), 
[__] (44) (BasicVariable BasicType) UserID string // write(shipment_db), 
[___] (45) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

