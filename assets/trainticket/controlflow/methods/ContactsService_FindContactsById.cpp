[] (PointerVariable PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}) 
[_] (StructVariable UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) contactsDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) id string // read(contacts_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D // read(contacts_db), 
[_] (StructVariable StructType) struct{ "id" string,  string} // read(contacts_db), 
[__] (FieldVariable FieldType) string // read(contacts_db), 
[___] (BasicVariable BasicType) id string // read(contacts_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts} // read(contacts_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

