[] (PointerObject PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase})
[_] (StructObject UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}
[__] (FieldObject FieldType) catalogue_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) catalogue_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue}

[] (InterfaceObject UserType) _ .error

[] (ArrayObject ArrayType) socks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}

[] (SliceObject UserType) projection primitive.D
[_] (StructObject StructType) struct{Key "tags" string, Value true bool}
[__] (FieldObject FieldType) Key "tags" string
[___] (BasicObject BasicType) "tags" string
[__] (FieldObject FieldType) Value true bool
[___] (BasicObject BasicType) true bool

[] (SliceObject UserType) filter primitive.D

[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue}
[_] (ArrayObject ArrayType) socks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}

[] (InterfaceObject UserType) _ .error

[] (ArrayObject ArrayType) tags []string

