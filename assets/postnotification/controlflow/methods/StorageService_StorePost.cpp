[] (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase}) 
[_] (StructVariable UserType) postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) cache Cache 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) reqID int64 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 
[_] (FieldVariable FieldType) PostID int64 
[__] (BasicVariable BasicType) PostID int64 

[] (BasicVariable BasicType) postIDStr string 
[_] (BasicVariable BasicType) PostID int64 
[_] (BasicVariable BasicType) 10 int 

