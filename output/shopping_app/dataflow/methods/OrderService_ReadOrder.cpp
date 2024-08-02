[] (-1) (PointerVariable PointerType) c (*shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue} 
[__] (-1) (ServiceVariable ServiceType) billing_service shopping_app.BillingService 
[__] (-1) (ServiceVariable ServiceType) product_service shopping_app.ProductService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (ServiceVariable ServiceType) stock_service shopping_app.StockService 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (-1) (Reference UserType) ref <ctx context.Context> @ ShipmentService 
[__] (36) (Reference UserType) ref <ctx context.Context> @ ShipmentService 
[_] (44) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (-1) (BasicVariable BasicType) orderID string 
[_] (0) (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[__] (38) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[___] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[____] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (45) (Reference BasicType) ref <orderID string> @ Frontend 

[] (-1) (StructVariable UserType) order shopping_app.Order struct{OrderID string, UserID string, ProductID string, Quantity int, Timestamp int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "orderID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "orderID" string 
[___] (0) (BasicVariable BasicType) "orderID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (-1) (BasicVariable BasicType) orderID string 
[____] (0) (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[_____] (38) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), 
[______] (39) (BasicVariable BasicType) OrderID string // write(shipment_db), 
[_______] (40) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), write(shipment_db), 
[____] (45) (Reference BasicType) ref <orderID string> @ Frontend 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = order_database, collection = order_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

