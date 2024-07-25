[] (PointerVariable PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}) 
[_] (StructVariable UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) contactsDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ArrayVariable ArrayType) all_contacts []contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts} 

[] (InterfaceVariable UserType) err .error 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts} // read(contacts_db), 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

