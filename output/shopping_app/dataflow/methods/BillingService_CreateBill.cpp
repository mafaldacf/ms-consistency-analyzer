[] (PointerVariable PointerType) s (*shopping_app.BillingServiceImpl struct{bill_db NoSQLDatabase}) 
[_] (StructVariable UserType) shopping_app.BillingServiceImpl struct{bill_db NoSQLDatabase} 
[__] (FieldVariable FieldType) bill_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) bill_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ Frontend 

[] (BasicVariable BasicType) userID string // write(billing_db), 
[_] (Reference BasicType) ref <userID string> @ OrderService // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[__] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[__] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[__] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

[] (BasicVariable BasicType) productID string // write(billing_db), 
[_] (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (BasicVariable BasicType) quantity int // write(billing_db), 
[_] (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 

[] (BasicVariable BasicType) pricePerUnit int // write(billing_db), 
[_] (Reference BasicType) ref <price int> @ OrderService // write(billing_db), 
[__] (Reference BasicType) ref <price int> @ Frontend // write(billing_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = bill_database, collection = bill_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) bill shopping_app.Bill struct{UserID string, ProductID string, Quantity int, PricePerUnit int, TotalCost (&int)} // write(billing_db), 
[_] (FieldVariable FieldType) PricePerUnit int // write(billing_db), 
[__] (BasicVariable BasicType) pricePerUnit int // write(billing_db), 
[___] (Reference BasicType) ref <price int> @ OrderService // write(billing_db), 
[____] (Reference BasicType) ref <price int> @ Frontend // write(billing_db), 
[_] (FieldVariable FieldType) ProductID string // write(billing_db), 
[__] (BasicVariable BasicType) productID string // write(billing_db), 
[___] (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (Reference BasicType) ref <productID string> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (FieldVariable FieldType) Quantity int // write(billing_db), 
[__] (BasicVariable BasicType) quantity int // write(billing_db), 
[___] (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (FieldVariable FieldType) TotalCost (&int) // write(billing_db), 
[__] (AddressVariable AddressType) quantity (&int) // write(billing_db), 
[___] (BasicVariable BasicType) quantity int // write(billing_db), 
[____] (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[_____] (Reference BasicType) ref <quantity int> @ Frontend // write(order_db), write(stock_db), write(billing_db), 
[_] (FieldVariable FieldType) UserID string // write(billing_db), 
[__] (BasicVariable BasicType) userID string // write(billing_db), 
[___] (Reference BasicType) ref <userID string> @ OrderService // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[____] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[____] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[____] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 

