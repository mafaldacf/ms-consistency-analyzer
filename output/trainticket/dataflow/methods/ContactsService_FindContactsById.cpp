[] (PointerObject PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase})
[_] (StructObject UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}
[__] (FieldObject FieldType) contactsDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(contacts_db._.id) {1}
[] (BasicObject BasicType) id string

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "id" string,  string}

    --> r-tainted: read(contacts_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts}
     --> r-tainted: read(contacts_db.Contact) {1}
[_] (StructObject UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(contacts_db.Contact) {1}
[] (StructObject UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

