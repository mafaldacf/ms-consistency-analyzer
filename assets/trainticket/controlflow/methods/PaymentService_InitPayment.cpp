[] (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) paymentDB NoSQLDatabase 
[__] (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string} // write(payments_db), 
[_] (FieldVariable FieldType) ID string // write(payments_db), 
[__] (BasicVariable BasicType) ID string // write(payments_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = payment, collection = payment} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) stored payment.Payment struct{ID string, OrderID string, UserID string, Price string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

