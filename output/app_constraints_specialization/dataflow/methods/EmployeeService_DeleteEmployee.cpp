[0] (PointerObject PointerType) s (*app_constraints_specialization.EmployeeServiceImpl struct{freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService, internService app_constraints_specialization.InternService, employeesDB NoSQLDatabase})
[_1] (StructObject UserType) app_constraints_specialization.EmployeeServiceImpl struct{freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService, internService app_constraints_specialization.InternService, employeesDB NoSQLDatabase}
[__2] (FieldObject FieldType) employeesDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) employeesDB NoSQLDatabase
[__2] (FieldObject FieldType) freelancerService app_constraints_specialization.FreelancerService
[___3] (ServiceObject ServiceType) freelancerService app_constraints_specialization.FreelancerService
[__2] (FieldObject FieldType) fulltimeService app_constraints_specialization.FulltimeService
[___3] (ServiceObject ServiceType) fulltimeService app_constraints_specialization.FulltimeService
[__2] (FieldObject FieldType) internService app_constraints_specialization.InternService
[___3] (ServiceObject ServiceType) internService app_constraints_specialization.InternService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Frontend

[0] (BasicObject BasicType) employeeID string
[_1] (Reference BasicType) ref <employeeID string> @ Frontend

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = employees, collection = employees}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) filter primitive.D
[_1] (StructObject StructType) struct{Key "freelancerID" string, Key "freelancerID" string, Value string, Value string}
[__2] (FieldObject FieldType) Key "freelancerID" string
[___3] (BasicObject BasicType) "freelancerID" string
[__2] (FieldObject FieldType) Value string
[___3] (BasicObject BasicType) employeeID string
[____4] (Reference BasicType) ref <employeeID string> @ Frontend

[0] (InterfaceObject UserType) err .error

