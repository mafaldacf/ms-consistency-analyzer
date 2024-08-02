[] (-1) (PointerVariable PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) catalogue_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (11) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (ArrayVariable ArrayType) tags []string 
[_] (12) (Reference ArrayType) ref <tags []string> @ FrontendService 

[] (-1) (BasicVariable BasicType) order string 
[_] (13) (Reference BasicType) ref <order string> @ FrontendService 

[] (-1) (BasicVariable BasicType) pageNum int 
[_] (14) (Reference BasicType) ref <pageNum int> @ FrontendService 

[] (-1) (BasicVariable BasicType) pageSize int 
[_] (15) (Reference BasicType) ref <pageSize int> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (ArrayVariable ArrayType) allSocks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 

[] (-1) (ArrayVariable ArrayType) socks []catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 

[] (-1) (SliceVariable UserType) filter primitive.D 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue} 

[] (-1) (InterfaceVariable UserType) _ .error 

