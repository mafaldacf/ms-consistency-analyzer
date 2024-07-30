[] (-1) (PointerVariable PointerType) f (*shopping_app.FrontendImpl struct{cart_service shopping_app.CartService, order_service shopping_app.OrderService}) 
[_] (0) (StructVariable UserType) shopping_app.FrontendImpl struct{cart_service shopping_app.CartService, order_service shopping_app.OrderService} 
[__] (-1) (ServiceVariable ServiceType) cart_service shopping_app.CartService 
[__] (-1) (ServiceVariable ServiceType) order_service shopping_app.OrderService 

[] (8) (InterfaceVariable UserType) ctx context.Context 

[] (9) (BasicVariable BasicType) cartID string // write(order_db), write(shipment_queue), 

[] (10) (BasicVariable BasicType) userID string // write(order_db), write(billing_db), write(analytics_queue), write(shipment_queue), 

[] (11) (BasicVariable BasicType) productID string // write(order_db), write(stock_db), write(billing_db), 

[] (12) (BasicVariable BasicType) quantity int // write(order_db), write(stock_db), write(billing_db), 

[] (13) (BasicVariable BasicType) price int // write(billing_db), 

