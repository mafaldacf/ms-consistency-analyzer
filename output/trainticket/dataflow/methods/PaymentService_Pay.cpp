[] (PointerObject PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase})
[_] (StructObject UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}
[__] (FieldObject FieldType) moneyDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) moneyDB NoSQLDatabase
[__] (FieldObject FieldType) paymentDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) payDB NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string}
[_] (FieldObject FieldType) OrderID string
[__] (BasicObject BasicType) OrderID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) ok bool

[] (InterfaceObject UserType) err .error

