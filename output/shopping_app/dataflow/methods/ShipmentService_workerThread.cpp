[] (PointerVariable PointerType) s (*shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers 4 int}) 
[_] (StructVariable UserType) shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers 4 int} 
[__] (FieldVariable FieldType) num_workers 4 int 
[___] (BasicVariable BasicType) 4 int 
[__] (FieldVariable FieldType) order_service shopping_app.OrderService 
[___] (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (FieldVariable FieldType) shipment_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 
[__] (FieldVariable FieldType) shipment_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ChanVariable ChanType) forever chan struct{} 

[] (MapVariable MapType) event map[string]interface{} 
[_] (Reference UserType) ref <shipmentMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}> @ ShipmentService // write(shipment_queue), 
[__] (FieldVariable FieldType) OrderID string // write(shipment_queue), 
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[___] (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[____] (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[____] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (FieldVariable FieldType) UserID string // write(shipment_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[___] (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[____] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[____] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[____] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[_] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 

[] (BasicVariable BasicType) UserID string // write(shipment_db), 
[_] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (StructVariable UserType) workerMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string} 
[_] (FieldVariable FieldType) OrderID string // write(shipment_db), 
[__] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[___] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) UserID string // write(shipment_db), 
[__] (BasicVariable BasicType) UserID string // write(shipment_db), 
[___] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

