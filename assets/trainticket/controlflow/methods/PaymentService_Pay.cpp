[] (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) paymentDB NoSQLDatabase 
[__] (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) payment payment.Payment struct{ID string, OrderID string, UserID string, Price string} 
[_] (FieldVariable FieldType) OrderID string 
[__] (BasicVariable BasicType) OrderID string 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment} 

[] (InterfaceVariable UserType) err .error 

[] (BasicVariable BasicType) ok bool 

[] (InterfaceVariable UserType) err .error 

