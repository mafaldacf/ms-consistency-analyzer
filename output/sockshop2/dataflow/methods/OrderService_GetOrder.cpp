[] (PointerVariable PointerType) s (*order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase}) 
[_] (StructVariable UserType) order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase} 
[__] (FieldVariable FieldType) carts cart.CartService 
[___] (ServiceVariable ServiceType) cartService cart.CartService 
[__] (FieldVariable FieldType) db NoSQLDatabase 
[___] (BlueprintBackendVariable BlueprintBackendType) orderDB NoSQLDatabase 
[__] (FieldVariable FieldType) payments payment.PaymentService 
[___] (ServiceVariable ServiceType) payments payment.PaymentService 
[__] (FieldVariable FieldType) shipping shipping.ShippingService 
[___] (ServiceVariable ServiceType) shipping shipping.ShippingService 
[__] (FieldVariable FieldType) users user.UserService 
[___] (ServiceVariable ServiceType) userService user.UserService 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) orderID string 
[_] (Reference BasicType) ref <orderID string> @ FrontendService 

[] (SliceVariable UserType) filter primitive.D 
[_] (StructVariable StructType) struct{ "id" string,  string} 
[__] (FieldVariable FieldType) string 
[___] (BasicVariable BasicType) orderID string 
[____] (Reference BasicType) ref <orderID string> @ FrontendService 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders} 

[] (InterfaceVariable UserType) _ .error 

[] (BlueprintBackendVariable BlueprintBackendType) cursor NoSQLCursor {database = order_service, collection = orders} 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) order order.Order struct{ID string, CustomerID string, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}, Date string, Total 10 float32, Total float32} 

