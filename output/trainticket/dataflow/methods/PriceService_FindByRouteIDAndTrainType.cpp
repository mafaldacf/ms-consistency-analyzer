[] (PointerObject PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase})
[_] (StructObject UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase}
[__] (FieldObject FieldType) priceDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ PriceService

    --> r-tainted: read(price_db.PriceConfig.RouteID) {1}
[] (BasicObject BasicType) routeID string
     --> r-tainted: read(price_db.PriceConfig.RouteID) {1}
[_] (Reference SliceType) ref <routeid []string> @ PriceService
      --> r-tainted: read(price_db.PriceConfig.RouteID) {1}
[__] (BasicObject BasicType) rt string
      --> r-tainted: read(price_db.PriceConfig.RouteID) {1}
[__] (BasicObject BasicType) ":" string

    --> r-tainted: read(price_db.PriceConfig.TrainType) {1}
[] (BasicObject BasicType) trainType string
     --> r-tainted: read(price_db.PriceConfig.TrainType) {1}
[_] (Reference SliceType) ref <trainType []string> @ PriceService
      --> r-tainted: read(price_db.PriceConfig.TrainType) {1}
[__] (BasicObject BasicType) rt string
      --> r-tainted: read(price_db.PriceConfig.TrainType) {1}
[__] (BasicObject BasicType) ":" string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "$and" string,  primitive.A}

    --> r-tainted: read(price_db.PriceConfig) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig}
     --> r-tainted: read(price_db.PriceConfig) {1}
[_] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(price_db.PriceConfig) {1}
[] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

