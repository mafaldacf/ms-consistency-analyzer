[] (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (FieldVariable FieldType) priceDB NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ PriceService 

[] (BasicVariable BasicType) routeID string 
[_] (Reference SliceType) ref <routeid []string> @ PriceService 
[__] (BasicVariable BasicType) rt string 
[__] (BasicVariable BasicType) ":" string 

[] (BasicVariable BasicType) trainType string 
[_] (Reference SliceType) ref <trainType []string> @ PriceService 
[__] (BasicVariable BasicType) rt string 
[__] (BasicVariable BasicType) ":" string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "$and" string,  primitive.A} 
[__] (FieldVariable FieldType) primitive.A 
[___] (SliceVariable UserType) primitive.A 
[____] (SliceVariable UserType) primitive.D 
[_____] (StructVariable StructType) struct{ "routeid" string,  string} 
[______] (FieldVariable FieldType) string 
[_______] (BasicVariable BasicType) routeID string 
[________] (Reference SliceType) ref <routeid []string> @ PriceService 
[_________] (BasicVariable BasicType) rt string 
[_________] (BasicVariable BasicType) ":" string 
[____] (SliceVariable UserType) primitive.D 
[_____] (StructVariable StructType) struct{ "traintype" string,  string} 
[______] (FieldVariable FieldType) string 
[_______] (BasicVariable BasicType) trainType string 
[________] (Reference SliceType) ref <trainType []string> @ PriceService 
[_________] (BasicVariable BasicType) rt string 
[_________] (BasicVariable BasicType) ":" string 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

