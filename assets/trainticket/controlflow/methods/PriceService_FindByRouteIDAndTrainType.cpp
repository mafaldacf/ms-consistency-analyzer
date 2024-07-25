[] (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ PriceService 

[] (BasicVariable BasicType) routeID string // read(price_db), 
[_] (Reference SliceType) ref <routeid []string> @ PriceService // read(price_db), 
[__] (BasicVariable BasicType) rt string // read(price_db), 
[__] (BasicVariable BasicType) ":" string // read(price_db), 

[] (BasicVariable BasicType) trainType string // read(price_db), 
[_] (Reference SliceType) ref <trainType []string> @ PriceService // read(price_db), 
[__] (BasicVariable BasicType) rt string // read(price_db), 
[__] (BasicVariable BasicType) ":" string // read(price_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(price_db), 
[_] (StructVariable StructType) struct{ "$and" string,  primitive.A} // read(price_db), 
[__] (FieldVariable FieldType) primitive.A // read(price_db), 
[___] (SliceVariable UserType) primitive.A // read(price_db), 
[____] (SliceVariable UserType) primitive.D // read(price_db), 
[_____] (StructVariable StructType) struct{ "routeid" string,  string} // read(price_db), 
[______] (FieldVariable FieldType) string // read(price_db), 
[_______] (BasicVariable BasicType) routeID string // read(price_db), 
[________] (Reference SliceType) ref <routeid []string> @ PriceService // read(price_db), 
[_________] (BasicVariable BasicType) rt string // read(price_db), 
[_________] (BasicVariable BasicType) ":" string // read(price_db), 
[____] (SliceVariable UserType) primitive.D // read(price_db), 
[_____] (StructVariable StructType) struct{ "traintype" string,  string} // read(price_db), 
[______] (FieldVariable FieldType) string // read(price_db), 
[_______] (BasicVariable BasicType) trainType string // read(price_db), 
[________] (Reference SliceType) ref <trainType []string> @ PriceService // read(price_db), 
[_________] (BasicVariable BasicType) rt string // read(price_db), 
[_________] (BasicVariable BasicType) ":" string // read(price_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig} // read(price_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

