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

[] (BasicVariable BasicType) sessionID string 

[] (BasicVariable BasicType) username string // write(user_db), 

[] (BasicVariable BasicType) password string // write(user_db), 

[] (BasicVariable BasicType) email string // write(user_db), 

[] (BasicVariable BasicType) first string // write(user_db), 

[] (BasicVariable BasicType) last string // write(user_db), 

[] (BasicVariable BasicType) userID string 

[] (InterfaceVariable UserType) err .error 

