[] (PointerObject PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase})
[_] (StructObject UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase}
[__] (FieldObject FieldType) priceDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ PriceService

    --> r-tainted: read(price_db._.id) {1}
[] (BasicObject BasicType) id string
     --> w-tainted: write(price_db.PriceConfig.ID) {1}         --> w-tainted: write(price_db.PriceConfig.ID) {1} --> r-tainted: read(price_db._.id) {1}
[_] (Reference BasicType) ref <ID string> @ PriceService

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

    --> r-tainted: read(price_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig}
     --> r-tainted: read(price_db.PriceConfig) {1}
[_] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(price_db.PriceConfig) {1}
[] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

