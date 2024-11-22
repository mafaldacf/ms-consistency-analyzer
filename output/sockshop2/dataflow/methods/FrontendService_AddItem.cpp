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

    --> r-tainted: read(catalogue_db._.id) {1}
[] (BasicObject BasicType) itemID string

[] (BasicObject BasicType) sessionID string

[] (StructObject UserType) sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}
     --> r-tainted: read(catalogue_db.Sock, catalogue_db.ImageURL, catalogue_db.[]string, catalogue_db.string, catalogue_db.ImageURL_1, catalogue_db.ImageURL_2, catalogue_db.TagString, catalogue_db.Tags) {8}
[_] (Reference UserType) ref <sock catalogue.Sock struct{ID string, Name string, Description string, ImageURL []string, ImageURL_1 string, ImageURL_2 string, Price float32, Quantity int, Tags []string, TagString string}> @ CatalogueService
      --> r-tainted: read(catalogue_db.ImageURL) {1}
[__] (FieldObject FieldType) ImageURL []string
       --> r-tainted: read(catalogue_db.[]string) {1}
[___] (ArrayObject SliceType) []string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) ImageURL_1 string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) ImageURL_2 string
      --> r-tainted: read(catalogue_db.ImageURL_1) {1}
[__] (FieldObject FieldType) ImageURL_1 string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) ImageURL_1 string
      --> r-tainted: read(catalogue_db.ImageURL_2) {1}
[__] (FieldObject FieldType) ImageURL_2 string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) ImageURL_2 string
      --> r-tainted: read(catalogue_db.TagString) {1}
[__] (FieldObject FieldType) TagString string
       --> r-tainted: read(catalogue_db.string) {1}
[___] (BasicObject BasicType) TagString string
      --> r-tainted: read(catalogue_db.Tags) {1}
[__] (FieldObject FieldType) Tags []string
       --> r-tainted: read(catalogue_db.[]string) {1}
[___] (SliceObject SliceType) []string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) TagString string
        --> r-tainted: read(catalogue_db.string) {1}
[____] (BasicObject BasicType) "," string
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string
[_] (FieldObject FieldType) Price float32
[__] (BasicObject BasicType) Price float32

[] (InterfaceObject UserType) err .error
[_] (Reference BasicType) ref <nil> @ CatalogueService

[] (StructObject UserType) _ cart.Item struct{ID string, Quantity int, UnitPrice float32}
[_] (Reference UserType) ref <item cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ CartService
[__] (Reference UserType) ref <cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ FrontendService
[___] (FieldObject FieldType) ID string
[____] (BasicObject BasicType) ID string
[___] (FieldObject FieldType) Quantity 1 int
[____] (BasicObject BasicType) 1 int
[___] (FieldObject FieldType) UnitPrice float32
[____] (BasicObject BasicType) Price float32
[_] (Reference UserType) ref <cart.Item struct{ID string, Quantity int, UnitPrice float32}> @ FrontendService
[__] (FieldObject FieldType) ID string
[___] (BasicObject BasicType) ID string
[__] (FieldObject FieldType) Quantity 1 int
[___] (BasicObject BasicType) 1 int
[__] (FieldObject FieldType) UnitPrice float32
[___] (BasicObject BasicType) Price float32

[] (InterfaceObject UserType) err .error
[_] (Reference BasicType) ref <nil> @ CartService

