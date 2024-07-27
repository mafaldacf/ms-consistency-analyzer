[] (-1) (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) paymentDB NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string} 
[_] (-1) (FieldVariable FieldType) UserID string 
[__] (-1) (BasicVariable BasicType) UserID string // write(money_db), 
[_] (-1) (FieldVariable FieldType) Price string 
[__] (-1) (BasicVariable BasicType) Price string // write(money_db), 

[] (-1) (StructVariable UserType) m payment.Money struct{ID string, UserID string, Price string} // write(money_db), 
[_] (-1) (FieldVariable FieldType) UserID string // write(money_db), 
[__] (-1) (BasicVariable BasicType) UserID string // write(money_db), 
[_] (-1) (FieldVariable FieldType) Price string // write(money_db), 
[__] (-1) (BasicVariable BasicType) Price string // write(money_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(money_db), 
[__] (0) (BasicVariable BasicType) string // write(money_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = money} 

[] (-1) (InterfaceVariable UserType) err .error 

