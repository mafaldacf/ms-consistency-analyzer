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

[] (BasicObject BasicType) username string

[] (BasicObject BasicType) password string

[] (StructObject UserType) u user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}
[_] (FieldObject FieldType) UserID string
[__] (BasicObject BasicType) UserID string

[] (InterfaceObject UserType) err .error

[] (InterfaceObject UserType) err .error

