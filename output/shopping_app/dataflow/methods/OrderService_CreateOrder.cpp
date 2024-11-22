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
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2}       --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[] (BasicObject BasicType) cartID string
     --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2}         --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[_] (Reference BasicType) ref <cartID string> @ Frontend
     --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}         --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[_] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService

    --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4}       --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[] (BasicObject BasicType) userID string
     --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4}         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[_] (Reference BasicType) ref <userID string> @ Frontend
     --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[_] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService
     --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}         --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[_] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService

    --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}       --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[] (BasicObject BasicType) productID string
     --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}         --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend

    --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[] (BasicObject BasicType) quantity int
     --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[_] (Reference BasicType) ref <quantity int> @ Frontend

    --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[] (BasicObject BasicType) price int
     --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[_] (Reference BasicType) ref <price int> @ Frontend

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = order_database, collection = order_collection}

[] (InterfaceObject UserType) _ .error

    --> w-tainted: write(order_db.Order) {1}
[] (StructObject UserType) order shopping_app.Order struct{OrderID string, UserID string, ProductID string, Quantity int, Timestamp 1 int}
     --> w-tainted: write(order_db.Order.OrderID) {1}
[_] (FieldObject FieldType) OrderID string
      --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2}           --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[__] (BasicObject BasicType) cartID string
       --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2}             --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[___] (Reference BasicType) ref <cartID string> @ Frontend
       --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}             --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService
     --> w-tainted: write(order_db.Order.ProductID) {1}
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}           --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[__] (BasicObject BasicType) productID string
       --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}             --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[___] (Reference BasicType) ref <productID string> @ Frontend
     --> w-tainted: write(order_db.Order.Quantity) {1}
[_] (FieldObject FieldType) Quantity int
      --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[__] (BasicObject BasicType) quantity int
       --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[___] (Reference BasicType) ref <quantity int> @ Frontend
     --> w-tainted: write(order_db.Order.Timestamp) {1}
[_] (FieldObject FieldType) Timestamp 1 int
      --> w-tainted: write(order_db.Order.Timestamp) {1}
[__] (BasicObject BasicType) 1 int
     --> w-tainted: write(order_db.Order.UserID) {1}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4}           --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[__] (BasicObject BasicType) userID string
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[___] (Reference BasicType) ref <userID string> @ Frontend
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[___] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[___] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService

[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}
     --> r-tainted: read(product_db.Product) {1}
[_] (Reference UserType) ref <product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}> @ ProductService
[_] (FieldObject FieldType) Category string
      --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory) {1}           --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory) {1} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory) {1}
[__] (BasicObject BasicType) Category string
       --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}             --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[___] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService

[] (InterfaceObject UserType) _ .error
[_] (Reference UserType) ref <err .error> @ ProductService

    --> w-tainted: write(analytics_queue.AnalyticsMessage) {1}       --> w-tainted: write(analytics_queue.AnalyticsMessage) {1} --> r-tainted: read(analytics_queue.AnalyticsMessage) {1}
[] (StructObject UserType) analyticsMessage shopping_app.AnalyticsMessage struct{UserID string, ProductCategory string}
     --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory) {1}         --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory) {1} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory) {1}
[_] (FieldObject FieldType) ProductCategory string
      --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}           --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[__] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService
      --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory) {1}           --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory) {1} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory) {1}
[__] (BasicObject BasicType) Category string
       --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2}             --> w-tainted: write(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.Analytics.Categories) {2} --> r-tainted: read(analytics_queue.AnalyticsMessage.ProductCategory, analytics_db.interface{}) {2}
[___] (Reference InterfaceType) ref <ProductCategory interface{}> @ AnalyticsService
     --> w-tainted: write(analytics_queue.AnalyticsMessage.UserID) {1}         --> w-tainted: write(analytics_queue.AnalyticsMessage.UserID) {1} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID) {1}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}           --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[__] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService
      --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4}           --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[__] (BasicObject BasicType) userID string
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[___] (Reference BasicType) ref <userID string> @ Frontend
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[___] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[___] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService

    --> w-tainted: write(shipment_queue.ShipmentMessage) {1}       --> w-tainted: write(shipment_queue.ShipmentMessage) {1} --> r-tainted: read(shipment_queue.ShipmentMessage) {1}
[] (StructObject UserType) shipmentMessage shopping_app.ShipmentMessage struct{OrderID string, UserID string}
     --> w-tainted: write(shipment_queue.ShipmentMessage.OrderID) {1}         --> w-tainted: write(shipment_queue.ShipmentMessage.OrderID) {1} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[_] (FieldObject FieldType) OrderID string
      --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}           --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[__] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService
      --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2}           --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[__] (BasicObject BasicType) cartID string
       --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2}             --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[___] (Reference BasicType) ref <cartID string> @ Frontend
       --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3}             --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID, shipment_db.Shipment.OrderID) {3} --> r-tainted: read(order_db._.orderID, shipment_queue.ShipmentMessage.OrderID, order_db.Order.OrderID) {3}
[___] (Reference InterfaceType) ref <OrderID interface{}> @ ShipmentService
     --> w-tainted: write(shipment_queue.ShipmentMessage.UserID) {1}         --> w-tainted: write(shipment_queue.ShipmentMessage.UserID) {1} --> r-tainted: read(shipment_queue.ShipmentMessage.UserID) {1}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}           --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[__] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService
      --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4}           --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[__] (BasicObject BasicType) userID string
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[___] (Reference BasicType) ref <userID string> @ Frontend
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[___] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService
       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}             --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[___] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService

