[0] (PointerObject PointerType) u (*app_constraints_specialization.FrontendImpl struct{employeeService app_constraints_specialization.EmployeeService, freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService, internService app_constraints_specialization.InternService})
[_1] (StructObject UserType) app_constraints_specialization.FrontendImpl struct{employeeService app_constraints_specialization.EmployeeService, freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService, internService app_constraints_specialization.InternService}
[__2] (FieldObject FieldType) employeeService app_constraints_specialization.EmployeeService
[___3] (ServiceObject ServiceType) employeeService app_constraints_specialization.EmployeeService
[__2] (FieldObject FieldType) freelancerService app_constraints_specialization.FreelancerService
[___3] (ServiceObject ServiceType) freelancerService app_constraints_specialization.FreelancerService
[__2] (FieldObject FieldType) fulltimeService app_constraints_specialization.FulltimeService
[___3] (ServiceObject ServiceType) fulltimeService app_constraints_specialization.FulltimeService
[__2] (FieldObject FieldType) internService app_constraints_specialization.InternService
[___3] (ServiceObject ServiceType) internService app_constraints_specialization.InternService

[0] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(fulltimes_db.Fulltime.EmployeeID) {1}
[0] (BasicObject BasicType) employeeID string

[0] (BasicObject BasicType) name string

[0] (BasicObject BasicType) IBAN string

    --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[0] (BasicObject BasicType) fulltimeID string

    --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[0] (BasicObject BasicType) salary string

    --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[0] (BasicObject BasicType) position string

[0] (StructObject UserType) fulltime app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}
[_1] (Reference UserType) ref <fulltime app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}> @ EmployeeService

[0] (InterfaceObject UserType) err .error
[_1] (Reference BasicType) ref <nil> @ EmployeeService

