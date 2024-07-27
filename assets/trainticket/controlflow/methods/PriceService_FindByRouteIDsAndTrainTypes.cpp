[] (-1) (PointerVariable PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) priceDB NoSQLDatabase 

[] (3) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ArrayVariable ArrayType) rtsAndTypes []string 

[] (-1) (MapVariable MapType) res map[string]price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 
[_] (-1) (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (-1) (BasicVariable BasicType) rt string 

[] (-1) (SliceVariable SliceType) pieces []string 
[_] (-1) (BasicVariable BasicType) rt string 
[_] (0) (BasicVariable BasicType) ":" string 

[] (4) (SliceVariable SliceType) routeid []string // read(price_db), 
[_] (5) (BasicVariable BasicType) rt string // read(price_db), 
[_] (6) (BasicVariable BasicType) ":" string // read(price_db), 

[] (7) (SliceVariable SliceType) trainType []string // read(price_db), 
[_] (8) (BasicVariable BasicType) rt string // read(price_db), 
[_] (9) (BasicVariable BasicType) ":" string // read(price_db), 

[] (-1) (StructVariable UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64} 

[] (-1) (InterfaceVariable UserType) _ .error 

