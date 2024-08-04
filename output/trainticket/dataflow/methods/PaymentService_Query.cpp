[] (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (FieldVariable FieldType) moneyDB NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 
[__] (FieldVariable FieldType) paymentDB NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) payDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ArrayVariable ArrayType) payments []payment.Payment struct{ID string, OrderID string, UserID string, Price string} 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = payment, collection = payment} 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

