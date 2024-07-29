[] (-1) (PointerVariable PointerType) s (*shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 

[] (36) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (29) (MapVariable MapType) event map[string]interface{} // read(shipment_queue), 
[_] (29) (Reference UserType) ref <shipmentMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}> @ ShipmentService // write(shipment_queue), read(shipment_queue), 
[__] (-1) (FieldVariable FieldType) UserID string // write(shipment_queue), read(shipment_queue), 
[___] (43) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[___] (-1) (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(billing_db), 
[____] (8) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), 
[____] (28) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 
[____] (43) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[__] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[___] (40) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[___] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[____] (7) (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), read(shipment_queue), 
[____] (40) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (43) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[_] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 

[] (42) (BasicVariable BasicType) UserID string // write(shipment_db), 
[_] (43) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (37) (StructVariable UserType) workerMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string} 
[_] (38) (FieldVariable FieldType) OrderID string // write(shipment_db), read(order_db), 
[__] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[___] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (41) (FieldVariable FieldType) UserID string // write(shipment_db), 
[__] (42) (BasicVariable BasicType) UserID string // write(shipment_db), 
[___] (43) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(shipment_db), 

