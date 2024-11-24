[] (PointerObject PointerType) s (*payment.paymentImpl struct{declineOverAmount float32})
[_] (StructObject UserType) payment.paymentImpl struct{declineOverAmount 50 float32}
[__] (FieldObject FieldType) declineOverAmount 50 float32
[___] (BasicObject BasicType) 50 float32

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) amount float32

[] (StructObject UserType) authorization payment.Authorisation struct{Authorised false bool, Message "Payment declined: amount exceeds" string}
[_] (FieldObject FieldType) Authorised false bool
[__] (BasicObject BasicType) false bool
[_] (FieldObject FieldType) Message "Payment declined: amount exceeds" string
[__] (BasicObject BasicType) "Payment declined: amount exceeds" string

