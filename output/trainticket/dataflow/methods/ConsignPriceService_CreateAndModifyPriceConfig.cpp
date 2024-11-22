[] (PointerObject PointerType) c (*consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(consignprice_db.ConsignPrice) {1}
[] (StructObject UserType) priceConfig consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64}
     --> w-tainted: write(consignprice_db.ConsignPrice.Index) {1}
[_] (FieldObject FieldType) Index int64
      --> w-tainted: write(consignprice_db.ConsignPrice.Index) {1}
[__] (BasicObject BasicType) 0 int

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = consign, collection = consign}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "index" string,  0 int}

    --> r-tainted: read(consignprice_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = consign, collection = consign}
     --> r-tainted: read(consignprice_db.ConsignPrice) {1}
[_] (StructObject UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(consignprice_db.ConsignPrice) {1}
[] (StructObject UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) ok bool

[] (InterfaceObject UserType) err .error

