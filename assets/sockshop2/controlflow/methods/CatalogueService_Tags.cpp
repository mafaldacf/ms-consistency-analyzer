[] (-1) (PointerVariable PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) catalogue_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (10) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) socks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 

[] (-1) (SliceVariable UserType) projection primitive.D 
[_] (0) (StructVariable StructType) struct{Key "tags" string, Value true bool} 
[__] (0) (FieldVariable FieldType) Key "tags" string 
[___] (0) (BasicVariable BasicType) "tags" string 
[__] (0) (FieldVariable FieldType) Value true bool 
[___] (0) (BasicVariable BasicType) true bool 

[] (-1) (SliceVariable UserType) filter primitive.D // read(catalogue_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue} // read(catalogue_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) tags []string 

