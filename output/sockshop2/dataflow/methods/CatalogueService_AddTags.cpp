[] (PointerObject PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase})
[_] (StructObject UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}
[__] (FieldObject FieldType) catalogue_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) catalogue_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (ArrayObject ArrayType) tags []string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) update primitive.D
[_] (StructObject StructType) struct{Key "tags" string, Value []string}
[__] (FieldObject FieldType) Key "tags" string
[___] (BasicObject BasicType) "tags" string
[__] (FieldObject FieldType) Value []string
[___] (ArrayObject ArrayType) tags []string

[] (SliceObject UserType) filter primitive.D

