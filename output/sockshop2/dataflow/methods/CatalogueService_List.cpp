[] (PointerVariable PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}) 
[_] (StructVariable UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase} 
[__] (FieldVariable FieldType) catalogue_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) catalogue_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (ArrayVariable ArrayType) tags []string 
[_] (Reference ArrayType) ref <tags []string> @ FrontendService 

[] (BasicVariable BasicType) order string 
[_] (Reference BasicType) ref <order string> @ FrontendService 

[] (BasicVariable BasicType) pageNum int 
[_] (Reference BasicType) ref <pageNum int> @ FrontendService 

[] (BasicVariable BasicType) pageSize int 
[_] (Reference BasicType) ref <pageSize int> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue} 

[] (InterfaceVariable UserType) _ .error 

[] (ArrayVariable ArrayType) allSocks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 

[] (ArrayVariable ArrayType) socks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 

[] (SliceVariable UserType) filter primitive.D 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue} 

[] (InterfaceVariable UserType) _ .error 

