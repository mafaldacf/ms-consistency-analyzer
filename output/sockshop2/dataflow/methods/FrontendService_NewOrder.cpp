[] (-1) (PointerVariable PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}) 
[_] (0) (StructVariable UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService} 
[__] (-1) (ServiceVariable ServiceType) cart cart.CartService 
[__] (-1) (ServiceVariable ServiceType) order order.OrderService 
[__] (-1) (ServiceVariable ServiceType) user user.UserService 
[__] (-1) (ServiceVariable ServiceType) catalogue catalogue.CatalogueService 

[] (25) (InterfaceVariable UserType) ctx context.Context 

[] (26) (BasicVariable BasicType) userID string // write(shipqueue), write(shipdb), write(order_db), 

[] (27) (BasicVariable BasicType) addressID string 

[] (28) (BasicVariable BasicType) cardID string 

[] (29) (BasicVariable BasicType) cartID string 

