[] (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) paymentDB NoSQLDatabase 
[__] (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string} 
[_] (FieldVariable FieldType) UserID string 
[__] (BasicVariable BasicType) UserID string // write(money_db), 
[_] (FieldVariable FieldType) Price string 
[__] (BasicVariable BasicType) Price string // write(money_db), 

[] (StructVariable UserType) m payment.Money struct{ID string, UserID string, Price string} // write(money_db), 
[_] (FieldVariable FieldType) ID string // write(money_db), 
[__] (BasicVariable BasicType) string // write(money_db), 
[_] (FieldVariable FieldType) UserID string // write(money_db), 
[__] (BasicVariable BasicType) UserID string // write(money_db), 
[_] (FieldVariable FieldType) Price string // write(money_db), 
[__] (BasicVariable BasicType) Price string // write(money_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = money} 

[] (InterfaceVariable UserType) err .error 

