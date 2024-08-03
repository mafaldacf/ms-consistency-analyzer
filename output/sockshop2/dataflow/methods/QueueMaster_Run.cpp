[] (-1) (PointerVariable PointerType) q (*queuemaster.queueMasterImpl struct{q Queue, shipping shipping.ShippingService, exitOnError false bool, processed 0 int}) 
[_] (0) (StructVariable UserType) queuemaster.queueMasterImpl struct{q Queue, shipping shipping.ShippingService, exitOnError false bool, processed 0 int} 
[__] (0) (FieldVariable FieldType) q Queue 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) queue Queue 
[__] (0) (FieldVariable FieldType) shipping shipping.ShippingService 
[___] (-1) (ServiceVariable ServiceType) shipping shipping.ShippingService 
[__] (0) (FieldVariable FieldType) exitOnError false bool 
[___] (0) (BasicVariable BasicType) false bool 
[__] (0) (FieldVariable FieldType) processed 0 int 
[___] (0) (BasicVariable BasicType) 0 int 

[] (53) (InterfaceVariable UserType) ctx context.Context 

[] (46) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} 
[_] (52) (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status string}> @ QueueMaster // write(shipqueue), write(shipdb), 
[__] (46) (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}> @ OrderService // write(shipqueue), write(shipdb), 
[___] (48) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[____] (49) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (50) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[____] (51) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[___] (47) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[____] (42) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[_____] (36) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (46) (Reference UserType) ref <shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}> @ OrderService // write(shipqueue), write(shipdb), 
[__] (50) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[___] (51) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (47) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[___] (42) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[____] (36) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[__] (48) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[___] (49) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 
[_] (50) (FieldVariable FieldType) ID string 
[__] (50) (Reference FieldType) ref <ID string> @ OrderService // write(shipqueue), write(shipdb), 
[___] (51) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[__] (50) (BasicVariable BasicType) ID string 
[___] (50) (Reference FieldType) ref <ID string> @ OrderService // write(shipqueue), write(shipdb), 
[____] (51) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 

