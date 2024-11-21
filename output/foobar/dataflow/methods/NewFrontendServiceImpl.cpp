[] (InterfaceObject UserType) ctx context.Context

[] (ServiceObject ServiceType) fooService foo.FooService

[] (ServiceObject ServiceType) barService bar.BarService

[] (PointerObject PointerType) d (*foobar.FrontendServiceImpl struct{fooService foo.FooService, barService bar.BarService})
[_] (StructObject UserType) foobar.FrontendServiceImpl struct{fooService foo.FooService, barService bar.BarService}
[__] (FieldObject FieldType) barService bar.BarService
[___] (ServiceObject ServiceType) barService bar.BarService
[__] (FieldObject FieldType) fooService foo.FooService
[___] (ServiceObject ServiceType) fooService foo.FooService

