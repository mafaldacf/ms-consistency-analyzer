[] (-1) (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (1) (Reference UserType) ref <ctx context.Context> @ PriceService 

[] (-1) (BasicVariable BasicType) routeID string 
[_] (2) (Reference SliceType) ref <routeid []string> @ PriceService 
[__] (3) (BasicVariable BasicType) rt string 
[__] (4) (BasicVariable BasicType) ":" string 

[] (-1) (BasicVariable BasicType) trainType string 
[_] (5) (Reference SliceType) ref <trainType []string> @ PriceService 
[__] (6) (BasicVariable BasicType) rt string 
[__] (7) (BasicVariable BasicType) ":" string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "$and" string,  primitive.A} 
[__] (0) (FieldVariable FieldType) primitive.A 
[___] (0) (SliceVariable UserType) primitive.A 
[____] (0) (SliceVariable UserType) primitive.D 
[_____] (0) (StructVariable StructType) struct{ "routeid" string,  string} 
[______] (0) (FieldVariable FieldType) string 
[_______] (-1) (BasicVariable BasicType) routeID string 
[________] (2) (Reference SliceType) ref <routeid []string> @ PriceService 
[_________] (3) (BasicVariable BasicType) rt string 
[_________] (4) (BasicVariable BasicType) ":" string 
[____] (0) (SliceVariable UserType) primitive.D 
[_____] (0) (StructVariable StructType) struct{ "traintype" string,  string} 
[______] (0) (FieldVariable FieldType) string 
[_______] (-1) (BasicVariable BasicType) trainType string 
[________] (5) (Reference SliceType) ref <trainType []string> @ PriceService 
[_________] (6) (BasicVariable BasicType) rt string 
[_________] (7) (BasicVariable BasicType) ":" string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

