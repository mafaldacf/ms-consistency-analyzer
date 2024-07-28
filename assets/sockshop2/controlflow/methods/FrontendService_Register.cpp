[] (-1) (PointerVariable PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}) 
[_] (0) (StructVariable UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService} 
[__] (-1) (ServiceVariable ServiceType) order order.OrderService 
[__] (-1) (ServiceVariable ServiceType) user user.UserService 
[__] (-1) (ServiceVariable ServiceType) catalogue catalogue.CatalogueService 
[__] (-1) (ServiceVariable ServiceType) cart cart.CartService 

[] (33) (InterfaceVariable UserType) ctx context.Context 

[] (40) (BasicVariable BasicType) sessionID string 

[] (34) (BasicVariable BasicType) username string // write(user_db), 

[] (35) (BasicVariable BasicType) password string // write(user_db), 

[] (36) (BasicVariable BasicType) email string // write(user_db), 

[] (37) (BasicVariable BasicType) first string // write(user_db), 

[] (38) (BasicVariable BasicType) last string // write(user_db), 

[] (39) (BasicVariable BasicType) userID string 

[] (-1) (InterfaceVariable UserType) err .error 

