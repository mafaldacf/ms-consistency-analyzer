[] (PointerObject PointerType) s (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase})
[_] (StructObject UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase
[__] (FieldObject FieldType) q Queue
[___] (BlueprintBackendObject BlueprintBackendType) queue Queue

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) id string

[] (BasicObject BasicType) status string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments}

[] (InterfaceObject UserType) _ .error

