[] (-1) (PointerVariable PointerType) c (*threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, billing_service threechain2.BillingService, order_db NoSQLDatabase, shipment_queue Queue}) 
[_] (0) (StructVariable UserType) threechain2.OrderServiceImpl struct{stock_service threechain2.StockService, billing_service threechain2.BillingService, order_db NoSQLDatabase, shipment_queue Queue} 
[__] (-1) (ServiceVariable ServiceType) stock_service threechain2.StockService 
[__] (-1) (ServiceVariable ServiceType) billing_service threechain2.BillingService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 

[] (7) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ CartService 

[] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[_] (2) (Reference BasicType) ref <cartID string> @ CartService // write(order_db), write(shipment_queue), read(shipment_queue), 
[_] (22) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 

[] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), write(billing_db), 
[_] (3) (Reference BasicType) ref <Username string> @ CartService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), 
[_] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (8) (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 
[_] (4) (Reference BasicType) ref <ProductID string> @ CartService // write(order_db), write(stock_db), write(billing_db), 

[] (9) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 
[_] (5) (Reference BasicType) ref <Quantity int> @ CartService // write(order_db), write(stock_db), write(billing_db), 

[] (11) (BasicVariable BasicType) price int // write(billing_db), 
[_] (6) (Reference BasicType) ref <PricePerUnit int> @ CartService // write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) order threechain2.Order struct{OrderID string, Username string, ProductID string, Quantity int, Timestamp int64} // write(order_db), 
[_] (0) (FieldVariable FieldType) OrderID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (2) (Reference BasicType) ref <cartID string> @ CartService // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (22) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (0) (FieldVariable FieldType) Username string // write(order_db), 
[__] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), write(billing_db), 
[___] (3) (Reference BasicType) ref <Username string> @ CartService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), 
[___] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) ProductID string // write(order_db), 
[__] (8) (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 
[___] (4) (Reference BasicType) ref <ProductID string> @ CartService // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(order_db), 
[__] (9) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 
[___] (5) (Reference BasicType) ref <Quantity int> @ CartService // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) Timestamp 1 int // write(order_db), 
[__] (0) (BasicVariable BasicType) 1 int // write(order_db), 

[] (12) (StructVariable UserType) message threechain2.ShipmentMessage struct{OrderID string, Username string} // write(shipment_queue), read(shipment_queue), 
[_] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), read(shipment_queue), 
[__] (22) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[__] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (2) (Reference BasicType) ref <cartID string> @ CartService // write(order_db), write(shipment_queue), read(shipment_queue), 
[___] (22) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), read(shipment_queue), write(shipment_db), read(order_db), 
[_] (-1) (FieldVariable FieldType) Username string // write(shipment_queue), read(shipment_queue), 
[__] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[__] (-1) (BasicVariable BasicType) username string // write(order_db), write(shipment_queue), read(shipment_queue), write(billing_db), 
[___] (3) (Reference BasicType) ref <Username string> @ CartService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), 
[___] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

