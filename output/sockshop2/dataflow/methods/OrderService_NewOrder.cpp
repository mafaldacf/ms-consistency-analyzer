[] (PointerObject PointerType) s (*order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase})
[_] (StructObject UserType) order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase}
[__] (FieldObject FieldType) carts cart.CartService
[___] (ServiceObject ServiceType) cartService cart.CartService
[__] (FieldObject FieldType) db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) orderDB NoSQLDatabase
[__] (FieldObject FieldType) payments payment.PaymentService
[___] (ServiceObject ServiceType) payments payment.PaymentService
[__] (FieldObject FieldType) shipping shipping.ShippingService
[___] (ServiceObject ServiceType) shipping shipping.ShippingService
[__] (FieldObject FieldType) users user.UserService
[___] (ServiceObject ServiceType) userService user.UserService

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) customerID string

[] (BasicObject BasicType) addressID string

[] (BasicObject BasicType) cardID string

[] (BasicObject BasicType) cartID string

[] (StructObject UserType) wg sync.WaitGroup

[] (ArrayObject ArrayType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32}

[] (ArrayObject ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}

[] (ArrayObject ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string}

[] (BasicObject BasicType) amount 10 float32

[] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) string
[_] (FieldObject FieldType) Name string
[__] (BasicObject BasicType) customerID string
[_] (FieldObject FieldType) Status "awaiting shipment" string
[__] (BasicObject BasicType) "awaiting shipment" string

[] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string

[] (InterfaceObject UserType) err .error

[] (StructObject UserType) order order.Order struct{ID string, CustomerID string, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}, Date string, Total 10 float32, Total float32}
[_] (FieldObject FieldType) Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[__] (StructObject UserType) user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[_] (FieldObject FieldType) Card user.Card struct{LongNum string, Expires string, CCV string, ID string}
[__] (StructObject UserType) user.Card struct{LongNum string, Expires string, CCV string, ID string}
[_] (FieldObject FieldType) CustomerID string
[__] (BasicObject BasicType) customerID string
[_] (FieldObject FieldType) Date string
[__] (BasicObject BasicType) string
[_] (FieldObject FieldType) ID string
[__] (BasicObject BasicType) ID string
[_] (FieldObject FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}
[__] (ArrayObject ArrayType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32}
[_] (FieldObject FieldType) Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[__] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[___] (FieldObject FieldType) ID string
[____] (BasicObject BasicType) ID string
[_] (FieldObject FieldType) Total 10 float32
[__] (BasicObject BasicType) amount 10 float32

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders}

[] (InterfaceObject UserType) _ .error

[] (InterfaceObject UserType) err .error

