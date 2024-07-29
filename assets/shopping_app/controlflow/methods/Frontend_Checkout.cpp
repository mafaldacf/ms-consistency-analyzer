[] (-1) (PointerVariable PointerType) f (*shopping_app.FrontendImpl struct{cart_service shopping_app.CartService, order_service shopping_app.OrderService}) 
[_] (0) (StructVariable UserType) shopping_app.FrontendImpl struct{cart_service shopping_app.CartService, order_service shopping_app.OrderService} 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 
[__] (-1) (ServiceVariable ServiceType) cart_service shopping_app.CartService 

[] (6) (InterfaceVariable UserType) ctx context.Context 

[] (7) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), read(shipment_queue), 

[] (8) (BasicVariable BasicType) userID string // write(order_db), write(billing_db), write(analytics_queue), read(analytics_queue), write(shipment_queue), read(shipment_queue), 

[] (9) (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 

[] (10) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 

[] (11) (BasicVariable BasicType) price int // write(billing_db), 

