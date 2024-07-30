[] (-1) (PointerVariable PointerType) s (*shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers int}) 
[_] (0) (StructVariable UserType) shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers int} 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_queue Queue 
[__] (-1) (BasicVariable BasicType) num_workers 4 int 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) analytics_db NoSQLDatabase 

[] (23) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ChanVariable ChanType) forever chan struct{} 

[] (19) (MapVariable MapType) event map[string]interface{} 
[_] (19) (Reference UserType) ref <analyticsMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}> @ AnalyticsService // write(analytics_queue), 
[__] (-1) (FieldVariable FieldType) UserID string // write(analytics_queue), 
[___] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[___] (-1) (BasicVariable BasicType) userID string // write(order_db), write(analytics_queue), write(shipment_queue), write(billing_db), 
[____] (10) (Reference BasicType) ref <userID string> @ Frontend // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 
[____] (30) (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[____] (45) (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), write(shipment_db), 
[__] (-1) (FieldVariable FieldType) ProductCategory string // write(analytics_queue), 
[___] (27) (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[___] (-1) (BasicVariable BasicType) Category string // write(analytics_queue), 
[____] (27) (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService // write(analytics_queue), write(analytics_db), 
[_] (30) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[_] (27) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 

[] (29) (BasicVariable BasicType) UserID string // write(analytics_db), 
[_] (30) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 

[] (26) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[_] (27) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 

[] (24) (StructVariable UserType) workerMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string} 
[_] (28) (FieldVariable FieldType) UserID string // write(analytics_db), 
[__] (29) (BasicVariable BasicType) UserID string // write(analytics_db), 
[___] (30) (InterfaceVariable InterfaceType) UserID interface{} // write(order_db), write(billing_db), write(analytics_queue), write(analytics_db), write(shipment_queue), 
[_] (25) (FieldVariable FieldType) ProductCategory string // write(analytics_db), 
[__] (26) (BasicVariable BasicType) ProductCategory string // write(analytics_db), 
[___] (27) (InterfaceVariable InterfaceType) ProductCategory interface{} // write(analytics_queue), write(analytics_db), 

