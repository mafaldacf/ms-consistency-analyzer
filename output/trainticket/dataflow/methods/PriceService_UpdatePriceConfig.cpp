[] (PointerObject PointerType) p (*price.PriceServiceImpl struct{priceDB NoSQLDatabase})
[_] (StructObject UserType) price.PriceServiceImpl struct{priceDB NoSQLDatabase}
[__] (FieldObject FieldType) priceDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) pc price.PriceConfig struct{ID string, TrainType string, RouteID string, BasicPriceRate float64, FirstClassPriceRate float64}
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = priceConfig, collection = priceConfig}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

