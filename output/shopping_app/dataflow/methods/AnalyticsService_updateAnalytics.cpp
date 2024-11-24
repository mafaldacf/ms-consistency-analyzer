[] (PointerObject PointerType) s (*shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers int})
[_] (StructObject UserType) shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers 4 int}
[__] (FieldObject FieldType) analytics_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) analytics_db NoSQLDatabase
[__] (FieldObject FieldType) analytics_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) analytics_queue Queue
[__] (FieldObject FieldType) num_workers 4 int
[___] (BasicObject BasicType) 4 int

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ AnalyticsService

[] (StructObject UserType) message shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}
[_] (Reference UserType) ref <workerMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}> @ AnalyticsService
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[__] (FieldObject FieldType) ProductCategory string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}               --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[____] (InterfaceObject InterfaceType) ProductCategory interface{}
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__] (FieldObject FieldType) UserID string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[____] (InterfaceObject InterfaceType) UserID interface{}
[_] (FieldObject FieldType) ProductCategory string
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[__] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}               --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[____] (InterfaceObject InterfaceType) ProductCategory interface{}
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[__] (BasicObject BasicType) ProductCategory string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[___] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[____] (BasicObject BasicType) ProductCategory string
         --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                 --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[_____] (InterfaceObject InterfaceType) ProductCategory interface{}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__] (Reference FieldType) ref <UserID string> @ AnalyticsService
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[____] (InterfaceObject InterfaceType) UserID interface{}
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__] (BasicObject BasicType) UserID string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___] (Reference FieldType) ref <UserID string> @ AnalyticsService
        --> w-tainted: write(analytics_db.Analytics.UserID) {1}               --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[____] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[_____] (InterfaceObject InterfaceType) UserID interface{}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = analytics_database, collection = analytics_collection}

[] (InterfaceObject UserType) _ .error

    --> r-tainted: read(analytics_db.Analytics, analytics_db.Categories, analytics_db.[]string, analytics_db.string, analytics_db.ProductCategory, analytics_db.interface{}) {6}
[] (StructObject UserType) analytics shopping_app.Analytics struct{UserID string, Categories []string}
     --> r-tainted: read(analytics_db.Categories) {1}
[_] (FieldObject FieldType) Categories []string
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.[]string) {1}
[__] (SliceObject SliceType) Categories []string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[____] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
         --> w-tainted: write(analytics_db.Analytics.Categories) {1}                 --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[_____] (BasicObject BasicType) ProductCategory string
          --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                   --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[______] (InterfaceObject InterfaceType) ProductCategory interface{}

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "userID" string, Value string}
[__] (FieldObject FieldType) Key "userID" string
[___] (BasicObject BasicType) "userID" string
[__] (FieldObject FieldType) Value string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___] (BasicObject BasicType) UserID string
        --> w-tainted: write(analytics_db.Analytics.UserID) {1}               --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[____] (Reference FieldType) ref <UserID string> @ AnalyticsService
         --> w-tainted: write(analytics_db.Analytics.UserID) {1}                 --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[_____] (BasicObject BasicType) UserID string
          --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}                   --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[______] (InterfaceObject InterfaceType) UserID interface{}

    --> r-tainted: read(analytics_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = analytics_database, collection = analytics_collection}
     --> r-tainted: read(analytics_db.Analytics, analytics_db.Categories, analytics_db.[]string, analytics_db.string, analytics_db.ProductCategory, analytics_db.interface{}) {6}
[_] (StructObject UserType) analytics shopping_app.Analytics struct{UserID string, Categories []string}
      --> r-tainted: read(analytics_db.Categories) {1}
[__] (FieldObject FieldType) Categories []string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.[]string) {1}
[___] (SliceObject SliceType) Categories []string
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[____] (BasicObject BasicType) ProductCategory string
         --> w-tainted: write(analytics_db.Analytics.Categories) {1}                 --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[_____] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
          --> w-tainted: write(analytics_db.Analytics.Categories) {1}                   --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[______] (BasicObject BasicType) ProductCategory string
           --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                     --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[_______] (InterfaceObject InterfaceType) ProductCategory interface{}

[] (InterfaceObject UserType) _ .error

    --> w-tainted: write(analytics_db.Analytics) {1}
[] (StructObject UserType) updatedAnalytics shopping_app.Analytics struct{UserID string, Categories []string}
     --> w-tainted: write(analytics_db.Analytics.Categories) {1}
[_] (FieldObject FieldType) Categories []string
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.[]string) {1}
[__] (SliceObject SliceType) Categories []string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[____] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
         --> w-tainted: write(analytics_db.Analytics.Categories) {1}                 --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[_____] (BasicObject BasicType) ProductCategory string
          --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                   --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[______] (InterfaceObject InterfaceType) ProductCategory interface{}
     --> w-tainted: write(analytics_db.Analytics.UserID) {1}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__] (BasicObject BasicType) UserID string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___] (Reference FieldType) ref <UserID string> @ AnalyticsService
        --> w-tainted: write(analytics_db.Analytics.UserID) {1}               --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[____] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[_____] (InterfaceObject InterfaceType) UserID interface{}

