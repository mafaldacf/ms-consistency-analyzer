[] (-1) (PointerVariable PointerType) s (*catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) catalogue.catalogueImpl struct{catalogue_db NoSQLDatabase} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) catalogue_db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (53) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (63) (Reference UserType) ref <ctx context.Context> @ FrontendService 
[_] (73) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) id string // read(catalogue_db), 
[_] (54) (Reference BasicType) ref <itemID string> @ FrontendService // read(catalogue_db), 
[_] (64) (Reference BasicType) ref <itemID string> @ FrontendService // read(catalogue_db), 
[_] (74) (Reference BasicType) ref <itemID string> @ FrontendService // read(catalogue_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = catalogue, collection = catalogue} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable UserType) query primitive.D // read(catalogue_db), 
[_] (0) (StructVariable StructType) struct{Key "id" string, Value string} // read(catalogue_db), 
[__] (0) (FieldVariable FieldType) Key "id" string // read(catalogue_db), 
[___] (0) (BasicVariable BasicType) "id" string // read(catalogue_db), 
[__] (0) (FieldVariable FieldType) Value string // read(catalogue_db), 
[___] (-1) (BasicVariable BasicType) id string // read(catalogue_db), 
[____] (54) (Reference BasicType) ref <itemID string> @ FrontendService // read(catalogue_db), 
[____] (64) (Reference BasicType) ref <itemID string> @ FrontendService // read(catalogue_db), 
[____] (74) (Reference BasicType) ref <itemID string> @ FrontendService // read(catalogue_db), 

[] (-1) (StructVariable UserType) sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 
[_] (-1) (FieldVariable FieldType) ImageURL_1 string 
[__] (-1) (BasicVariable BasicType) ImageURL_1 string 
[_] (-1) (FieldVariable FieldType) ImageURL_2 string 
[__] (-1) (BasicVariable BasicType) ImageURL_2 string 
[_] (-1) (FieldVariable FieldType) ImageURL []string 
[__] (0) (ArrayVariable SliceType) []string 
[___] (-1) (BasicVariable BasicType) ImageURL_1 string 
[___] (-1) (BasicVariable BasicType) ImageURL_2 string 
[_] (-1) (FieldVariable FieldType) TagString string 
[__] (-1) (BasicVariable BasicType) TagString string 
[_] (-1) (FieldVariable FieldType) Tags []string 
[__] (0) (SliceVariable SliceType) []string 
[___] (-1) (BasicVariable BasicType) TagString string 
[___] (0) (BasicVariable BasicType) "," string 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = catalogue, collection = catalogue} // read(catalogue_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

