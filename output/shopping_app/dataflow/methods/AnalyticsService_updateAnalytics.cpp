[0] (PointerObject PointerType) s (*shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers int})
[_1] (StructObject UserType) shopping_app.AnalyticsServiceImpl struct{analytics_db NoSQLDatabase, analytics_queue Queue, num_workers 4 int}
[__2] (FieldObject FieldType) analytics_db NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) analytics_db NoSQLDatabase
[__2] (FieldObject FieldType) analytics_queue Queue
[___3] (BlueprintBackendObject BlueprintBackendType) analytics_queue Queue
[__2] (FieldObject FieldType) num_workers 4 int
[___3] (BasicObject BasicType) 4 int

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ AnalyticsService

[0] (StructObject UserType) message shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}
[_1] (Reference UserType) ref <workerMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}> @ AnalyticsService
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[__2] (FieldObject FieldType) ProductCategory string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___3] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}               --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[____4] (InterfaceObject InterfaceType) ProductCategory interface{}
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__2] (FieldObject FieldType) UserID string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___3] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[____4] (InterfaceObject InterfaceType) UserID interface{}
[_1] (FieldObject FieldType) ProductCategory string
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[__2] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___3] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}               --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[____4] (InterfaceObject InterfaceType) ProductCategory interface{}
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[__2] (BasicObject BasicType) ProductCategory string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[___3] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[____4] (BasicObject BasicType) ProductCategory string
         --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                 --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[_____5] (InterfaceObject InterfaceType) ProductCategory interface{}
[_1] (FieldObject FieldType) UserID string
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__2] (Reference FieldType) ref <UserID string> @ AnalyticsService
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___3] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[____4] (InterfaceObject InterfaceType) UserID interface{}
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__2] (BasicObject BasicType) UserID string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___3] (Reference FieldType) ref <UserID string> @ AnalyticsService
        --> w-tainted: write(analytics_db.Analytics.UserID) {1}               --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[____4] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[_____5] (InterfaceObject InterfaceType) UserID interface{}

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = analytics_database, collection = analytics_collection}

[0] (InterfaceObject UserType) _ .error

    --> r-tainted: read(analytics_db.Analytics, analytics_db.Categories, analytics_db.[]string, analytics_db.string, analytics_db.ProductCategory, analytics_db.interface{}) {6}
[0] (StructObject UserType) analytics shopping_app.Analytics struct{UserID string, Categories []string}
     --> r-tainted: read(analytics_db.Categories) {1}
[_1] (FieldObject FieldType) Categories []string
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.[]string) {1}
[__2] (SliceObject SliceType) Categories []string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___3] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[____4] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
         --> w-tainted: write(analytics_db.Analytics.Categories) {1}                 --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[_____5] (BasicObject BasicType) ProductCategory string
          --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                   --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[______6] (InterfaceObject InterfaceType) ProductCategory interface{}

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{Key "userID" string, Key "userID" string, Value string, Value string}
[__2] (FieldObject FieldType) Key "userID" string
[___3] (BasicObject BasicType) "userID" string
[__2] (FieldObject FieldType) Value string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___3] (BasicObject BasicType) UserID string
        --> w-tainted: write(analytics_db.Analytics.UserID) {1}               --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[____4] (Reference FieldType) ref <UserID string> @ AnalyticsService
         --> w-tainted: write(analytics_db.Analytics.UserID) {1}                 --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[_____5] (BasicObject BasicType) UserID string
          --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}                   --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[______6] (InterfaceObject InterfaceType) UserID interface{}

    --> r-tainted: read(analytics_db._) {1}
[0] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = analytics_database, collection = analytics_collection}
     --> r-tainted: read(analytics_db.Analytics, analytics_db.Categories, analytics_db.[]string, analytics_db.string, analytics_db.ProductCategory, analytics_db.interface{}) {6}
[_1] (StructObject UserType) analytics shopping_app.Analytics struct{UserID string, Categories []string}
      --> r-tainted: read(analytics_db.Categories) {1}
[__2] (FieldObject FieldType) Categories []string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.[]string) {1}
[___3] (SliceObject SliceType) Categories []string
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[____4] (BasicObject BasicType) ProductCategory string
         --> w-tainted: write(analytics_db.Analytics.Categories) {1}                 --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[_____5] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
          --> w-tainted: write(analytics_db.Analytics.Categories) {1}                   --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[______6] (BasicObject BasicType) ProductCategory string
           --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                     --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[_______7] (InterfaceObject InterfaceType) ProductCategory interface{}

[0] (InterfaceObject UserType) _ .error

    --> w-tainted: write(analytics_db.Analytics) {1}
[0] (StructObject UserType) updatedAnalytics shopping_app.Analytics struct{UserID string, Categories []string}
     --> w-tainted: write(analytics_db.Analytics.Categories) {1}
[_1] (FieldObject FieldType) Categories []string
      --> w-tainted: write(analytics_db.Analytics.Categories) {1}           --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.[]string) {1}
[__2] (SliceObject SliceType) Categories []string
       --> w-tainted: write(analytics_db.Analytics.Categories) {1}             --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[___3] (BasicObject BasicType) ProductCategory string
        --> w-tainted: write(analytics_db.Analytics.Categories) {1}               --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.ProductCategory) {1}
[____4] (Reference FieldType) ref <ProductCategory string> @ AnalyticsService
         --> w-tainted: write(analytics_db.Analytics.Categories) {1}                 --> w-tainted: write(analytics_db.Analytics.Categories) {1} --> r-tainted: read(analytics_db.string) {1}
[_____5] (BasicObject BasicType) ProductCategory string
          --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}                   --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[______6] (InterfaceObject InterfaceType) ProductCategory interface{}
     --> w-tainted: write(analytics_db.Analytics.UserID) {1}
[_1] (FieldObject FieldType) UserID string
      --> w-tainted: write(analytics_db.Analytics.UserID) {1}           --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[__2] (BasicObject BasicType) UserID string
       --> w-tainted: write(analytics_db.Analytics.UserID) {1}             --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[___3] (Reference FieldType) ref <UserID string> @ AnalyticsService
        --> w-tainted: write(analytics_db.Analytics.UserID) {1}               --> w-tainted: write(analytics_db.Analytics.UserID) {1} --> r-tainted: read(analytics_db._.userID) {1}
[____4] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[_____5] (InterfaceObject InterfaceType) UserID interface{}

