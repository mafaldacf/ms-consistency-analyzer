[] (PointerObject PointerType) f (*shopping_app.FrontendImpl struct{cart_service shopping_app.CartService, order_service shopping_app.OrderService})
[_] (StructObject UserType) shopping_app.FrontendImpl struct{order_service shopping_app.OrderService, cart_service shopping_app.CartService}
[__] (FieldObject FieldType) cart_service shopping_app.CartService
[___] (ServiceObject ServiceType) cart_service shopping_app.CartService
[__] (FieldObject FieldType) order_service shopping_app.OrderService
[___] (ServiceObject ServiceType) order_service shopping_app.OrderService

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2}       --> w-tainted: write(order_db.Order.OrderID, shipment_queue.ShipmentMessage.OrderID) {2} --> r-tainted: read(shipment_queue.ShipmentMessage.OrderID) {1}
[] (BasicObject BasicType) cartID string

    --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4}       --> w-tainted: write(order_db.Order.UserID, billing_db.Bill.UserID, analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {4} --> r-tainted: read(analytics_queue.AnalyticsMessage.UserID, shipment_queue.ShipmentMessage.UserID) {2}
[] (BasicObject BasicType) userID string

    --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}       --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[] (BasicObject BasicType) productID string

    --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[] (BasicObject BasicType) quantity int

    --> w-tainted: write(billing_db.Bill.PricePerUnit) {1}
[] (BasicObject BasicType) price int

