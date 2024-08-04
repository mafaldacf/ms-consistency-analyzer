[] (PointerVariable PointerType) service (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (FieldVariable FieldType) q Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(shipqueue), write(shipdb), 
[_] (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}> @ OrderService // write(shipqueue), write(shipdb), 
[__] (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[____] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[__] (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (InterfaceVariable UserType) _ .error 

