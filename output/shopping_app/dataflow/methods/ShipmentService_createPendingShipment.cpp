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
[_] (Reference UserType) ref <ctx context.Context> @ ShipmentService 

[] (StructVariable UserType) message shopping_app.ShipmentMessage struct{OrderID string, UserID string} 
[_] (Reference UserType) ref <workerMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}> @ ShipmentService 
[__] (FieldVariable FieldType) OrderID string // write(shipment_db), 
[___] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[____] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (FieldVariable FieldType) UserID string // write(shipment_db), 
[___] (BasicVariable BasicType) UserID string // write(shipment_db), 
[____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) OrderID string 
[__] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[___] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[____] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[___] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[____] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_____] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) UserID string 
[__] (Reference FieldType) ref <UserID string> @ ShipmentService // write(shipment_db), 
[___] (BasicVariable BasicType) UserID string // write(shipment_db), 
[____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[__] (BasicVariable BasicType) UserID string // write(shipment_db), 
[___] (Reference FieldType) ref <UserID string> @ ShipmentService // write(shipment_db), 
[____] (BasicVariable BasicType) UserID string // write(shipment_db), 
[_____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipment_database, collection = shipment_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) shipment shopping_app.Shipment struct{OrderID string, UserID string, Status "pending" string} // write(shipment_db), 
[_] (FieldVariable FieldType) OrderID string // write(shipment_db), 
[__] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[___] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[____] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_____] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) Status "pending" string // write(shipment_db), 
[__] (BasicVariable BasicType) "pending" string // write(shipment_db), 
[_] (FieldVariable FieldType) UserID string // write(shipment_db), 
[__] (BasicVariable BasicType) UserID string // write(shipment_db), 
[___] (Reference FieldType) ref <UserID string> @ ShipmentService // write(shipment_db), 
[____] (BasicVariable BasicType) UserID string // write(shipment_db), 
[_____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

