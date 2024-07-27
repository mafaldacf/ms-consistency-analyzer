[] (-1) (PointerVariable PointerType) c (*consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) priceConfig consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64} // write(consignprice_db), 
[_] (-1) (FieldVariable FieldType) Index int64 // write(consignprice_db), 
[__] (0) (BasicVariable BasicType) 0 int // write(consignprice_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = consign, collection = consign} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "index" string,  0 int} 
[__] (0) (FieldVariable FieldType) 0 int 
[___] (0) (BasicVariable BasicType) 0 int 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = consign, collection = consign} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) ok bool 

[] (-1) (InterfaceVariable UserType) err .error 

