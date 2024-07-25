[] (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ArrayVariable ArrayType) rtsAndTypes []string 

[] (MapVariable MapType) res map[string]price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 
[_] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (BasicVariable BasicType) rt string 

[] (SliceVariable SliceType) pieces []string 
[_] (BasicVariable BasicType) rt string 
[_] (BasicVariable BasicType) ":" string 

[] (SliceVariable SliceType) routeid []string // read(price_db), 
[_] (BasicVariable BasicType) rt string // read(price_db), 
[_] (BasicVariable BasicType) ":" string // read(price_db), 

[] (SliceVariable SliceType) trainType []string // read(price_db), 
[_] (BasicVariable BasicType) rt string // read(price_db), 
[_] (BasicVariable BasicType) ":" string // read(price_db), 

[] (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (InterfaceVariable UserType) _ .error 

