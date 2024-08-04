[] (InterfaceVariable UserType) ctx context.Context 

[] (ServiceVariable ServiceType) fooService foo.FooService 

[] (ServiceVariable ServiceType) barService bar.BarService 

[] (PointerVariable PointerType) d (*foobar.FrontendServiceImpl struct{fooService foo.FooService, barService bar.BarService}) 
[_] (StructVariable UserType) foobar.FrontendServiceImpl struct{fooService foo.FooService, barService bar.BarService} 
[__] (FieldVariable FieldType) barService bar.BarService 
[___] (ServiceVariable ServiceType) barService bar.BarService 
[__] (FieldVariable FieldType) fooService foo.FooService 
[___] (ServiceVariable ServiceType) fooService foo.FooService 

