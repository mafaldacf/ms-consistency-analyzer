[] (PointerObject PointerType) s (*shopping_app.BillingServiceImpl struct{bill_db NoSQLDatabase})
[_] (StructObject UserType) shopping_app.BillingServiceImpl struct{bill_db NoSQLDatabase}
[__] (FieldObject FieldType) bill_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) bill_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ OrderService
[__] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> w-tainted: write(billing_db.Bill.UserID) {1}
[] (BasicObject BasicType) userID string
     --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4}         --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[_] (Reference BasicType) ref <userID string> @ OrderService
      --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4}           --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[__] (Reference BasicType) ref <userID string> @ Frontend
      --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}           --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[__] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService
      --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}           --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[__] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService

    --> w-tainted: write(billing_db.Bill.ProductID) {1}
[] (BasicObject BasicType) productID string
     --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}         --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[_] (Reference BasicType) ref <productID string> @ OrderService
      --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}           --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[__] (Reference BasicType) ref <productID string> @ Frontend

    --> w-tainted: write(billing_db.Bill.Quantity, billing_db.Bill.TotalCost) {2}
[] (BasicObject BasicType) quantity int
     --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[_] (Reference BasicType) ref <quantity int> @ OrderService
      --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[__] (Reference BasicType) ref <quantity int> @ Frontend

    --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[] (BasicObject BasicType) pricePerUnit int
     --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[_] (Reference BasicType) ref <price int> @ OrderService
      --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[__] (Reference BasicType) ref <price int> @ Frontend

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = bill_database, collection = bill_collection}

[] (InterfaceObject UserType) _ .error

    --> w-tainted: write(billing_db.Bill) {1}
[] (StructObject UserType) bill shopping_app.Bill struct{UserID string, ProductID string, Quantity int, PricePerUnit int, TotalCost (&int)}
     --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[_] (FieldObject FieldType) PricePerUnit int
      --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[__] (BasicObject BasicType) pricePerUnit int
       --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[___] (Reference BasicType) ref <price int> @ OrderService
        --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[____] (Reference BasicType) ref <price int> @ Frontend
     --> w-tainted: write(billing_db.Bill.ProductID) {1}
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(billing_db.Bill.ProductID) {1}
[__] (BasicObject BasicType) productID string
       --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}             --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[___] (Reference BasicType) ref <productID string> @ OrderService
        --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}               --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[____] (Reference BasicType) ref <productID string> @ Frontend
     --> w-tainted: write(billing_db.Bill.Quantity) {1}
[_] (FieldObject FieldType) Quantity int
      --> w-tainted: write(billing_db.Bill.Quantity, billing_db.Bill.TotalCost) {2}
[__] (BasicObject BasicType) quantity int
       --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[___] (Reference BasicType) ref <quantity int> @ OrderService
        --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[____] (Reference BasicType) ref <quantity int> @ Frontend
     --> w-tainted: write(billing_db.Bill.TotalCost) {1}
[_] (FieldObject FieldType) TotalCost (&int)
      --> w-tainted: write(billing_db.Bill.TotalCost) {1}
[__] (AddressObject AddressType) quantity (&int)
       --> w-tainted: write(billing_db.Bill.Quantity, billing_db.Bill.TotalCost) {2}
[___] (BasicObject BasicType) quantity int
        --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[____] (Reference BasicType) ref <quantity int> @ OrderService
         --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[_____] (Reference BasicType) ref <quantity int> @ Frontend
     --> w-tainted: write(billing_db.Bill.UserID) {1}
[_] (FieldObject FieldType) UserID string
      --> w-tainted: write(billing_db.Bill.UserID) {1}
[__] (BasicObject BasicType) userID string
       --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4}             --> w-tainted: write(order_db.Order.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, billing_db.Bill.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[___] (Reference BasicType) ref <userID string> @ OrderService
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[____] (Reference BasicType) ref <userID string> @ Frontend
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, analytics_db.Analytics.UserID, shipment_queue.ShipmentMessage.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, analytics_db._.userID, shipment_queue.ShipmentMessage.UserID) {3}
[____] (Reference InterfaceType) ref <UserID interface{}> @ AnalyticsService
        --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5}               --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID, shipment_db.Shipment.UserID) {5} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[____] (Reference InterfaceType) ref <UserID interface{}> @ ShipmentService

