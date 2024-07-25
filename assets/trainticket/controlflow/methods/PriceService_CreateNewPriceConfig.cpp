[] (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} // write(price_db), 
[_] (FieldVariable FieldType) ID string // write(price_db), 
[__] (BasicVariable BasicType) ID string // write(price_db), read(price_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) _ price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) ID string // write(price_db), read(price_db), 

[] (BasicVariable BasicType) ok bool 

[] (InterfaceVariable UserType) err .error 

