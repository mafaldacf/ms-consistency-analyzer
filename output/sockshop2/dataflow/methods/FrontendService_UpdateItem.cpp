[] (PointerObject PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService})
[_] (StructObject UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}
[__] (FieldObject FieldType) cart cart.CartService
[___] (ServiceObject ServiceType) cart cart.CartService
[__] (FieldObject FieldType) catalogue catalogue.CatalogueService
[___] (ServiceObject ServiceType) catalogue catalogue.CatalogueService
[__] (FieldObject FieldType) order order.OrderService
[___] (ServiceObject ServiceType) order order.OrderService
[__] (FieldObject FieldType) user user.UserService
[___] (ServiceObject ServiceType) user user.UserService

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) sessionID string

[] (BasicObject BasicType) itemID string

[] (BasicObject BasicType) quantity int

[] (StructObject UserType) item catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string
[_] (FieldObject FieldType) Price float32
[__] (BasicObject BasicType) Price float32

[] (InterfaceObject UserType) err .error

