[] (PointerVariable PointerType) s (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (FieldVariable FieldType) q Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) id string 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (InterfaceVariable UserType) _ .error 

[] (BlueprintBackendVariable BlueprintBackendType) cursor NoSQLCursor {database = shipping_service, collection = shipments} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} 

