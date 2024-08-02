[] (-1) (PointerVariable PointerType) s (*shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers 4 int}) 
[_] (0) (StructVariable UserType) shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers 4 int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (36) (Reference UserType) ref <ctx context.Context> @ ShipmentService 

[] (-1) (StructVariable UserType) message shopping_app.ShipmentMessage struct{OrderID string, UserID string} 
[_] (37) (Reference UserType) ref <workerMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}> @ ShipmentService 
[__] (38) (FieldVariable FieldType) OrderID string // write(shipment_db), 
[___] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[____] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (41) (FieldVariable FieldType) UserID string // write(shipment_db), 
[___] (42) (BasicVariable BasicType) UserID string // write(shipment_db), 
[____] (43) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) OrderID string 
[__] (38) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[___] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[____] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (0) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[___] (38) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[____] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_____] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) UserID string 
[__] (41) (Reference FieldType) ref <UserID string> @ ShipmentService // write(shipment_db), 
[___] (42) (BasicVariable BasicType) UserID string // write(shipment_db), 
[____] (43) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[__] (0) (BasicVariable BasicType) UserID string // write(shipment_db), 
[___] (41) (Reference FieldType) ref <UserID string> @ ShipmentService // write(shipment_db), 
[____] (42) (BasicVariable BasicType) UserID string // write(shipment_db), 
[_____] (43) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipment_database, collection = shipment_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) shipment shopping_app.Shipment struct{OrderID string, UserID string, Status string} // write(shipment_db), 
[_] (0) (FieldVariable FieldType) Status "pending" string // write(shipment_db), 
[__] (0) (BasicVariable BasicType) "pending" string // write(shipment_db), 
[_] (0) (FieldVariable FieldType) OrderID string // write(shipment_db), 
[__] (0) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[___] (38) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[____] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_____] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) UserID string // write(shipment_db), 
[__] (0) (BasicVariable BasicType) UserID string // write(shipment_db), 
[___] (41) (Reference FieldType) ref <UserID string> @ ShipmentService // write(shipment_db), 
[____] (42) (BasicVariable BasicType) UserID string // write(shipment_db), 
[_____] (43) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

