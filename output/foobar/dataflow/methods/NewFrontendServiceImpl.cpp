[] (-1) (InterfaceVariable UserType) ctx context.Context 

[] (-1) (ServiceVariable ServiceType) fooService foo.FooService 

[] (-1) (ServiceVariable ServiceType) barService bar.BarService 

[] (-1) (AddressVariable AddressType) d (&foobar.FrontendServiceImpl struct{barService bar.BarService, fooService foo.FooService}) 
[_] (0) (StructVariable UserType) foobar.FrontendServiceImpl struct{barService bar.BarService, fooService foo.FooService} 
[__] (0) (FieldVariable FieldType) barService bar.BarService 
[___] (-1) (ServiceVariable ServiceType) barService bar.BarService 
[__] (0) (FieldVariable FieldType) fooService foo.FooService 
[___] (-1) (ServiceVariable ServiceType) fooService foo.FooService 

