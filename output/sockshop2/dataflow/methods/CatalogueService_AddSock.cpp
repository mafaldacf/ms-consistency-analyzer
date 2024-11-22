[] (PointerObject PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase})
[_] (StructObject UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}
[__] (FieldObject FieldType) catalogue_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) catalogue_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService

    --> w-tainted: write(catalogue_db.Sock) {1}
[] (StructObject UserType) sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}
     --> w-tainted: write(catalogue_db.Sock) {1}
[_] (Reference UserType) ref <sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}> @ FrontendService
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue}

[] (InterfaceObject UserType) _ .error

