[] (-1) (PointerVariable PointerType) s (*threechain2.BillingServiceImpl struct{bill_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) threechain2.BillingServiceImpl struct{bill_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) bill_db NoSQLDatabase 

[] (7) (InterfaceVariable UserType) ctx context.Context 
[_] (7) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (1) (Reference UserType) ref <ctx context.Context> @ CartService 

[] (-1) (BasicVariable BasicType) username string // write(billing_db), 
[_] (-1) (Reference BasicType) ref <username string> @ OrderService // write(order_db), write(shipment_queue), read(shipment_queue), write(billing_db), 
[__] (3) (Reference BasicType) ref <Username string> @ CartService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), 
[__] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 

[] (8) (BasicVariable BasicType) productID string // write(billing_db), 
[_] (8) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (4) (Reference BasicType) ref <ProductID string> @ CartService // write(order_db), write(stock_db), write(billing_db), 

[] (9) (BasicVariable BasicType) quantity int // write(billing_db), 
[_] (9) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[__] (5) (Reference BasicType) ref <Quantity int> @ CartService // write(order_db), write(stock_db), write(billing_db), 

[] (-1) (BasicVariable BasicType) pricePerUnit int // write(billing_db), 
[_] (11) (Reference BasicType) ref <price int> @ OrderService // write(billing_db), 
[__] (6) (Reference BasicType) ref <PricePerUnit int> @ CartService // write(billing_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = bill_database, collection = bill_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) bill threechain2.Bill struct{Username string, ProductID string, Quantity int, PricePerUnit int, TotalCost int} // write(billing_db), 
[_] (0) (FieldVariable FieldType) Quantity int // write(billing_db), 
[__] (9) (BasicVariable BasicType) quantity int // write(billing_db), 
[___] (9) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (5) (Reference BasicType) ref <Quantity int> @ CartService // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) PricePerUnit int // write(billing_db), 
[__] (-1) (BasicVariable BasicType) pricePerUnit int // write(billing_db), 
[___] (11) (Reference BasicType) ref <price int> @ OrderService // write(billing_db), 
[____] (6) (Reference BasicType) ref <PricePerUnit int> @ CartService // write(billing_db), 
[_] (0) (FieldVariable FieldType) TotalCost (&int) // write(billing_db), 
[__] (0) (AddressVariable AddressType) quantity (&int) // write(billing_db), 
[___] (9) (BasicVariable BasicType) quantity int // write(billing_db), 
[____] (9) (Reference BasicType) ref <quantity int> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[_____] (5) (Reference BasicType) ref <Quantity int> @ CartService // write(order_db), write(stock_db), write(billing_db), 
[_] (0) (FieldVariable FieldType) Username string // write(billing_db), 
[__] (-1) (BasicVariable BasicType) username string // write(billing_db), 
[___] (-1) (Reference BasicType) ref <username string> @ OrderService // write(order_db), write(shipment_queue), read(shipment_queue), write(billing_db), 
[____] (3) (Reference BasicType) ref <Username string> @ CartService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), 
[____] (25) (Reference InterfaceType) ref <Username interface{}> @ ShipmentService // write(order_db), write(billing_db), write(shipment_queue), read(shipment_queue), write(shipment_db), 
[_] (0) (FieldVariable FieldType) ProductID string // write(billing_db), 
[__] (8) (BasicVariable BasicType) productID string // write(billing_db), 
[___] (8) (Reference BasicType) ref <productID string> @ OrderService // write(order_db), write(stock_db), write(billing_db), 
[____] (4) (Reference BasicType) ref <ProductID string> @ CartService // write(order_db), write(stock_db), write(billing_db), 

