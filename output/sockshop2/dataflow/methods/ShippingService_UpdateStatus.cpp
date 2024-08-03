[] (-1) (PointerVariable PointerType) s (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) q Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) queue Queue 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (53) (Reference UserType) ref <ctx context.Context> @ QueueMaster 

[] (50) (BasicVariable BasicType) id string 
[_] (50) (Reference BasicType) ref <ID string> @ QueueMaster 
[__] (50) (Reference FieldType) ref <ID string> @ OrderService // write(shipqueue), write(shipdb), 
[___] (51) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 

[] (0) (BasicVariable BasicType) status string 
[_] (54) (Reference BasicType) ref <"shipped" string> @ QueueMaster 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments} 

[] (-1) (InterfaceVariable UserType) _ .error 

