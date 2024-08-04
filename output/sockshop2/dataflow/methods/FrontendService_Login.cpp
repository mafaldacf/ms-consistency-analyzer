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

[] (BasicVariable BasicType) username string 

[] (BasicVariable BasicType) password string 

[] (StructVariable UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} 
[_] (FieldVariable FieldType) UserID string 
[__] (BasicVariable BasicType) UserID string 

[] (InterfaceVariable UserType) err .error 

[] (InterfaceVariable UserType) err .error 

