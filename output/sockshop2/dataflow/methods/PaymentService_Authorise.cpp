[] (-1) (PointerVariable PointerType) s (*payment.paymentImpl struct{declineOverAmount float32}) 
[_] (0) (StructVariable UserType) payment.paymentImpl struct{declineOverAmount float32} 
[__] (-1) (BasicVariable BasicType) declineOverAmount float32 

[] (22) (InterfaceVariable UserType) ctx context.Context 
[_] (22) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (17) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) amount float32 
[_] (27) (Reference BasicType) ref <amount 10 float32> @ OrderService // write(order_db), 

[] (-1) (StructVariable UserType) authorization payment.Authorisation struct{Authorised bool, Message string} 
[_] (0) (FieldVariable FieldType) Message "Payment declined: amount exceeds" string 
[__] (0) (BasicVariable BasicType) "Payment declined: amount exceeds" string 
[_] (0) (FieldVariable FieldType) Authorised false bool 
[__] (0) (BasicVariable BasicType) false bool 

