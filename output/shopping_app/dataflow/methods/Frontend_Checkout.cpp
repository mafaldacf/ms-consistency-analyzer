[] (PointerVariable PointerType) f (*shopping_app.FrontendImpl struct{order_service shopping_app.OrderService, cart_service shopping_app.CartService}) 
[_] (StructVariable UserType) shopping_app.FrontendImpl struct{order_service shopping_app.OrderService, cart_service shopping_app.CartService} 
[__] (FieldVariable FieldType) cart_service shopping_app.CartService 
[___] (ServiceVariable ServiceType) cart_service shopping_app.CartService 
[__] (FieldVariable FieldType) order_service shopping_app.OrderService 
[___] (ServiceVariable ServiceType) order_service shopping_app.OrderService 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 

[] (BasicVariable BasicType) userID string // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 

[] (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 

[] (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 

[] (BasicVariable BasicType) price int // write(billing_db), 

