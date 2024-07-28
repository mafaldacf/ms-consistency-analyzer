[] (-1) (PointerVariable PointerType) s (*order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase} 
[__] (-1) (ServiceVariable ServiceType) users user.UserService 
[__] (-1) (ServiceVariable ServiceType) carts cart.CartService 
[__] (-1) (ServiceVariable ServiceType) payments payment.PaymentService 
[__] (-1) (ServiceVariable ServiceType) shipping shipping.ShippingService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (77) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) orderID string // read(order_db), 
[_] (78) (Reference BasicType) ref <orderID string> @ FrontendService // read(order_db), 

[] (-1) (SliceVariable UserType) filter primitive.D // read(order_db), 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} // read(order_db), 
[__] (0) (FieldVariable FieldType) string // read(order_db), 
[___] (-1) (BasicVariable BasicType) orderID string // read(order_db), 
[____] (78) (Reference BasicType) ref <orderID string> @ FrontendService // read(order_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) cursor NoSQLCursor {database = order_service, collection = orders} // read(order_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) order order.Order struct{ID string, CustomerID string, Customer user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status string}, Date string, Total float32} 

