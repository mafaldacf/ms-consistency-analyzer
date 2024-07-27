[] (-1) (PointerVariable PointerType) c (*threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue}) 
[_] (0) (StructVariable UserType) threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, order_db NoSQLDatabase, shipment_queue Queue} 
[__] (-1) (ServiceVariable ServiceType) stock_service threechain2.StockService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (-1) (Reference UserType) ref <ctx context.Context> @ ShipmentService 
[__] (11) (Reference UserType) ref <ctx context.Context> @ ShipmentService 

[] (-1) (BasicVariable BasicType) orderID string // read(order_db), 
[_] (0) (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(order_db), 
[__] (16) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(order_db), 
[___] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[____] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 

[] (-1) (StructVariable UserType) order threechain2.Order struct{OrderID string, Username string, Product string, Quantity int, Timestamp int64} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(order_db), 
[_] (0) (StructVariable StructType) struct{Key "orderID" string, Value string} // read(order_db), 
[__] (0) (FieldVariable FieldType) Key "orderID" string // read(order_db), 
[___] (0) (BasicVariable BasicType) "orderID" string // read(order_db), 
[__] (0) (FieldVariable FieldType) Value string // read(order_db), 
[___] (-1) (BasicVariable BasicType) orderID string // read(order_db), 
[____] (0) (Reference BasicType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(order_db), 
[_____] (16) (Reference FieldType) ref <OrderID string> @ ShipmentService // write(shipment_db), read(order_db), 
[______] (17) (BasicVariable BasicType) OrderID string // write(shipment_db), read(order_db), 
[_______] (18) (InterfaceVariable InterfaceType) OrderID interface{} // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = order_database, collection = order_collection} // read(order_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

