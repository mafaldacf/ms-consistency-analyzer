[] (-1) (PointerVariable PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}) 
[_] (0) (StructVariable UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) contactsDB NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (StructVariable UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} // write(contacts_db), 
[_] (-1) (FieldVariable FieldType) DocumentType int // write(contacts_db), 
[__] (-1) (BasicVariable BasicType) DocumentType int // write(contacts_db), 
[_] (-1) (FieldVariable FieldType) AccountID string // write(contacts_db), 
[__] (-1) (BasicVariable BasicType) AccountID string // write(contacts_db), 
[_] (-1) (FieldVariable FieldType) DocumentNumber string // write(contacts_db), 
[__] (-1) (BasicVariable BasicType) DocumentNumber string // write(contacts_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{ "accountid" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) AccountID string // write(contacts_db), 
[_] (0) (StructVariable StructType) struct{ "documentnumber" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) DocumentNumber string // write(contacts_db), 
[_] (0) (StructVariable StructType) struct{ "documenttype" string,  int} 
[__] (0) (FieldVariable FieldType) int 
[___] (-1) (BasicVariable BasicType) DocumentType int // write(contacts_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) existing contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string} 

[] (-1) (BasicVariable BasicType) exists bool 

[] (-1) (InterfaceVariable UserType) err .error 

