[] (PointerObject PointerType) s (*shipping.shippingImpl struct{q Queue, db NoSQLDatabase})
[_] (StructObject UserType) shipping.shippingImpl struct{q Queue, db NoSQLDatabase}
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase
[__] (FieldObject FieldType) q Queue
[___] (BlueprintBackendObject BlueprintBackendType) queue Queue

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) id string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = shipping_service, collection = shipments}

[] (InterfaceObject UserType) _ .error

[] (BlueprintBackendObject BlueprintBackendType) cursor NoSQLCursor {database = shipping_service, collection = shipments}
[_] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status string}

[] (InterfaceObject UserType) err .error

[] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status string}

