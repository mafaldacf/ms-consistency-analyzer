[] (-1) (PointerVariable PointerType) s (*shopping_app.BillingServiceImpl struct{bill_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shopping_app.BillingServiceImpl struct{bill_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) bill_db NoSQLDatabase 

[] (12) (InterfaceVariable UserType) ctx context.Context 
[_] (12) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (6) (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (-1) (BasicVariable BasicType) userID string // write(billing_db), 
[_] (-1) (Reference BasicType) ref <userID string> @ OrderService // write(order_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(billing_db), 
[__] (8) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), 
[__] (28) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 
[__] (43) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (13) (BasicVariable BasicType) productID string // write(billing_db), 
[_] (13) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (9) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (14) (BasicVariable BasicType) quantity int // write(billing_db), 
[_] (14) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (10) (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BasicVariable BasicType) pricePerUnit int // write(billing_db), 
[_] (16) (Reference BasicType) ref <price int> @ OrderService // write(billing_db), 
[__] (11) (Reference BasicType) ref <price int> @ Frontend // write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = bill_database, collection = bill_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) bill shopping_app.Bill struct{UserID string, ProductID string, Quantity int, PricePerUnit int, TotalCost int} // write(billing_db), 
[_] (0) (FieldVariable FieldType) UserID string // write(billing_db), 
[__] (-1) (BasicVariable BasicType) userID string // write(billing_db), 
[___] (-1) (Reference BasicType) ref <userID string> @ OrderService // write(order_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(billing_db), 
[____] (8) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), 
[____] (28) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 
[____] (43) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) ProductID string // write(billing_db), 
[__] (13) (BasicVariable BasicType) productID string // write(billing_db), 
[___] (13) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (9) (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(billing_db), 
[__] (14) (BasicVariable BasicType) quantity int // write(billing_db), 
[___] (14) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (10) (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) PricePerUnit int // write(billing_db), 
[__] (-1) (BasicVariable BasicType) pricePerUnit int // write(billing_db), 
[___] (16) (Reference BasicType) ref <price int> @ OrderService // write(billing_db), 
[____] (11) (Reference BasicType) ref <price int> @ Frontend // write(billing_db), 
[_] (0) (FieldVariable FieldType) TotalCost (&int) // write(billing_db), 
[__] (0) (AddressVariable AddressType) quantity (&int) // write(billing_db), 
[___] (14) (BasicVariable BasicType) quantity int // write(billing_db), 
[____] (14) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[_____] (10) (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

