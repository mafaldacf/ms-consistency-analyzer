[] (-1) (PointerVariable PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}) 
[_] (0) (StructVariable UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService} 
[__] (0) (FieldVariable FieldType) user user.UserService 
[___] (-1) (ServiceVariable ServiceType) user user.UserService 
[__] (0) (FieldVariable FieldType) catalogue catalogue.CatalogueService 
[___] (-1) (ServiceVariable ServiceType) catalogue catalogue.CatalogueService 
[__] (0) (FieldVariable FieldType) cart cart.CartService 
[___] (-1) (ServiceVariable ServiceType) cart cart.CartService 
[__] (0) (FieldVariable FieldType) order order.OrderService 
[___] (-1) (ServiceVariable ServiceType) order order.OrderService 

[] (35) (InterfaceVariable UserType) ctx context.Context 

[] (36) (BasicVariable BasicType) userID string // write(shipqueue), write(shipdb), write(order_db), 

[] (37) (BasicVariable BasicType) addressID string 

[] (38) (BasicVariable BasicType) cardID string 

[] (39) (BasicVariable BasicType) cartID string 

