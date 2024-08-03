[] (-1) (PointerVariable PointerType) s (*order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase}) 
[_] (0) (StructVariable UserType) order.orderImpl struct{users user.UserService, carts cart.CartService, payments payment.PaymentService, shipping shipping.ShippingService, db NoSQLDatabase} 
[__] (0) (FieldVariable FieldType) users user.UserService 
[___] (-1) (ServiceVariable ServiceType) userService user.UserService 
[__] (0) (FieldVariable FieldType) carts cart.CartService 
[___] (-1) (ServiceVariable ServiceType) cartService cart.CartService 
[__] (0) (FieldVariable FieldType) payments payment.PaymentService 
[___] (-1) (ServiceVariable ServiceType) payments payment.PaymentService 
[__] (0) (FieldVariable FieldType) shipping shipping.ShippingService 
[___] (-1) (ServiceVariable ServiceType) shipping shipping.ShippingService 
[__] (0) (FieldVariable FieldType) db NoSQLDatabase 
[___] (-1) (BlueprintBackendVariable BlueprintBackendType) orderDB NoSQLDatabase 

[] (40) (InterfaceVariable UserType) ctx context.Context 
[_] (35) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (42) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[_] (36) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 

[] (43) (BasicVariable BasicType) addressID string 
[_] (37) (Reference BasicType) ref <addressID string> @ FrontendService 

[] (44) (BasicVariable BasicType) cardID string 
[_] (38) (Reference BasicType) ref <cardID string> @ FrontendService 

[] (41) (BasicVariable BasicType) cartID string 
[_] (39) (Reference BasicType) ref <cartID string> @ FrontendService 

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

[] (45) (BasicVariable BasicType) amount 10 float32 // write(order_db), 

[] (46) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(shipqueue), write(shipdb), 
[_] (50) (FieldVariable FieldType) ID string // write(shipqueue), write(shipdb), 
[__] (51) (BasicVariable BasicType) string // write(shipqueue), write(shipdb), 
[_] (47) (FieldVariable FieldType) Name string // write(shipqueue), write(shipdb), 
[__] (42) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[___] (36) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 
[_] (48) (FieldVariable FieldType) Status "awaiting shipment" string // write(shipqueue), write(shipdb), 
[__] (49) (BasicVariable BasicType) "awaiting shipment" string // write(shipqueue), write(shipdb), 

[] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(order_db), 
[_] (-1) (FieldVariable FieldType) ID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) ID string // write(order_db), 

[] (-1) (InterfaceVariable UserType) err .error 

[] (-1) (StructVariable UserType) order order.Order struct{ID string, CustomerID string, Address []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string}, Card []user.Card struct{LongNum string, Expires string, CCV string, ID string}, Items []cart.Item struct{ID string, Quantity int, UnitPrice float32}, Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string}, Date string, Total 10 float32, Total float32} // write(order_db), 
[_] (0) (FieldVariable FieldType) Address []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(order_db), 
[__] (-1) (SliceVariable SliceType) addresses []user.Address struct{Street string, Number string, Country string, City string, PostCode string, ID string} // write(order_db), 
[_] (0) (FieldVariable FieldType) Card []user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(order_db), 
[__] (-1) (SliceVariable SliceType) cards []user.Card struct{LongNum string, Expires string, CCV string, ID string} // write(order_db), 
[_] (0) (FieldVariable FieldType) Items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 
[__] (-1) (SliceVariable SliceType) items []cart.Item struct{ID string, Quantity int, UnitPrice float32} // write(order_db), 
[_] (0) (FieldVariable FieldType) Shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(order_db), 
[__] (-1) (StructVariable UserType) shipment shipping.Shipment struct{ID string, Name string, Status "awaiting shipment" string} // write(order_db), 
[___] (-1) (FieldVariable FieldType) ID string // write(order_db), 
[____] (-1) (BasicVariable BasicType) ID string // write(order_db), 
[_] (0) (FieldVariable FieldType) Date string // write(order_db), 
[__] (0) (BasicVariable BasicType) string // write(order_db), 
[_] (0) (FieldVariable FieldType) Total 10 float32 // write(order_db), 
[__] (45) (BasicVariable BasicType) amount 10 float32 // write(order_db), 
[_] (0) (FieldVariable FieldType) ID string // write(order_db), 
[__] (-1) (BasicVariable BasicType) ID string // write(order_db), 
[_] (0) (FieldVariable FieldType) CustomerID string // write(order_db), 
[__] (42) (BasicVariable BasicType) customerID string // write(shipqueue), write(shipdb), write(order_db), 
[___] (36) (Reference BasicType) ref <userID string> @ FrontendService // write(shipqueue), write(shipdb), write(order_db), 

[] (-1) (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = order_service, collection = orders} 

[] (-1) (InterfaceVariable UserType) _ .error 

[] (-1) (InterfaceVariable UserType) err .error 

