[] (-1) (PointerVariable PointerType) s (*order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) shipping shipping.ShippingService 
[___] (-1) (ServiceVariable ServiceType) shipping shipping.ShippingService 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) orderDB NoSQLDatabase 
[__] (0) (FieldVariable FieldType) users user.UserService 
[___] (-1) (ServiceVariable ServiceType) userService user.UserService 
[__] (0) (FieldVariable FieldType) carts cart.CartService 
[___] (-1) (ServiceVariable ServiceType) cartService cart.CartService 
[__] (0) (FieldVariable FieldType) payments payment.PaymentService 
[___] (-1) (ServiceVariable ServiceType) payments payment.PaymentService 

[] (-1) (InterfaceVariable UserType) ctx context.Context 
[_] (28) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) orderID string 
[_] (29) (Reference BasicType) ref <orderID string> @ FrontendService 

[] (-1) (SliceVariable UserType) filter primitive.D 
[_] (0) (StructVariable StructType) struct{ "id" string,  string} 
[__] (0) (FieldVariable FieldType) string 
[___] (-1) (BasicVariable BasicType) orderID string 
[____] (29) (Reference BasicType) ref <orderID string> @ FrontendService 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) cursor NoSQLCursor {database = order_service, collection = orders} 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) order order.Order struct{ID string, CustomerID string, Address []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card []user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}, Date string, Total 10 float32, Total float32} 

