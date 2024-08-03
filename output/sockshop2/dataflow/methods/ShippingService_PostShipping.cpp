[] (-1) (PointerVariable PointerType) service (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) q Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) queue Queue 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (40) (InterfaceVariable UserType) ctx context.Context 
[_] (40) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (35) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (52) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(shipqueue), write(shipdb), 
[_] (46) (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}> @ OrderService // write(shipqueue), write(shipdb), 
[__] (50) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[___] (51) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (47) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[___] (42) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[____] (36) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[__] (48) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (49) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (-1) (InterfaceVariable UserType) _ .error 

