[] (-1) (PointerVariable PointerType) s (*order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase} 
[__] (-1) (ServiceVariable ServiceType) shipping shipping.ShippingService 
[__] (-1) (BlueprintBackendVariable BlueprintBackendType) db NoSQLDatabase 
[__] (-1) (ServiceVariable ServiceType) users user.UserService 
[__] (-1) (ServiceVariable ServiceType) carts cart.CartService 
[__] (-1) (ServiceVariable ServiceType) payments payment.PaymentService 

[] (22) (InterfaceVariable UserType) ctx context.Context 
[_] (17) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (24) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[_] (18) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 

[] (25) (BasicVariable BasicType) addressID string 
[_] (19) (Reference BasicType) ref <addressID string> @ FrontendService 

[] (26) (BasicVariable BasicType) cardID string 
[_] (20) (Reference BasicType) ref <cardID string> @ FrontendService 

[] (23) (BasicVariable BasicType) cartID string 
[_] (21) (Reference BasicType) ref <cartID string> @ FrontendService 

[] (-1) (StructVariable UserType) wg sync.WaitGroup 

[] (-1) (ArrayVariable ArrayType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32} 

[] (-1) (ArrayVariable ArrayType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} 

[] (-1) (ArrayVariable ArrayType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} 

[] (-1) (SliceVariable SliceType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable SliceType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(order_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (SliceVariable SliceType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(order_db), 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (27) (BasicVariable BasicType) amount 10 float32 // write(order_db), 

[] (28) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(shipqueue), write(shipdb), 
[_] (31) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[__] (32) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[_] (33) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[__] (24) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[___] (18) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (29) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[__] (30) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 

[] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(order_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) ID string // write(order_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) order order.Order struct{ID string, CustomerID string, Customer user.User struct{FirstName string, LastName string, Email string, Username string, Password string, Addresses user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Cards user.Card struct{LongNum string, Expires string, CCV string, ID string}, UserID string, Salt string}, Address user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status string}, Date string, Total float32} // write(order_db), 
[_] (0) (FieldVariable FieldType) Card []user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(order_db), 
[__] (-1) (SliceVariable SliceType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(order_db), 
[_] (0) (FieldVariable FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 
[__] (-1) (SliceVariable SliceType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 
[_] (0) (FieldVariable FieldType) Shipment shipping.Shipment struct{ID string, Name string, Status string} // write(order_db), 
[__] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status string} // write(order_db), 
[___] (-1) (FieldVariable FieldType) ID string // write(order_db), 
[____] (-1) (BasicVariable BasicType) ID string // write(order_db), 
[_] (0) (FieldVariable FieldType) Date string // write(order_db), 
[__] (0) (BasicVariable BasicType) string // write(order_db), 
[_] (0) (FieldVariable FieldType) Total 10 float32 // write(order_db), 
[__] (27) (BasicVariable BasicType) amount 10 float32 // write(order_db), 
[_] (0) (FieldVariable FieldType) ID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) ID string // write(order_db), 
[_] (0) (FieldVariable FieldType) CustomerID string // write(order_db), 
[__] (24) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[___] (18) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (0) (FieldVariable FieldType) Address []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(order_db), 
[__] (-1) (SliceVariable SliceType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(order_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (InterfaceVariable UserType) err .error 

