[] (PointerVariable PointerType) s (*shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers 4 int}) 
[_] (StructVariable UserType) shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers 4 int} 
[__] (FieldVariable FieldType) analytics_db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 
[__] (FieldVariable FieldType) analytics_queue Queue 
[___] (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (FieldVariable FieldType) num_workers 4 int 
[___] (BasicVariable BasicType) 4 int 

[] (InterfaceVariable UserType) ctx context.Context 

[] (ChanVariable ChanType) forever chan struct{} 

[] (MapVariable MapType) event map[string]interface{} 
[_] (Reference UserType) ref <analyticsMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}> @ AnalyticsService // write(analytics_queue), 
[__] (FieldVariable FieldType) ProductCategory string // write(analytics_queue), 
[___] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (BasicVariable BasicType) Category string // write(analytics_queue), 
[____] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[__] (FieldVariable FieldType) UserID string // write(analytics_queue), 
[___] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[____] (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[____] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[____] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[_] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[_] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 

[] (BasicVariable BasicType) UserID string // write(analytics_db), 
[_] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 

[] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[_] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 

[] (StructVariable UserType) workerMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string} 
[_] (FieldVariable FieldType) ProductCategory string // write(analytics_db), 
[__] (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[___] (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 
[_] (FieldVariable FieldType) UserID string // write(analytics_db), 
[__] (BasicVariable BasicType) UserID string // write(analytics_db), 
[___] (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 

