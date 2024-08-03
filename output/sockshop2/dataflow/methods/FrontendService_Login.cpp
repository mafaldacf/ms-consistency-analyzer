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

[] (70) (InterfaceVariable UserType) ctx context.Context 

[] (74) (BasicVariable BasicType) sessionID string 

[] (71) (BasicVariable BasicType) username string 

[] (72) (BasicVariable BasicType) password string 

[] (-1) (StructVariable UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string} 
[_] (-1) (FieldVariable FieldType) UserID string 
[__] (73) (BasicVariable BasicType) UserID string 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (InterfaceVariable UserType) err .error 

