[] (PointerObject PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase})
[_] (StructObject UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase}
[__] (FieldObject FieldType) priceDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(price_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = priceConfig, collection = priceConfig}
     --> r-tainted: read(price_db.[]price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}) {1}
[_] (ArrayObject ArrayType) pcs []price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(price_db.[]price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}) {1}
[] (ArrayObject ArrayType) pcs []price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}

[] (InterfaceObject UserType) err .error

