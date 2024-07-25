[] (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ PriceService 

[] (BasicVariable BasicType) id string // read(price_db), 
[_] (Reference BasicType) ref <ID string> @ PriceService // write(price_db), read(price_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(price_db), 
[_] (StructVariable StructType) struct{ "id" string,  string} // read(price_db), 
[__] (FieldVariable FieldType) string // read(price_db), 
[___] (BasicVariable BasicType) id string // read(price_db), 
[____] (Reference BasicType) ref <ID string> @ PriceService // write(price_db), read(price_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig} // read(price_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

