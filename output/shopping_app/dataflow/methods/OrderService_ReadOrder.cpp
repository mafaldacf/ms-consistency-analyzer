[] (PointerVariable PointerType) c (*shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue}) 
[_] (StructVariable UserType) shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue} 
[__] (FieldVariable FieldType) analytics_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (FieldVariable FieldType) billing_service shopping_app.BillingService 
[___] (ServiceVariable ServiceType) billing_service shopping_app.BillingService 
[__] (FieldVariable FieldType) order_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 
[__] (FieldVariable FieldType) product_service shopping_app.ProductService 
[___] (ServiceVariable ServiceType) product_service shopping_app.ProductService 
[__] (FieldVariable FieldType) shipment_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (FieldVariable FieldType) stock_service shopping_app.StockService 
[___] (ServiceVariable ServiceType) stock_service shopping_app.StockService 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ ShipmentService 
[__] (Reference UserType) ref <ctx context.Context> @ ShipmentService 
[_] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) orderID string 
[_] (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[__] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[___] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[____] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (Reference BasicType) ref <orderID string> @ Frontend 

[] (StructVariable UserType) order shopping_app.Order struct{OrderID string, UserID string, ProductID string, Quantity int, Timestamp 1 int} 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "orderID" string, Value string} 
[__] (FieldVariable FieldType) Key "orderID" string 
[___] (BasicVariable BasicType) "orderID" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) orderID string 
[____] (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[_____] (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[______] (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_______] (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[____] (Reference BasicType) ref <orderID string> @ Frontend 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = order_database, collection = order_collection} 

[] (InterfaceVariable UserType) _ .error 

