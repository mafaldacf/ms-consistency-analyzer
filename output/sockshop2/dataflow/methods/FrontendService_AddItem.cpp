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

[] (1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (BasicVariable BasicType) sessionID string 

[] (2) (BasicVariable BasicType) itemID string 

[] (3) (BasicVariable BasicType) sessionID string 

[] (-1) (StructVariable UserType) sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 
[_] (-1) (FieldVariable FieldType) ID string 
[__] (10) (BasicVariable BasicType) ID string 
[_] (-1) (FieldVariable FieldType) Price float32 
[__] (8) (BasicVariable BasicType) Price float32 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) _ cart.Item struct{ID string, Quantity 1 int, UnitPrice float32} 

[] (-1) (InterfaceVariable UserType) err .error 

