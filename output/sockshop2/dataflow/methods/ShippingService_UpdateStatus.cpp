[] (PointerVariable PointerType) s (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (FieldVariable FieldType) q Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) queue Queue 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ QueueMaster 

[] (BasicVariable BasicType) id string 
[_] (Reference BasicType) ref <ID string> @ QueueMaster 
[__] (Reference FieldType) ref <ID string> @ OrderService // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 

[] (BasicVariable BasicType) status string 
[_] (Reference BasicType) ref <"shipped" string> @ QueueMaster 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (InterfaceVariable UserType) _ .error 

