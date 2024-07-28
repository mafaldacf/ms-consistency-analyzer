[] (-1) (PointerVariable PointerType) service (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) q Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (16) (InterfaceVariable UserType) ctx context.Context 
[_] (16) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (11) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(shipqueue), write(shipdb), 
[_] (22) (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status string}> @ OrderService // write(shipqueue), write(shipdb), 
[__] (23) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[___] (24) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (25) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[___] (18) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), read(user_db), 
[____] (12) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), read(user_db), 
[__] (26) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (27) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (-1) (InterfaceVariable UserType) _ .error 

