[] (-1) (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (8) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} // write(price_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(price_db), 
[__] (9) (BasicVariable BasicType) ID string // write(price_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) _ price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (9) (BasicVariable BasicType) ID string // write(price_db), 

[] (-1) (BasicVariable BasicType) ok bool 

[] (-1) (InterfaceVariable UserType) err .error 

