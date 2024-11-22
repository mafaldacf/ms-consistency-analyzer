[] (PointerObject PointerType) f (*shopping_app.FrontendImpl struct{order_service shopping_app.OrderService, cart_service shopping_app.CartService})
[_] (StructObject UserType) shopping_app.FrontendImpl struct{order_service shopping_app.OrderService, cart_service shopping_app.CartService}
[__] (FieldObject FieldType) cart_service shopping_app.CartService
[___] (ServiceObject ServiceType) cart_service shopping_app.CartService
[__] (FieldObject FieldType) order_service shopping_app.OrderService
[___] (ServiceObject ServiceType) order_service shopping_app.OrderService

[] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(order_db._.orderID, order_db.Order.OrderID) {2}
[] (BasicObject BasicType) orderID string

