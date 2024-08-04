[] (PointerVariable PointerType) c (*consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase} 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ ConsignPriceService 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = consign, collection = consign} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "index" string,  0 int} 
[__] (FieldVariable FieldType) 0 int 
[___] (BasicVariable BasicType) 0 int 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = consign, collection = consign} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

