[] (PointerObject PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase})
[_] (StructObject UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}
[__] (FieldObject FieldType) catalogue_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) catalogue_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService

    --> r-tainted: read(catalogue_db._.id) {1}
[] (BasicObject BasicType) id string
     --> r-tainted: read(catalogue_db._.id) {1}
[_] (Reference BasicType) ref <itemID string> @ FrontendService

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "id" string, Value string}
[__] (FieldObject FieldType) Key "id" string
[___] (BasicObject BasicType) "id" string
[__] (FieldObject FieldType) Value string
       --> r-tainted: read(catalogue_db._.id) {1}
[___] (BasicObject BasicType) id string
        --> r-tainted: read(catalogue_db._.id) {1}
[____] (Reference BasicType) ref <itemID string> @ FrontendService

    --> r-tainted: read(catalogue_db.Sock, catalogue_db.ImageURL, catalogue_db.[]string, catalogue_db.string, catalogue_db.ImageURL_1, catalogue_db.ImageURL_2, catalogue_db.TagString, catalogue_db.Tags) {8}
[] (StructObject UserType) sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}
     --> r-tainted: read(catalogue_db.ImageURL) {1}
[_] (FieldObject FieldType) ImageURL []string
      --> r-tainted: read(catalogue_db.[]string) {1}
[__] (ArrayObject SliceType) []string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) ImageURL_1 string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) ImageURL_2 string
     --> r-tainted: read(catalogue_db.ImageURL_1) {1}
[_] (FieldObject FieldType) ImageURL_1 string
      --> r-tainted: read(catalogue_db.string) {1}
[__] (BasicObject BasicType) ImageURL_1 string
     --> r-tainted: read(catalogue_db.ImageURL_2) {1}
[_] (FieldObject FieldType) ImageURL_2 string
      --> r-tainted: read(catalogue_db.string) {1}
[__] (BasicObject BasicType) ImageURL_2 string
     --> r-tainted: read(catalogue_db.TagString) {1}
[_] (FieldObject FieldType) TagString string
      --> r-tainted: read(catalogue_db.string) {1}
[__] (BasicObject BasicType) TagString string
     --> r-tainted: read(catalogue_db.Tags) {1}
[_] (FieldObject FieldType) Tags []string
      --> r-tainted: read(catalogue_db.[]string) {1}
[__] (SliceObject SliceType) []string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) TagString string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) "," string

    --> r-tainted: read(catalogue_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue}
     --> r-tainted: read(catalogue_db.Sock, catalogue_db.ImageURL, catalogue_db.[]string, catalogue_db.string, catalogue_db.ImageURL_1, catalogue_db.ImageURL_2, catalogue_db.TagString, catalogue_db.Tags) {8}
[_] (StructObject UserType) sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}
      --> r-tainted: read(catalogue_db.ImageURL) {1}
[__] (FieldObject FieldType) ImageURL []string
       --> r-tainted: read(catalogue_db.[]string) {1}
[___] (ArrayObject SliceType) []string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) ImageURL_1 string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) ImageURL_2 string
      --> r-tainted: read(catalogue_db.ImageURL_1) {1}
[__] (FieldObject FieldType) ImageURL_1 string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) ImageURL_1 string
      --> r-tainted: read(catalogue_db.ImageURL_2) {1}
[__] (FieldObject FieldType) ImageURL_2 string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) ImageURL_2 string
      --> r-tainted: read(catalogue_db.TagString) {1}
[__] (FieldObject FieldType) TagString string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) TagString string
      --> r-tainted: read(catalogue_db.Tags) {1}
[__] (FieldObject FieldType) Tags []string
       --> r-tainted: read(catalogue_db.[]string) {1}
[___] (SliceObject SliceType) []string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) TagString string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) "," string

[] (InterfaceObject UserType) _ .error

