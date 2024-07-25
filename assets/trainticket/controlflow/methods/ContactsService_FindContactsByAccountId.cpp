[] (PointerVariable PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}) 
[_] (StructVariable UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) contactsDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) id string 

[] (ArrayVariable ArrayType) account_contacts []contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "accountid" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) id string 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts} 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

