[0] (PointerObject PointerType) s (*order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase})
[_1] (StructObject UserType) order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase}
[__2] (FieldObject FieldType) carts cart.CartService
[___3] (ServiceObject ServiceType) cartService cart.CartService
[__2] (FieldObject FieldType) db NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) orderDB NoSQLDatabase
[__2] (FieldObject FieldType) payments payment.PaymentService
[___3] (ServiceObject ServiceType) payments payment.PaymentService
[__2] (FieldObject FieldType) shipping shipping.ShippingService
[___3] (ServiceObject ServiceType) shipping shipping.ShippingService
[__2] (FieldObject FieldType) users user.UserService
[___3] (ServiceObject ServiceType) userService user.UserService

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) customerID string

[0] (BasicObject BasicType) addressID string

[0] (BasicObject BasicType) cardID string

[0] (BasicObject BasicType) cartID string

[0] (StructObject UserType) wg sync.WaitGroup

[0] (ArrayObject ArrayType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32}

[0] (ArrayObject ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}

[0] (ArrayObject ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string}

[0] (BasicObject BasicType) amount 10 float32

[0] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[_1] (FieldObject FieldType) ID string
[__2] (BasicObject BasicType) string
[_1] (FieldObject FieldType) Name string
[__2] (BasicObject BasicType) customerID string
[_1] (FieldObject FieldType) Status "awaiting shipment" string
[__2] (BasicObject BasicType) "awaiting shipment" string

[0] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[_1] (FieldObject FieldType) ID string
[__2] (BasicObject BasicType) ID string

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) order order.Order struct{ID string, CustomerID string, Customer user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}, Date string, Total 10 float32}
[_1] (FieldObject FieldType) Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[__2] (StructObject UserType) user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}
[_1] (FieldObject FieldType) Card user.Card struct{LongNum string, Expires string, CCV string, ID string}
[__2] (StructObject UserType) user.Card struct{LongNum string, Expires string, CCV string, ID string}
[_1] (FieldObject FieldType) CustomerID string
[__2] (BasicObject BasicType) customerID string
[_1] (FieldObject FieldType) Date string
[__2] (BasicObject BasicType) string
[_1] (FieldObject FieldType) ID string
[__2] (BasicObject BasicType) ID string
[_1] (FieldObject FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}
[__2] (ArrayObject ArrayType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32}
[_1] (FieldObject FieldType) Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[__2] (StructObject UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}
[___3] (FieldObject FieldType) ID string
[____4] (BasicObject BasicType) ID string
[_1] (FieldObject FieldType) Total 10 float32
[__2] (BasicObject BasicType) amount 10 float32

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders}

[0] (InterfaceObject UserType) _ .error

[0] (InterfaceObject UserType) err .error

