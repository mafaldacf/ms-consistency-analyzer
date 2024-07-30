[] (-1) (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) paymentDB NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string} 
[_] (-1) (FieldVariable FieldType) OrderID string 
[__] (-1) (BasicVariable BasicType) OrderID string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BasicVariable BasicType) ok bool 

[] (-1) (InterfaceVariable UserType) err .error 

