[] (-1) (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (3) (Reference UserType) ref <ctx context.Context> @ PriceService 

[] (-1) (BasicVariable BasicType) routeID string // read(price_db), 
[_] (4) (Reference SliceType) ref <routeid []string> @ PriceService // read(price_db), 
[__] (5) (BasicVariable BasicType) rt string // read(price_db), 
[__] (6) (BasicVariable BasicType) ":" string // read(price_db), 

[] (-1) (BasicVariable BasicType) trainType string // read(price_db), 
[_] (7) (Reference SliceType) ref <trainType []string> @ PriceService // read(price_db), 
[__] (8) (BasicVariable BasicType) rt string // read(price_db), 
[__] (9) (BasicVariable BasicType) ":" string // read(price_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(price_db), 
[_] (0) (StructVariable StructType) struct{ "$and" string,  primitive.A} // read(price_db), 
[__] (0) (FieldVariable FieldType) primitive.A // read(price_db), 
[___] (0) (SliceVariable UserType) primitive.A // read(price_db), 
[____] (0) (SliceVariable UserType) primitive.D // read(price_db), 
[_____] (0) (StructVariable StructType) struct{ "routeid" string,  string} // read(price_db), 
[______] (0) (FieldVariable FieldType) string // read(price_db), 
[_______] (-1) (BasicVariable BasicType) routeID string // read(price_db), 
[________] (4) (Reference SliceType) ref <routeid []string> @ PriceService // read(price_db), 
[_________] (5) (BasicVariable BasicType) rt string // read(price_db), 
[_________] (6) (BasicVariable BasicType) ":" string // read(price_db), 
[____] (0) (SliceVariable UserType) primitive.D // read(price_db), 
[_____] (0) (StructVariable StructType) struct{ "traintype" string,  string} // read(price_db), 
[______] (0) (FieldVariable FieldType) string // read(price_db), 
[_______] (-1) (BasicVariable BasicType) trainType string // read(price_db), 
[________] (7) (Reference SliceType) ref <trainType []string> @ PriceService // read(price_db), 
[_________] (8) (BasicVariable BasicType) rt string // read(price_db), 
[_________] (9) (BasicVariable BasicType) ":" string // read(price_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig} // read(price_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

