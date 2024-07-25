[] (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ PriceService 

[] (BasicVariable BasicType) id string 
[_] (Reference FieldType) ref <ID string> @ PriceService // write(price_db), 
[__] (BasicVariable BasicType) ID string // write(price_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "id" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) id string 
[____] (Reference FieldType) ref <ID string> @ PriceService // write(price_db), 
[_____] (BasicVariable BasicType) ID string // write(price_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

