[] (PointerVariable PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}) 
[_] (StructVariable UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService} 
[__] (FieldVariable FieldType) cart cart.CartService 
[___] (ServiceVariable ServiceType) cart cart.CartService 
[__] (FieldVariable FieldType) catalogue catalogue.CatalogueService 
[___] (ServiceVariable ServiceType) catalogue catalogue.CatalogueService 
[__] (FieldVariable FieldType) order order.OrderService 
[___] (ServiceVariable ServiceType) order order.OrderService 
[__] (FieldVariable FieldType) user user.UserService 
[___] (ServiceVariable ServiceType) user user.UserService 

[] (InterfaceVariable UserType) ctx context.Context 

[] (BasicVariable BasicType) userID string // write(shipqueue), write(shipdb), write(order_db), 

[] (BasicVariable BasicType) addressID string 

[] (BasicVariable BasicType) cardID string 

[] (BasicVariable BasicType) cartID string 

