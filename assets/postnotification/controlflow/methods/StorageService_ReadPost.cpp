[] (PointerVariable PointerType) s (*postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase}) 
[_] (StructVariable UserType) postnotification.StorageServiceImpl struct{cache Cache, db NoSQLDatabase} 
[__] (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (BlueprintBackendVariable BlueprintBackendType) cache Cache 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) reqID int64 

[] (BasicVariable BasicType) postID int64 

[] (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (BasicVariable BasicType) postIDStr string 
[_] (BasicVariable BasicType) postID int64 
[_] (BasicVariable BasicType) 10 int 

[] (BasicVariable BasicType) _ bool 

[] (InterfaceVariable UserType) err .error 

