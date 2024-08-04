[] (PointerVariable PointerType) s (*shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers 4 int}) 
[_] (StructVariable UserType) shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers 4 int} 
[__] (FieldVariable FieldType) analytics_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (FieldVariable FieldType) analytics_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (FieldVariable FieldType) num_workers 4 int 
[___] (BasicVariable BasicType) 4 int 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (StructVariable UserType) message shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string} 
[_] (Reference UserType) ref <workerMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}> @ AnalyticsService 
[__] (FieldVariable FieldType) ProductCategory string // write(analytics_db), 
[___] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 
[__] (FieldVariable FieldType) UserID string // write(analytics_db), 
[___] (BasicVariable BasicType) UserID string // write(analytics_db), 
[____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[_] (FieldVariable FieldType) ProductCategory string 
[__] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[___] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 
[__] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[___] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[____] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[_____] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 
[_] (FieldVariable FieldType) UserID string 
[__] (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[___] (BasicVariable BasicType) UserID string // write(analytics_db), 
[____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[__] (BasicVariable BasicType) UserID string // write(analytics_db), 
[___] (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[____] (BasicVariable BasicType) UserID string // write(analytics_db), 
[_____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_database, collection = analytics_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) analytics shopping_app.Analytics struct{UserID string, Categories []string} 
[_] (FieldVariable FieldType) Categories []string 
[__] (SliceVariable SliceType) Categories []string // write(analytics_db), 
[___] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[_____] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[______] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 

[] (SliceVariable UserType) query primitive.D 
[_] (StructVariable StructType) struct{Key "userID" string, Value string} 
[__] (FieldVariable FieldType) Key "userID" string 
[___] (BasicVariable BasicType) "userID" string 
[__] (FieldVariable FieldType) Value string 
[___] (BasicVariable BasicType) UserID string // write(analytics_db), 
[____] (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[_____] (BasicVariable BasicType) UserID string // write(analytics_db), 
[______] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 

[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = analytics_database, collection = analytics_collection} 

[] (InterfaceVariable UserType) _ .error 

[] (StructVariable UserType) updatedAnalytics shopping_app.Analytics struct{UserID string, Categories []string} // write(analytics_db), 
[_] (FieldVariable FieldType) Categories []string // write(analytics_db), 
[__] (SliceVariable SliceType) Categories []string // write(analytics_db), 
[___] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[_____] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[______] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 
[_] (FieldVariable FieldType) UserID string // write(analytics_db), 
[__] (BasicVariable BasicType) UserID string // write(analytics_db), 
[___] (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[____] (BasicVariable BasicType) UserID string // write(analytics_db), 
[_____] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 

