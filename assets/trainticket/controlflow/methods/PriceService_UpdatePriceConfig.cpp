[] (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 
[_] (FieldVariable FieldType) ID string 
[__] (BasicVariable BasicType) ID string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string, ID string} 
[__] (FieldVariable FieldType) "id" string 
[___] (BasicVariable BasicType) "id" string 
[__] (FieldVariable FieldType) ID string 
[___] (BasicVariable BasicType) ID string 

