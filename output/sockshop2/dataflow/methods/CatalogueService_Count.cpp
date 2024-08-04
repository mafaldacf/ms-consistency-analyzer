[] (PointerVariable PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}) 
[_] (StructVariable UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase} 
[__] (FieldVariable FieldType) catalogue_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) catalogue_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ArrayVariable ArrayType) tags []string 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue} 

[] (InterfaceVariable UserType) _ .error 

[] (ArrayVariable ArrayType) socks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 

[] (SliceVariable UserType) filter primitive.D 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue} 

[] (InterfaceVariable UserType) _ .error 

