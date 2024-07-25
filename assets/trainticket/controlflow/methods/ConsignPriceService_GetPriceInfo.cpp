[] (PointerVariable PointerType) c (*consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase}) 
[_] (StructVariable UserType) consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = consign, collection = consign} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "index" string,  0 int} 
[__] (FieldVariable FieldType) 0 int 
[___] (BasicVariable BasicType) 0 int 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = consign, collection = consign} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64} 
[_] (FieldVariable FieldType) InitialWeight float64 
[__] (BasicVariable BasicType) InitialWeight float64 
[_] (FieldVariable FieldType) InitialPrice float64 
[__] (BasicVariable BasicType) InitialPrice float64 
[_] (FieldVariable FieldType) WithinPrice float64 
[__] (BasicVariable BasicType) WithinPrice float64 
[_] (FieldVariable FieldType) BeyondPrice float64 
[__] (BasicVariable BasicType) BeyondPrice float64 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) info string 
[_] (BasicVariable BasicType) "The price of weight within %.2f is %.2f. The price of extra weight within the region is %.2f and beyond the region is %.2f" string 
[_] (FieldVariable FieldType) InitialWeight float64 
[__] (BasicVariable BasicType) InitialWeight float64 
[_] (FieldVariable FieldType) InitialPrice float64 
[__] (BasicVariable BasicType) InitialPrice float64 
[_] (FieldVariable FieldType) WithinPrice float64 
[__] (BasicVariable BasicType) WithinPrice float64 
[_] (FieldVariable FieldType) BeyondPrice float64 
[__] (BasicVariable BasicType) BeyondPrice float64 

