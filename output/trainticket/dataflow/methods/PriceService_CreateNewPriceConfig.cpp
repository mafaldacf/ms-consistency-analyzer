[] (PointerObject PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase})
[_] (StructObject UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase}
[__] (FieldObject FieldType) priceDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(price_db.PriceConfig) {1}
[] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}
     --> w-tainted: write(price_db.PriceConfig.ID) {1}
[_] (FieldObject FieldType) ID string
      --> w-tainted: write(price_db.PriceConfig.ID) {1}           --> w-tainted: write(price_db.PriceConfig.ID) {1} --> r-tainted: read(price_db._.id) {1}
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig}

[] (InterfaceObject UserType) err .error

[] (StructObject UserType) _ price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}
     --> r-tainted: read(price_db.PriceConfig) {1}
[_] (Reference UserType) ref <pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}> @ FindByID

[] (InterfaceObject UserType) err .error
[_] (Reference BasicType) ref <nil> @ FindByID

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

[] (BasicObject BasicType) ok bool

[] (InterfaceObject UserType) err .error

