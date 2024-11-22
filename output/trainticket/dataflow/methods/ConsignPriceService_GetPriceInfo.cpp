[] (PointerObject PointerType) c (*consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase})
[_] (StructObject UserType) consignprice.ConsignPriceServiceImpl struct{db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = consign, collection = consign}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "index" string,  0 int}

    --> r-tainted: read(consignprice_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = consign, collection = consign}
     --> r-tainted: read(consignprice_db.ConsignPrice, consignprice_db.BeyondPrice, consignprice_db.float64, consignprice_db.InitialPrice, consignprice_db.InitialWeight, consignprice_db.WithinPrice) {6}
[_] (StructObject UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64}
      --> r-tainted: read(consignprice_db.BeyondPrice) {1}
[__] (FieldObject FieldType) BeyondPrice float64
       --> r-tainted: read(consignprice_db.float64) {1}
[___] (BasicObject BasicType) BeyondPrice float64
      --> r-tainted: read(consignprice_db.InitialPrice) {1}
[__] (FieldObject FieldType) InitialPrice float64
       --> r-tainted: read(consignprice_db.float64) {1}
[___] (BasicObject BasicType) InitialPrice float64
      --> r-tainted: read(consignprice_db.InitialWeight) {1}
[__] (FieldObject FieldType) InitialWeight float64
       --> r-tainted: read(consignprice_db.float64) {1}
[___] (BasicObject BasicType) InitialWeight float64
      --> r-tainted: read(consignprice_db.WithinPrice) {1}
[__] (FieldObject FieldType) WithinPrice float64
       --> r-tainted: read(consignprice_db.float64) {1}
[___] (BasicObject BasicType) WithinPrice float64

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(consignprice_db.ConsignPrice, consignprice_db.BeyondPrice, consignprice_db.float64, consignprice_db.InitialPrice, consignprice_db.InitialWeight, consignprice_db.WithinPrice) {6}
[] (StructObject UserType) cp consignprice.ConsignPrice struct{ID string, Index int64, InitialWeight float64, InitialPrice float64, WithinPrice float64, BeyondPrice float64}
     --> r-tainted: read(consignprice_db.BeyondPrice) {1}
[_] (FieldObject FieldType) BeyondPrice float64
      --> r-tainted: read(consignprice_db.float64) {1}
[__] (BasicObject BasicType) BeyondPrice float64
     --> r-tainted: read(consignprice_db.InitialPrice) {1}
[_] (FieldObject FieldType) InitialPrice float64
      --> r-tainted: read(consignprice_db.float64) {1}
[__] (BasicObject BasicType) InitialPrice float64
     --> r-tainted: read(consignprice_db.InitialWeight) {1}
[_] (FieldObject FieldType) InitialWeight float64
      --> r-tainted: read(consignprice_db.float64) {1}
[__] (BasicObject BasicType) InitialWeight float64
     --> r-tainted: read(consignprice_db.WithinPrice) {1}
[_] (FieldObject FieldType) WithinPrice float64
      --> r-tainted: read(consignprice_db.float64) {1}
[__] (BasicObject BasicType) WithinPrice float64

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) info string
[_] (BasicObject BasicType) "The price of weight within %.2f is %.2f. The price of extra weight within the region is %.2f and beyond the region is %.2f" string
     --> r-tainted: read(consignprice_db.float64) {1}
[_] (BasicObject BasicType) InitialWeight float64
     --> r-tainted: read(consignprice_db.float64) {1}
[_] (BasicObject BasicType) InitialPrice float64
     --> r-tainted: read(consignprice_db.float64) {1}
[_] (BasicObject BasicType) WithinPrice float64
     --> r-tainted: read(consignprice_db.float64) {1}
[_] (BasicObject BasicType) BeyondPrice float64

