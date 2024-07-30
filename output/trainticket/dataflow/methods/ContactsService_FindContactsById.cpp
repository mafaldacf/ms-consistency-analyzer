[] (-1) (PointerVariable PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) contactsDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) id string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) id string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

