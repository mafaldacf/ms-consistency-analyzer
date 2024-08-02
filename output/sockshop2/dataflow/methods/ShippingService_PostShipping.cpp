[] (-1) (PointerVariable PointerType) service (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) q Queue 

[] (22) (InterfaceVariable UserType) ctx context.Context 
[_] (22) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (17) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(shipqueue), write(shipdb), 
[_] (28) (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status string}> @ OrderService // write(shipqueue), write(shipdb), 
[__] (29) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (30) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 
[__] (31) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[___] (32) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (33) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[___] (24) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[____] (18) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (-1) (InterfaceVariable UserType) _ .error 

