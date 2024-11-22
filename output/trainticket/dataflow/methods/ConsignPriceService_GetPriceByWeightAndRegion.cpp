[] (PointerObject PointerType) c (*consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) weight float64

[] (BasicObject BasicType) isWithinRegion bool

[] (StructObject UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64}
     --> r-tainted: read(consignprice_db.ConsignPrice) {1}
[_] (Reference UserType) ref <cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64}> @ GetPriceConfig
[_] (FieldObject FieldType) InitialPrice float64
[__] (BasicObject BasicType) InitialPrice float64

[] (InterfaceObject UserType) err .error
[_] (Reference BasicType) ref <nil> @ GetPriceConfig

[] (FieldObject FieldType) price float64
[_] (BasicObject BasicType) InitialPrice float64

