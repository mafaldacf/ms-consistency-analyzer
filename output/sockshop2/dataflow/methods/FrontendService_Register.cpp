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

[] (75) (InterfaceVariable UserType) ctx context.Context 

[] (82) (BasicVariable BasicType) sessionID string 

[] (76) (BasicVariable BasicType) username string // write(user_db), 

[] (77) (BasicVariable BasicType) password string // write(user_db), 

[] (78) (BasicVariable BasicType) email string // write(user_db), 

[] (79) (BasicVariable BasicType) first string // write(user_db), 

[] (80) (BasicVariable BasicType) last string // write(user_db), 

[] (81) (BasicVariable BasicType) userID string 

[] (-1) (InterfaceVariable UserType) err .error 

