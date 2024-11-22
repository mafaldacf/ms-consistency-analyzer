[] (PointerObject PointerType) c (*shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue})
[_] (StructObject UserType) shopping_app.OrderServiceImpl struct{stock_service shopping_app.StockService, billing_service shopping_app.BillingService, product_service shopping_app.ProductService, order_db NoSQLDatabase, shipment_queue Queue, analytics_queue Queue}
[__] (FieldObject FieldType) analytics_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) analytics_queue Queue
[__] (FieldObject FieldType) billing_service shopping_app.BillingService
[___] (ServiceObject ServiceType) billing_service shopping_app.BillingService
[__] (FieldObject FieldType) order_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) order_db NoSQLDatabase
[__] (FieldObject FieldType) product_service shopping_app.ProductService
[___] (ServiceObject ServiceType) product_service shopping_app.ProductService
[__] (FieldObject FieldType) shipment_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) shipment_queue Queue
[__] (FieldObject FieldType) stock_service shopping_app.StockService
[___] (ServiceObject ServiceType) stock_service shopping_app.StockService

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ ShipmentService
[__] (Reference UserType) ref <ctx context.Context> @ ShipmentService
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[] (BasicObject BasicType) orderID string
     --> w-tainted: write(shipment_db.Shipment.OrderID) {1}         --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[_] (Reference BasicType) ref <OrderID string> @ ShipmentService
      --> w-tainted: write(shipment_db.Shipment.OrderID) {1}           --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[__] (Reference FieldType) ref <OrderID string> @ ShipmentService
       --> w-tainted: write(shipment_db.Shipment.OrderID) {1}             --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___] (BasicObject BasicType) OrderID string
        --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}               --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[____] (InterfaceObject InterfaceType) OrderID interface{}
     --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[_] (Reference BasicType) ref <orderID string> @ Frontend

    --> r-tainted: read(order_db.Order) {1}
[] (StructObject UserType) order shopping_app.Order struct{OrderID string, UserID string, ProductID string, Quantity int, Timestamp 1 int}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "orderID" string, Value string}
[__] (FieldObject FieldType) Key "orderID" string
[___] (BasicObject BasicType) "orderID" string
[__] (FieldObject FieldType) Value string
       --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[___] (BasicObject BasicType) orderID string
        --> w-tainted: write(shipment_db.Shipment.OrderID) {1}               --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[____] (Reference BasicType) ref <OrderID string> @ ShipmentService
         --> w-tainted: write(shipment_db.Shipment.OrderID) {1}                 --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[_____] (Reference FieldType) ref <OrderID string> @ ShipmentService
          --> w-tainted: write(shipment_db.Shipment.OrderID) {1}                   --> w-tainted: write(shipment_db.Shipment.OrderID) {1} --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[______] (BasicObject BasicType) OrderID string
           --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}                     --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[_______] (InterfaceObject InterfaceType) OrderID interface{}
        --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[____] (Reference BasicType) ref <orderID string> @ Frontend

    --> r-tainted: read(order_db._, order_db.Order) {2}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = order_database, collection = order_collection}
     --> r-tainted: read(order_db.Order) {1}
[_] (StructObject UserType) order shopping_app.Order struct{OrderID string, UserID string, ProductID string, Quantity int, Timestamp 1 int}

[] (InterfaceObject UserType) _ .error

