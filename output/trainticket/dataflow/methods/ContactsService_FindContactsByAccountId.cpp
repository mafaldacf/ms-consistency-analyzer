[] (PointerObject PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase})
[_] (StructObject UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}
[__] (FieldObject FieldType) contactsDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(contacts_db._.accountid) {1}
[] (BasicObject BasicType) id string

    --> r-tainted: read(contacts_db.[]contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}) {1}
[] (ArrayObject ArrayType) account_contacts []contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "accountid" string,  string}

    --> r-tainted: read(contacts_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts}
     --> r-tainted: read(contacts_db.[]contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}) {1}
[_] (ArrayObject ArrayType) account_contacts []contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

