[] (PointerObject PointerType) c (*contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase})
[_] (StructObject UserType) contacts.ContactsServiceImpl struct{contactsDB NoSQLDatabase}
[__] (FieldObject FieldType) contactsDB NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(contacts_db.Contact) {1}
[] (StructObject UserType) contact contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}
     --> w-tainted: write(contacts_db.Contact.AccountID) {1}
[_] (FieldObject FieldType) AccountID string
      --> w-tainted: write(contacts_db.Contact.AccountID) {1}           --> w-tainted: write(contacts_db.Contact.AccountID) {1} --> r-tainted: read(contacts_db._.accountid) {1}
[__] (BasicObject BasicType) AccountID string
     --> w-tainted: write(contacts_db.Contact.DocumentNumber) {1}
[_] (FieldObject FieldType) DocumentNumber string
      --> w-tainted: write(contacts_db.Contact.DocumentNumber) {1}           --> w-tainted: write(contacts_db.Contact.DocumentNumber) {1} --> r-tainted: read(contacts_db._.documentnumber) {1}
[__] (BasicObject BasicType) DocumentNumber string
     --> w-tainted: write(contacts_db.Contact.DocumentType) {1}
[_] (FieldObject FieldType) DocumentType int
      --> w-tainted: write(contacts_db.Contact.DocumentType) {1}           --> w-tainted: write(contacts_db.Contact.DocumentType) {1} --> r-tainted: read(contacts_db._.documenttype) {1}
[__] (BasicObject BasicType) DocumentType int

[] (BlueprintBackendObject BlueprintBackendType) coll NoSQLCollection {database = contacts, collection = contacts}

[] (InterfaceObject UserType) err .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{ "accountid" string,  string}
[_] (StructObject StructType) struct{ "documentnumber" string,  string}
[_] (StructObject StructType) struct{ "documenttype" string,  int}

    --> r-tainted: read(contacts_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) res NoSQLCursor {database = contacts, collection = contacts}

[] (InterfaceObject UserType) err .error

    --> r-tainted: read(contacts_db.Contact) {1}
[] (StructObject UserType) existing contacts.Contact struct{ID string, AccountID string, Name string, DocumentType int, DocumentNumber string, PhoneNumber string}

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

