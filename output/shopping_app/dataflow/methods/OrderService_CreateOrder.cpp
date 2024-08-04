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
[_] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[_] (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[_] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 

[] (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[_] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[_] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[_] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 
[_] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 
[_] (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (BasicVariable BasicType) price int // write(billing_db), 
[_] (Reference BasicType) ref <price int> @ Frontend // write(billing_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) order shopping_app.Order struct{OrderID string, UserID string, ProductID string, Quantity int, Timestamp 1 int} // write(order_db), 
[_] (FieldVariable FieldType) OrderID string // write(order_db), 
[__] (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[___] (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) ProductID string // write(order_db), 
[__] (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 
[___] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (FieldVariable FieldType) Quantity int // write(order_db), 
[__] (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 
[___] (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (FieldVariable FieldType) Timestamp 1 int // write(order_db), 
[__] (BasicVariable BasicType) 1 int // write(order_db), 
[_] (FieldVariable FieldType) UserID string // write(order_db), 
[__] (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[___] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 

[] (StructVariable UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string} 
[_] (FieldVariable FieldType) Category string 
[__] (BasicVariable BasicType) Category string // write(analytics_queue), 
[___] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) analyticsMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string} // write(analytics_queue), 
[_] (FieldVariable FieldType) ProductCategory string // write(analytics_queue), 
[__] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[__] (BasicVariable BasicType) Category string // write(analytics_queue), 
[___] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[_] (FieldVariable FieldType) UserID string // write(analytics_queue), 
[__] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[__] (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[___] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (StructVariable UserType) shipmentMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string} // write(shipment_queue), 
[_] (FieldVariable FieldType) OrderID string // write(shipment_queue), 
[__] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[__] (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 
[___] (Reference BasicType) ref <cartID string> @ Frontend // write(order_db), write(shipment_queue), 
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService // write(order_db), write(shipment_queue), write(shipment_db), 
[_] (FieldVariable FieldType) UserID string // write(shipment_queue), 
[__] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[__] (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[___] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

