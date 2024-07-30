[] (-1) (PointerVariable PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}) 
[_] (0) (StructVariable UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService} 
[__] (-1) (ServiceVariable ServiceType) user user.UserService 
[__] (-1) (ServiceVariable ServiceType) catalogue catalogue.CatalogueService 
[__] (-1) (ServiceVariable ServiceType) cart cart.CartService 
[__] (-1) (ServiceVariable ServiceType) order order.OrderService 

[] (49) (InterfaceVariable UserType) ctx context.Context 

[] (51) (BasicVariable BasicType) sessionID string 

[] (50) (BasicVariable BasicType) itemID string 

[] (56) (BasicVariable BasicType) quantity int 

[] (-1) (StructVariable UserType) item catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string} 
[_] (-1) (FieldVariable FieldType) ID string 
[__] (54) (BasicVariable BasicType) ID string 
[_] (-1) (FieldVariable FieldType) Price float32 
[__] (58) (BasicVariable BasicType) Price float32 

[] (-1) (InterfaceVariable UserType) err .error 

