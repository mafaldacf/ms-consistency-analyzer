[] (PointerObject PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase})
[_] (StructObject UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}
[__] (FieldObject FieldType) moneyDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) moneyDB NoSQLDatabase
[__] (FieldObject FieldType) paymentDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) payDB NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(payments_db.Payment) {1}
[] (StructObject UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string}
     --> w-tainted: write(payments_db.Payment.ID) {1}
[_] (FieldObject FieldType) ID string
      --> w-tainted: write(payments_db.Payment.ID) {1}           --> w-tainted: write(payments_db.Payment.ID) {1} --> r-tainted: read(payments_db._.id) {1}
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(payments_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = payment, collection = payment}
     --> r-tainted: read(payments_db.Payment) {1}
[_] (StructObject UserType) stored payment.Payment struct{ID string, OrderID string, UserID string, Price string}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(payments_db.Payment) {1}
[] (StructObject UserType) stored payment.Payment struct{ID string, OrderID string, UserID string, Price string}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

