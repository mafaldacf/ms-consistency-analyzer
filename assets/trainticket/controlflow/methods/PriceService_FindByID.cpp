[] (-1) (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (8) (Reference UserType) ref <ctx context.Context> @ PriceService 

[] (-1) (BasicVariable BasicType) id string 
[_] (9) (Reference BasicType) ref <ID string> @ PriceService // write(price_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) id string 
[____] (9) (Reference BasicType) ref <ID string> @ PriceService // write(price_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

