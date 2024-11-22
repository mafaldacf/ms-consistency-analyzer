[] (PointerObject PointerType) s (*shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers 4 int})
[_] (StructObject UserType) shopping_app.ShipmentServiceImpl struct{order_service shopping_app.OrderService, shipment_db NoSQLDatabase, shipment_queue Queue, num_workers 4 int}
[__] (FieldObject FieldType) num_workers 4 int
[___] (BasicObject BasicType) 4 int
[__] (FieldObject FieldType) order_service shopping_app.OrderService
[___] (ServiceObject ServiceType) order_service shopping_app.OrderService
[__] (FieldObject FieldType) shipment_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) shipment_db NoSQLDatabase
[__] (FieldObject FieldType) shipment_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) shipment_queue Queue

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ ShipmentService

[] (StructObject UserType) message shopping_app.ShipmentMessage struct{OrderID string, UserID string}
[_] (Reference UserType) ref <workerMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}> @ ShipmentService
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__] (FieldObject FieldType) OrderID string
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___] (BasicObject BasicType) OrderID string
        --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}               --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[____] (InterfaceObject InterfaceType) OrderID interface{}
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__] (FieldObject FieldType) UserID string
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[____] (InterfaceObject InterfaceType) UserID interface{}
[_] (FieldObject FieldType) OrderID string
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__] (Reference FieldType) ref <OrderID string> @ ShipmentService
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___] (BasicObject BasicType) OrderID string
        --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}               --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[____] (InterfaceObject InterfaceType) OrderID interface{}
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__] (BasicObject BasicType) OrderID string
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___] (Reference FieldType) ref <OrderID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.OrderID) {1}               --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[____] (BasicObject BasicType) OrderID string
         --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}                 --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[_____] (InterfaceObject InterfaceType) OrderID interface{}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__] (Reference FieldType) ref <UserID string> @ ShipmentService
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___] (BasicObject BasicType) UserID string
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[____] (InterfaceObject InterfaceType) UserID interface{}
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__] (BasicObject BasicType) UserID string
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___] (Reference FieldType) ref <UserID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[____] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[_____] (InterfaceObject InterfaceType) UserID interface{}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = shipment_database, collection = shipment_collection}

[] (InterfaceObject UserType) _ .error

    --> w-tainted: write(shipment_db.Shipment) {1}
[] (StructObject UserType) shipment shopping_app.Shipment struct{OrderID string, UserID string, Status "pending" string}
     --> w-tainted: write(shipment_db.Shipment.OrderID) {1}
[_] (FieldObject FieldType) OrderID string
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__] (BasicObject BasicType) OrderID string
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___] (Reference FieldType) ref <OrderID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.OrderID) {1}               --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[____] (BasicObject BasicType) OrderID string
         --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}                 --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[_____] (InterfaceObject InterfaceType) OrderID interface{}
     --> w-tainted: write(shipment_db.Shipment.Status) {1}
[_] (FieldObject FieldType) Status "pending" string
      --> w-tainted: write(shipment_db.Shipment.Status) {1}
[__] (BasicObject BasicType) "pending" string
     --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[__] (BasicObject BasicType) UserID string
       --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[___] (Reference FieldType) ref <UserID string> @ ShipmentService
        --> w-tainted: write(shipment_db.Shipment.UserID) {1}
[____] (BasicObject BasicType) UserID string
         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}                 --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[_____] (InterfaceObject InterfaceType) UserID interface{}

