[] (-1) (PointerVariable PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}) 
[_] (0) (StructVariable UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService} 
[__] (-1) (ServiceVariable ServiceType) user user.UserService 
[__] (-1) (ServiceVariable ServiceType) catalogue catalogue.CatalogueService 
[__] (-1) (ServiceVariable ServiceType) cart cart.CartService 
[__] (-1) (ServiceVariable ServiceType) order order.OrderService 

[] (11) (InterfaceVariable UserType) ctx context.Context 

[] (12) (BasicVariable BasicType) userID string // write(shipqueue), write(shipdb), write(order_db), read(user_db), 

[] (13) (BasicVariable BasicType) addressID string // read(user_db), 

[] (14) (BasicVariable BasicType) cardID string // read(user_db), 

[] (15) (BasicVariable BasicType) cartID string 

