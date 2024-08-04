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

[] (BasicVariable BasicType) itemID string 

[] (BasicVariable BasicType) quantity int 

[] (StructVariable UserType) item catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 
[_] (FieldVariable FieldType) ID string 
[__] (BasicVariable BasicType) ID string 
[_] (FieldVariable FieldType) Price float32 
[__] (BasicVariable BasicType) Price float32 

[] (InterfaceVariable UserType) err .error 

