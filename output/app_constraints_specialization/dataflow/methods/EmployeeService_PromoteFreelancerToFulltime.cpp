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

    --> w-tainted: write(fulltimes_db.Fulltime.EmployeeID) {1}
[0] (BasicObject BasicType) employeeID string
     --> w-tainted: write(fulltimes_db.Fulltime.EmployeeID) {1}
[_1] (Reference BasicType) ref <employeeID string> @ Frontend

[0] (BasicObject BasicType) name string
[_1] (Reference BasicType) ref <name string> @ Frontend

[0] (BasicObject BasicType) IBAN string
[_1] (Reference BasicType) ref <IBAN string> @ Frontend

    --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[0] (BasicObject BasicType) fulltimeID string
     --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[_1] (Reference BasicType) ref <fulltimeID string> @ Frontend

    --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[0] (BasicObject BasicType) salary string
     --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[_1] (Reference BasicType) ref <salary string> @ Frontend

    --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[0] (BasicObject BasicType) position string
     --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[_1] (Reference BasicType) ref <position string> @ Frontend

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = employees, collection = employees}

[0] (InterfaceObject UserType) err .error

[0] (StructObject UserType) fulltime app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}

[0] (BasicObject BasicType) err1 error

[0] (BasicObject BasicType) err2 error

[0] (BasicObject BasicType) err3 error

[0] (StructObject UserType) wg sync.WaitGroup

