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

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{ "customerid" string,  string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders}

[] (InterfaceObject UserType) _ .error

[] (BlueprintBackendObject BlueprintBackendType) cursor NoSQLCursor {database = order_service, collection = orders}
[_] (ArrayObject ArrayType) orders []order.Order struct{ID string, CustomerID string, Customer user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status string}, Date string, Total float32}

[] (InterfaceObject UserType) err .error

[] (ArrayObject ArrayType) orders []order.Order struct{ID string, CustomerID string, Customer user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status string}, Date string, Total float32}

[] (InterfaceObject UserType) err .error

