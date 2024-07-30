[] (-1) (PointerVariable PointerType) s (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) q Queue 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) id string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) cursor NoSQLCursor {database = shipping_service, collection = shipments} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} 

