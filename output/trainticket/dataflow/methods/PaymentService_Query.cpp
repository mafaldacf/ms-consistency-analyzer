[] (PointerObject PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase})
[_] (StructObject UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}
[__] (FieldObject FieldType) moneyDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) moneyDB NoSQLDatabase
[__] (FieldObject FieldType) paymentDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) payDB NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(payments_db.[]payment.Payment struct{ID string, OrderID string, UserID string, Price string}) {1}
[] (ArrayObject ArrayType) payments []payment.Payment struct{ID string, OrderID string, UserID string, Price string}

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(payments_db.Payment) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = payment, collection = payment}
     --> r-tainted: read(payments_db.[]payment.Payment struct{ID string, OrderID string, UserID string, Price string}) {1}
[_] (ArrayObject ArrayType) payments []payment.Payment struct{ID string, OrderID string, UserID string, Price string}

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

