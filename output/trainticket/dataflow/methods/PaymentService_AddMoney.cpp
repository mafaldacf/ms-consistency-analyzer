[] (PointerObject PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase})
[_] (StructObject UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}
[__] (FieldObject FieldType) moneyDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) moneyDB NoSQLDatabase
[__] (FieldObject FieldType) paymentDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) payDB NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string}
[_] (FieldObject FieldType) Price string
      --> w-tainted: write(money_db.Money.Price) {1}
[__] (BasicObject BasicType) Price string
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(money_db.Money.UserID) {1}
[__] (BasicObject BasicType) UserID string

    --> w-tainted: write(money_db.Money) {1}
[] (StructObject UserType) m payment.Money struct{ID string, UserID string, Price string}
     --> w-tainted: write(money_db.Money.ID) {1}
[_] (FieldObject FieldType) ID string
      --> w-tainted: write(money_db.Money.ID) {1}
[__] (BasicObject BasicType) string
     --> w-tainted: write(money_db.Money.Price) {1}
[_] (FieldObject FieldType) Price string
      --> w-tainted: write(money_db.Money.Price) {1}
[__] (BasicObject BasicType) Price string
     --> w-tainted: write(money_db.Money.UserID) {1}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(money_db.Money.UserID) {1}
[__] (BasicObject BasicType) UserID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = payment, collection = money}

[] (InterfaceObject UserType) err .error

