[] (PointerVariable PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}) 
[_] (StructVariable UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase} 
[__] (FieldVariable FieldType) catalogue_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) catalogue_db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) id string 
[_] (Reference BasicType) ref <itemID string> @ FrontendService 
[_] (Reference BasicType) ref <itemID string> @ FrontendService 
[_] (Reference BasicType) ref <itemID string> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue} 

[] (InterfaceVariable UserType) _ .error 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "id" string, Value string} 
[__] (FieldVariable FieldType) Key "id" string 
[___] (BasicVariable BasicType) "id" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) id string 
[____] (Reference BasicType) ref <itemID string> @ FrontendService 
[____] (Reference BasicType) ref <itemID string> @ FrontendService 
[____] (Reference BasicType) ref <itemID string> @ FrontendService 

[] (StructVariable UserType) sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 
[_] (FieldVariable FieldType) ImageURL []string 
[__] (ArrayVariable SliceType) []string 
[___] (BasicVariable BasicType) ImageURL_1 string 
[___] (BasicVariable BasicType) ImageURL_2 string 
[_] (FieldVariable FieldType) ImageURL_1 string 
[__] (BasicVariable BasicType) ImageURL_1 string 
[_] (FieldVariable FieldType) ImageURL_2 string 
[__] (BasicVariable BasicType) ImageURL_2 string 
[_] (FieldVariable FieldType) TagString string 
[__] (BasicVariable BasicType) TagString string 
[_] (FieldVariable FieldType) Tags []string 
[__] (SliceVariable SliceType) []string 
[___] (BasicVariable BasicType) TagString string 
[___] (BasicVariable BasicType) "," string 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue} 

[] (InterfaceVariable UserType) _ .error 

