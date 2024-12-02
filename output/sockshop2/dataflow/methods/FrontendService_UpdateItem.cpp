[0] (PointerObject PointerType) f (*frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService})
[_1] (StructObject UserType) frontend.FrontendImpl struct{user user.UserService, catalogue catalogue.CatalogueService, cart cart.CartService, order order.OrderService}
[__2] (FieldObject FieldType) cart cart.CartService
[___3] (ServiceObject ServiceType) cart cart.CartService
[__2] (FieldObject FieldType) catalogue catalogue.CatalogueService
[___3] (ServiceObject ServiceType) catalogue catalogue.CatalogueService
[__2] (FieldObject FieldType) order order.OrderService
[___3] (ServiceObject ServiceType) order order.OrderService
[__2] (FieldObject FieldType) user user.UserService
[___3] (ServiceObject ServiceType) user user.UserService

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) sessionID string

[0] (BasicObject BasicType) itemID string

[0] (BasicObject BasicType) quantity int

[0] (StructObject UserType) item catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}
[_1] (FieldObject FieldType) ID string
[__2] (BasicObject BasicType) ID string
[_1] (FieldObject FieldType) Price float32
[__2] (BasicObject BasicType) Price float32

[0] (InterfaceObject UserType) err .error

