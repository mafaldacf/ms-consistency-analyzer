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

[0] (BasicObject BasicType) orderID string

[0] (SliceObject UserType) filter primitive.D
[_1] (StructObject StructType) struct{ string,  "id" string,  string}

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders}

[0] (InterfaceObject UserType) _ .error

[0] (BlueprintBackendObject BlueprintBackendType) cursor NoSQLCursor {database = order_service, collection = orders}
[_1] (StructObject UserType) order order.Order struct{ID string, CustomerID string, Customer user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status string}, Date string, Total float32}

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) order order.Order struct{ID string, CustomerID string, Customer user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status string}, Date string, Total float32}

