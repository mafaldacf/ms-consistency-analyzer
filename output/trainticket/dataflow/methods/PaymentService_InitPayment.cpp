[] (-1) (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) paymentDB NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string} // write(payments_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(payments_db), 
[__] (-1) (BasicVariable BasicType) ID string // write(payments_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = payment, collection = payment} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) stored payment.Payment struct{ID string, OrderID string, UserID string, Price string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

