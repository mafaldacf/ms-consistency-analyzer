[] (PointerObject PointerType) d (*foobar.FrontendServiceImpl struct{fooService foo.FooService, barService bar.BarService})
[_] (StructObject UserType) foobar.FrontendServiceImpl struct{fooService foo.FooService, barService bar.BarService}
[__] (FieldObject FieldType) barService bar.BarService
[___] (ServiceObject ServiceType) barService bar.BarService
[__] (FieldObject FieldType) fooService foo.FooService
[___] (ServiceObject ServiceType) fooService foo.FooService

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) f string
[_] (Reference AddressType) ref <(&"Foo: " string)> @ FooService
[__] (BasicObject BasicType) "Foo: " string

[] (InterfaceObject UserType) err1 .error
[_] (Reference BasicType) ref <nil> @ FooService

[] (BasicObject BasicType) b string
[_] (Reference AddressType) ref <(&"Bar: " string)> @ BarService
[__] (BasicObject BasicType) "Bar: " string

[] (InterfaceObject UserType) err2 .error
[_] (Reference BasicType) ref <nil> @ BarService

