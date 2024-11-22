[] (PointerObject PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase})
[_] (StructObject UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}
[__] (FieldObject FieldType) moneyDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) moneyDB NoSQLDatabase
[__] (FieldObject FieldType) paymentDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) payDB NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) pay_coll NoSQLCollection {database = payment, collection = payment}

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

[] (BlueprintBackendObject BlueprintBackendType) money_coll NoSQLCollection {database = payment, collection = money}

[] (InterfaceObject UserType) err .error

