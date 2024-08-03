[] (-1) (PointerVariable PointerType) s (*payment.paymentImpl struct{declineOverAmount 50 float32}) 
[_] (0) (StructVariable UserType) payment.paymentImpl struct{declineOverAmount 50 float32} 
[__] (0) (FieldVariable FieldType) declineOverAmount 50 float32 
[___] (-1) (BasicVariable BasicType) 50 float32 

[] (40) (InterfaceVariable UserType) ctx context.Context 
[_] (40) (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (35) (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (-1) (BasicVariable BasicType) amount float32 
[_] (45) (Reference BasicType) ref <amount 10 float32> @ OrderService // write(order_db), 

[] (-1) (StructVariable UserType) authorization payment.Authorisation struct{Authorised false bool, Message "Payment declined: amount exceeds" string} 
[_] (0) (FieldVariable FieldType) Authorised false bool 
[__] (0) (BasicVariable BasicType) false bool 
[_] (0) (FieldVariable FieldType) Message "Payment declined: amount exceeds" string 
[__] (0) (BasicVariable BasicType) "Payment declined: amount exceeds" string 

