[] (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (FieldVariable FieldType) moneyDB NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 
[__] (FieldVariable FieldType) paymentDB NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) payDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BlueprintBackendVariable BlueprintBackendType) pay_coll NoSQLCollection {database = payment, collection = payment} 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) money_coll NoSQLCollection {database = payment, collection = money} 

[] (InterfaceVariable UserType) err .error 

