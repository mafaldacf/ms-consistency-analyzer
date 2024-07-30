[] (-1) (PointerVariable PointerType) c (*shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue}) 
[_] (0) (StructVariable UserType) shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue} 
[__] (-1) (ServiceVariable ServiceType) stock_service shopping_app.StockService 
[__] (-1) (ServiceVariable ServiceType) billing_service shopping_app.BillingService 
[__] (-1) (ServiceVariable ServiceType) product_service shopping_app.ProductService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) order_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) shipment_queue Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (14) (InterfaceVariable UserType) ctx context.Context 
[_] (8) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[_] (9) (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[_] (42) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 

[] (-1) (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[_] (10) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[_] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[_] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (15) (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 
[_] (11) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (16) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 
[_] (12) (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (18) (BasicVariable BasicType) price int // write(billing_db), 
[_] (13) (Reference BasicType) ref <price int> @ Frontend // write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) order shopping_app.Order struct{OrderID string, UserID string, ProductID string, Quantity int, Timestamp int64} // write(order_db), 
[_] (0) (FieldVariable FieldType) ProductID string // write(order_db), 
[__] (15) (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 
[___] (11) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(order_db), 
[__] (16) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 
[___] (12) (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) Timestamp 1 int // write(order_db), 
[__] (0) (BasicVariable BasicType) 1 int // write(order_db), 
[_] (0) (FieldVariable FieldType) OrderID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[___] (9) (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[___] (42) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) UserID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[___] (10) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[___] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (-1) (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (-1) (FieldVariable FieldType) Category string 
[__] (-1) (BasicVariable BasicType) Category string // write(analytics_queue), 
[___] (27) (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (19) (StructVariable UserType) analyticsMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string} // write(analytics_queue), 
[_] (-1) (FieldVariable FieldType) UserID string // write(analytics_queue), 
[__] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[__] (-1) (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[___] (10) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[___] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[_] (-1) (FieldVariable FieldType) ProductCategory string // write(analytics_queue), 
[__] (27) (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[__] (-1) (BasicVariable BasicType) Category string // write(analytics_queue), 
[___] (27) (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 

[] (31) (StructVariable UserType) shipmentMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string} // write(shipment_queue), 
[_] (-1) (FieldVariable FieldType) OrderID string // write(shipment_queue), 
[__] (42) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (-1) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[___] (9) (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[___] (42) (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (-1) (FieldVariable FieldType) UserID string // write(shipment_queue), 
[__] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[__] (-1) (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[___] (10) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[___] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

