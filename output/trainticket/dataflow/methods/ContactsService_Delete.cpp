[] (PointerObject PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase})
[_] (StructObject UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}
[__] (FieldObject FieldType) contactsDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (StructObject UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

