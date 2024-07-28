[] (-1) (PointerVariable PointerType) s (*postnotification.TimelineServiceImpl struct{storage_service postnotification.StorageService, timeline_cache Cache}) 
[_] (0) (StructVariable UserType) postnotification.TimelineServiceImpl struct{storage_service postnotification.StorageService, timeline_cache Cache} 
[__] (-1) (ServiceVariable ServiceType) storage_service postnotification.StorageService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) timeline_cache Cache 

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (2) (BasicVariable BasicType) reqID int64 

[] (-1) (StructVariable UserType) timeline postnotification.Timeline struct{ReqID int64, PostID int64} 
[_] (-1) (FieldVariable FieldType) PostID int64 
[__] (3) (BasicVariable BasicType) PostID int64 // read(posts_db), read(analytics_db), 

[] (-1) (BasicVariable BasicType) reqIDStr string 
[_] (2) (BasicVariable BasicType) reqID int64 
[_] (0) (BasicVariable BasicType) 10 int 

[] (-1) (StructVariable UserType) post postnotification.Post struct{ReqID int64, PostID int64, Text string, Mentions []string, Timestamp int64, Creator postnotification.Creator struct{Username string}} 

[] (-1) (StructVariable UserType) analytics postnotification.Analytics struct{PostID int64} 

[] (-1) (InterfaceVariable UserType) err .error 

