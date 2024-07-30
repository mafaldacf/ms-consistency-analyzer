[] (-1) (PointerVariable PointerType) service (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) q Queue 

[] (30) (InterfaceVariable UserType) ctx context.Context 
[_] (30) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (25) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(shipqueue), write(shipdb), 
[_] (36) (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status string}> @ OrderService // write(shipqueue), write(shipdb), 
[__] (37) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[___] (38) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (39) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[___] (32) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[____] (26) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[__] (40) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (41) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (-1) (InterfaceVariable UserType) _ .error 

