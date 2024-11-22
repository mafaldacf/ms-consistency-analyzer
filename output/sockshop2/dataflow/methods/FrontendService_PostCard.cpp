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

[] (BasicObject BasicType) userID string

[] (StructObject UserType) card user.Card struct{LongNum string, Expires string, CCV string, ID string}

