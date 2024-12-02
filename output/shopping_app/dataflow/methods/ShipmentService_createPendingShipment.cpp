[0] (PointerObject PointerType) s (*shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers int})
[_1] (StructObject UserType) shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers 4 int}
[__2] (FieldObject FieldType) num_workers 4 int
[___3] (BasicObject BasicType) 4 int
[__2] (FieldObject FieldType) order_service shopping_app.OrderService
[___3] (ServiceObject ServiceType) order_service shopping_app.OrderService
[__2] (FieldObject FieldType) shipment_db NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) shipment_db NoSQLDatabase
[__2] (FieldObject FieldType) shipment_queue Queue
[___3] (BlueprintBackendObject BlueprintBackendType) shipment_queue Queue

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ ShipmentService

[0] (StructObject UserType) message shopping_app.ShipmentMessage struct{OrderID string, UserID string}
[_1] (Reference UserType) ref <workerMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}> @ ShipmentService
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__2] (FieldObject FieldType) OrderID string
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___3] (BasicObject BasicType) OrderID string
        --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}               --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[____4] (InterfaceObject InterfaceType) OrderID interface{}
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__2] (FieldObject FieldType) UserID string
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___3] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[____4] (InterfaceObject InterfaceType) UserID interface{}
[_1] (FieldObject FieldType) OrderID string
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__2] (Reference FieldType) ref <OrderID string> @ ShipmentService
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___3] (BasicObject BasicType) OrderID string
        --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}               --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[____4] (InterfaceObject InterfaceType) OrderID interface{}
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__2] (BasicObject BasicType) OrderID string
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___3] (Reference FieldType) ref <OrderID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.OrderID) {1}               --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[____4] (BasicObject BasicType) OrderID string
         --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}                 --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[_____5] (InterfaceObject InterfaceType) OrderID interface{}
[_1] (FieldObject FieldType) UserID string
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__2] (Reference FieldType) ref <UserID string> @ ShipmentService
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___3] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[____4] (InterfaceObject InterfaceType) UserID interface{}
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__2] (BasicObject BasicType) UserID string
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___3] (Reference FieldType) ref <UserID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[____4] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[_____5] (InterfaceObject InterfaceType) UserID interface{}

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = shipment_database, collection = shipment_collection}

[0] (InterfaceObject UserType) _ .error

    --> w-tainted: write(shipment_db.Shipment) {1}
[0] (StructObject UserType) shipment shopping_app.Shipment struct{OrderID string, UserID string, Status "pending" string}
     --> w-tainted: write(shipment_db.Shipment.OrderID) {1}
[_1] (FieldObject FieldType) OrderID string
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__2] (BasicObject BasicType) OrderID string
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___3] (Reference FieldType) ref <OrderID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.OrderID) {1}               --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[____4] (BasicObject BasicType) OrderID string
         --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}                 --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[_____5] (InterfaceObject InterfaceType) OrderID interface{}
     --> w-tainted: write(shipment_db.Shipment.Status) {1}
[_1] (FieldObject FieldType) Status "pending" string
      --> w-tainted: write(shipment_db.Shipment.Status) {1}
[__2] (BasicObject BasicType) "pending" string
     --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[_1] (FieldObject FieldType) UserID string
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__2] (BasicObject BasicType) UserID string
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___3] (Reference FieldType) ref <UserID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[____4] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[_____5] (InterfaceObject InterfaceType) UserID interface{}

