[] (PointerVariable PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}) 
[_] (StructVariable UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) contactsDB NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (StructVariable UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} // write(contacts_db), 
[_] (FieldVariable FieldType) AccountID string // write(contacts_db), 
[__] (BasicVariable BasicType) AccountID string // write(contacts_db), 
[_] (FieldVariable FieldType) DocumentNumber string // write(contacts_db), 
[__] (BasicVariable BasicType) DocumentNumber string // write(contacts_db), 
[_] (FieldVariable FieldType) DocumentType int // write(contacts_db), 
[__] (BasicVariable BasicType) DocumentType int // write(contacts_db), 

[] (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts} 

[] (InterfaceVariable UserType) err .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{ "accountid" string, AccountID string} 
[__] (FieldVariable FieldType) "accountid" string 
[___] (BasicVariable BasicType) "accountid" string 
[__] (FieldVariable FieldType) AccountID string // write(contacts_db), 
[___] (BasicVariable BasicType) AccountID string // write(contacts_db), 
[_] (StructVariable StructType) struct{ "documentnumber" string, DocumentNumber string} 
[__] (FieldVariable FieldType) "documentnumber" string 
[___] (BasicVariable BasicType) "documentnumber" string 
[__] (FieldVariable FieldType) DocumentNumber string // write(contacts_db), 
[___] (BasicVariable BasicType) DocumentNumber string // write(contacts_db), 
[_] (StructVariable StructType) struct{ "documenttype" string, DocumentType int} 
[__] (FieldVariable FieldType) "documenttype" string 
[___] (BasicVariable BasicType) "documenttype" string 
[__] (FieldVariable FieldType) DocumentType int // write(contacts_db), 
[___] (BasicVariable BasicType) DocumentType int // write(contacts_db), 

[] (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) existing contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} 

[] (BasicVariable BasicType) exists bool 

[] (InterfaceVariable UserType) err .error 

