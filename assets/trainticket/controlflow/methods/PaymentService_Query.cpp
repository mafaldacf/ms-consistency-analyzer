[] (-1) (PointerVariable PointerType) p (*payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) payment.PaymentServiceImpl struct{paymentDB NoSQLDatabase, moneyDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) paymentDB NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) moneyDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ArrayVariable ArrayType) payments []payment.Payment struct{ID string, OrderID string, UserID string, Price string} 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = payment, collection = payment} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = payment, collection = payment} // read(payments_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (InterfaceVariable UserType) err .error 

