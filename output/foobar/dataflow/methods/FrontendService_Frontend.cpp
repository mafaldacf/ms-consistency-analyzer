[0] (PointerObject PointerType) d (*foobar.FrontendServiceImpl struct{barService bar.BarService, fooService foo.FooService})
[_1] (StructObject UserType) foobar.FrontendServiceImpl struct{barService bar.BarService, fooService foo.FooService}
[__2] (FieldObject FieldType) barService bar.BarService
[___3] (ServiceObject ServiceType) barService bar.BarService
[__2] (FieldObject FieldType) fooService foo.FooService
[___3] (ServiceObject ServiceType) fooService foo.FooService

[0] (InterfaceObject UserType) ctx context.Context

[0] (BasicObject BasicType) f string
[_1] (Reference BasicType) ref <string> @ FooService

[0] (InterfaceObject UserType) err1 .error
[_1] (Reference BasicType) ref <nil> @ FooService

[0] (BasicObject BasicType) b string
[_1] (Reference BasicType) ref <string> @ BarService

[0] (InterfaceObject UserType) err2 .error
[_1] (Reference BasicType) ref <nil> @ BarService

