[] (PointerVariable PointerType) s (*payment.paymentImpl struct{declineOverAmount 50 float32}) 
[_] (StructVariable UserType) payment.paymentImpl struct{declineOverAmount 50 float32} 
[__] (FieldVariable FieldType) declineOverAmount 50 float32 
[___] (BasicVariable BasicType) 50 float32 

[] (InterfaceVariable UserType) ctx context.Context 
[_] (Reference UserType) ref <ctx context.Context> @ OrderService 
[__] (Reference UserType) ref <ctx context.Context> @ FrontendService 

[] (BasicVariable BasicType) amount float32 
[_] (Reference BasicType) ref <amount 10 float32> @ OrderService // write(order_db), 

[] (StructVariable UserType) authorization payment.Authorisation struct{Authorised false bool, Message "Payment declined: amount exceeds" string} 
[_] (FieldVariable FieldType) Authorised false bool 
[__] (BasicVariable BasicType) false bool 
[_] (FieldVariable FieldType) Message "Payment declined: amount exceeds" string 
[__] (BasicVariable BasicType) "Payment declined: amount exceeds" string 

