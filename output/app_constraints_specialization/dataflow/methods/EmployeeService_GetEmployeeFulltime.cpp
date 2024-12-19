[0] (PointerObject PointerType) s (*app_constraints_specialization.EmployeeServiceImpl struct{freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService, employeesDB NoSQLDatabase})
[_1] (StructObject UserType) app_constraints_specialization.EmployeeServiceImpl struct{freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService, employeesDB NoSQLDatabase}
[__2] (FieldObject FieldType) employeesDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) employeesDB NoSQLDatabase
[__2] (FieldObject FieldType) freelancerService app_constraints_specialization.FreelancerService
[___3] (ServiceObject ServiceType) freelancerService app_constraints_specialization.FreelancerService
[__2] (FieldObject FieldType) fulltimeService app_constraints_specialization.FulltimeService
[___3] (ServiceObject ServiceType) fulltimeService app_constraints_specialization.FulltimeService

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(fulltimes_db.Fulltime.FulltimeID) {1}
[0] (BasicObject BasicType) fulltimeID string
     --> r-tainted: read(fulltimes_db.Fulltime.FulltimeID) {1}
[_1] (Reference BasicType) ref <fulltimeID string> @ Frontend

[0] (StructObject UserType) fulltime app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}
     --> r-tainted: read(fulltimes_db.Fulltime) {1}
[_1] (Reference UserType) ref <fulltime app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}> @ FulltimeService
[_1] (FieldObject FieldType) EmployeeID string
      --> r-tainted: read(employees_db.Employee.EmployeeID) {1}
[__2] (BasicObject BasicType) EmployeeID string

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <err .error> @ FulltimeService

    --> r-tainted: read(employees_db.Employee) {1}
[0] (StructObject UserType) employee app_constraints_specialization.Employee struct{EmployeeID string, Name string, IBAN string, Specialization string}

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = employees, collection = employees}

[0] (InterfaceObject UserType) err .error

[0] (SliceObject UserType) query primitive.D
[_1] (StructObject StructType) struct{Key "employeeID" string, Key "employeeID" string, Value string, Value string}
[__2] (FieldObject FieldType) Key "employeeID" string
[___3] (BasicObject BasicType) "employeeID" string
[__2] (FieldObject FieldType) Value string
       --> r-tainted: read(employees_db.Employee.EmployeeID) {1}
[___3] (BasicObject BasicType) EmployeeID string

    --> r-tainted: read(employees_db.Employee) {1}
[0] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = employees, collection = employees}
     --> r-tainted: read(employees_db.Employee) {1}
[_1] (StructObject UserType) employee app_constraints_specialization.Employee struct{EmployeeID string, Name string, IBAN string, Specialization string}

[0] (InterfaceObject UserType) err .error

[0] (BasicObject BasicType) res bool

[0] (InterfaceObject UserType) err .error

