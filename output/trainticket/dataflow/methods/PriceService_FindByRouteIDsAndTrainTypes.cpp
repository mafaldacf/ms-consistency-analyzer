[] (PointerObject PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase})
[_] (StructObject UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase}
[__] (FieldObject FieldType) priceDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (ArrayObject ArrayType) rtsAndTypes []string

[] (MapObject MapType) res map[string]price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}
[_] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}
      --> r-tainted: read(price_db.PriceConfig) {1}
[__] (Reference UserType) ref <pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}> @ FindByRouteIDAndTrainType

[] (BasicObject BasicType) rt string

[] (SliceObject SliceType) pieces []string
[_] (BasicObject BasicType) rt string
[_] (BasicObject BasicType) ":" string

    --> r-tainted: read(price_db.PriceConfig.RouteID) {1}
[] (SliceObject SliceType) routeid []string
     --> r-tainted: read(price_db.PriceConfig.RouteID) {1}
[_] (BasicObject BasicType) rt string
     --> r-tainted: read(price_db.PriceConfig.RouteID) {1}
[_] (BasicObject BasicType) ":" string

    --> r-tainted: read(price_db.PriceConfig.TrainType) {1}
[] (SliceObject SliceType) trainType []string
     --> r-tainted: read(price_db.PriceConfig.TrainType) {1}
[_] (BasicObject BasicType) rt string
     --> r-tainted: read(price_db.PriceConfig.TrainType) {1}
[_] (BasicObject BasicType) ":" string

[] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}
     --> r-tainted: read(price_db.PriceConfig) {1}
[_] (Reference UserType) ref <pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}> @ FindByRouteIDAndTrainType

[] (InterfaceObject UserType) _ .error
[_] (Reference BasicType) ref <nil> @ FindByRouteIDAndTrainType

