[] (PointerObject PointerType) service (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase})
[_] (StructObject UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase
[__] (FieldObject FieldType) q Queue
[___] (BlueprintBackendObject BlueprintBackendType) queue Queue

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments}

[] (InterfaceObject UserType) _ .error

