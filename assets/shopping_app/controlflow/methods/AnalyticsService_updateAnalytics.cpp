[] (-1) (PointerVariable PointerType) s (*shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers int} 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (21) (Reference UserType) ref <ctx context.Context> @ AnalyticsService 

[] (-1) (StructVariable UserType) message shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string} 
[_] (22) (Reference UserType) ref <workerMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}> @ AnalyticsService 
[__] (26) (FieldVariable FieldType) UserID string // write(analytics_db), 
[___] (27) (BasicVariable BasicType) UserID string // write(analytics_db), 
[____] (28) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 
[__] (23) (FieldVariable FieldType) ProductCategory string // write(analytics_db), 
[___] (24) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (25) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[_] (0) (FieldVariable FieldType) UserID string 
[__] (26) (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[___] (27) (BasicVariable BasicType) UserID string // write(analytics_db), 
[____] (28) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 
[__] (0) (BasicVariable BasicType) UserID string // write(analytics_db), 
[___] (26) (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[____] (27) (BasicVariable BasicType) UserID string // write(analytics_db), 
[_____] (28) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 
[_] (0) (FieldVariable FieldType) ProductCategory string 
[__] (23) (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[___] (24) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (25) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), read(analytics_queue), write(analytics_db), 
[__] (0) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[___] (23) (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[____] (24) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[_____] (25) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), read(analytics_queue), write(analytics_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = analytics_database, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) analytics shopping_app.Analytics struct{UserID string, Categories []string} 
[_] (-1) (FieldVariable FieldType) Categories []string 
[__] (-1) (SliceVariable SliceType) Categories []string // write(analytics_db), 
[___] (0) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (23) (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[_____] (24) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[______] (25) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), read(analytics_queue), write(analytics_db), 

[] (-1) (SliceVariable UserType) query primitive.D 
[_] (0) (StructVariable StructType) struct{Key "userID" string, Value string} 
[__] (0) (FieldVariable FieldType) Key "userID" string 
[___] (0) (BasicVariable BasicType) "userID" string 
[__] (0) (FieldVariable FieldType) Value string 
[___] (0) (BasicVariable BasicType) UserID string // write(analytics_db), 
[____] (26) (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[_____] (27) (BasicVariable BasicType) UserID string // write(analytics_db), 
[______] (28) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = analytics_database, collection = analytics_collection} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (StructVariable UserType) updatedAnalytics shopping_app.Analytics struct{UserID string, Categories []string} // write(analytics_db), 
[_] (0) (FieldVariable FieldType) UserID string // write(analytics_db), 
[__] (0) (BasicVariable BasicType) UserID string // write(analytics_db), 
[___] (26) (Reference FieldType) ref <UserID string> @ AnalyticsService // write(analytics_db), 
[____] (27) (BasicVariable BasicType) UserID string // write(analytics_db), 
[_____] (28) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(analytics_db), write(shipment_queue), read(shipment_queue), 
[_] (0) (FieldVariable FieldType) Categories []string // write(analytics_db), 
[__] (-1) (SliceVariable SliceType) Categories []string // write(analytics_db), 
[___] (0) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[____] (23) (Reference FieldType) ref <ProductCategory string> @ AnalyticsService // write(analytics_db), 
[_____] (24) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[______] (25) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), read(analytics_queue), write(analytics_db), 

