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

[] (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[_] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 

[] (BasicVariable BasicType) addressID string 
[_] (Reference BasicType) ref <addressID string> @ FrontendService 

[] (BasicVariable BasicType) cardID string 
[_] (Reference BasicType) ref <cardID string> @ FrontendService 

[] (BasicVariable BasicType) cartID string 
[_] (Reference BasicType) ref <cartID string> @ FrontendService 

[] (StructVariable UserType) wg sync.WaitGroup 

[] (ArrayVariable ArrayType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 

[] (ArrayVariable ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} 

[] (ArrayVariable ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} 

[] (BasicVariable BasicType) amount 10 float32 // write(order_db), 

[] (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(shipqueue), write(shipdb), 
[_] (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[__] (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[_] (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[__] (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[___] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[__] (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 

[] (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(order_db), 
[_] (FieldVariable FieldType) ID string // write(order_db), 
[__] (BasicVariable BasicType) ID string // write(order_db), 

[] (InterfaceVariable UserType) err .error 

[] (StructVariable UserType) order order.Order struct{ID string, CustomerID string, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}, Date string, Total 10 float32, Total float32} // write(order_db), 
[_] (FieldVariable FieldType) Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(order_db), 
[__] (StructVariable UserType) user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(order_db), 
[_] (FieldVariable FieldType) Card user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(order_db), 
[__] (StructVariable UserType) user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(order_db), 
[_] (FieldVariable FieldType) CustomerID string // write(order_db), 
[__] (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[___] (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (FieldVariable FieldType) Date string // write(order_db), 
[__] (BasicVariable BasicType) string // write(order_db), 
[_] (FieldVariable FieldType) ID string // write(order_db), 
[__] (BasicVariable BasicType) ID string // write(order_db), 
[_] (FieldVariable FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 
[__] (ArrayVariable ArrayType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 
[_] (FieldVariable FieldType) Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(order_db), 
[__] (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(order_db), 
[___] (FieldVariable FieldType) ID string // write(order_db), 
[____] (BasicVariable BasicType) ID string // write(order_db), 
[_] (FieldVariable FieldType) Total 10 float32 // write(order_db), 
[__] (BasicVariable BasicType) amount 10 float32 // write(order_db), 

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders} 

[] (InterfaceVariable UserType) _ .error 

[] (InterfaceVariable UserType) err .error 

