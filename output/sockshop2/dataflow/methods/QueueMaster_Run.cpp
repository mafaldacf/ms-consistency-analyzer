[] (PointerVariable PointerType) q (*queuemaster.queueMasterImpl struct{q Queue, shipping shipping.ShippingService, exitOnError false bool, processed 0 int}) 
[_] (StructVariable UserType) queuemaster.queueMasterImpl struct{q Queue, shipping shipping.ShippingService, exitOnError false bool, processed 0 int} 
[__] (FieldVariable FieldType) exitOnError false bool 
[___] (BasicVariable BasicType) false bool 
[__] (FieldVariable FieldType) processed 0 int 
[___] (BasicVariable BasicType) 0 int 
[__] (FieldVariable FieldType) q Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) queue Queue 
[__] (FieldVariable FieldType) shipping shipping.ShippingService 
[___] (ServiceVariable ServiceType) shipping shipping.ShippingService 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} 
[_] (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status string}> @ QueueMaster // write(shipqueue), write(shipdb), 
[__] (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}> @ OrderService // write(shipqueue), write(shipdb), 
[___] (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[____] (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[___] (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[____] (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[_____] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[___] (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[____] (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 
[_] (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}> @ OrderService // write(shipqueue), write(shipdb), 
[__] (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[____] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[__] (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 
[_] (FieldVariable FieldType) ID string 
[__] (Reference FieldType) ref <ID string> @ OrderService // write(shipqueue), write(shipdb), 
[___] (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (BasicVariable BasicType) ID string 
[___] (Reference FieldType) ref <ID string> @ OrderService // write(shipqueue), write(shipdb), 
[____] (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 

