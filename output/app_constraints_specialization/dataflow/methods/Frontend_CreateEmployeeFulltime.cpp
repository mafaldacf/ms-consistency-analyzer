[0] (PointerObject PointerType) u (*app_constraints_specialization.FrontendImpl struct{employeeService app_constraints_specialization.EmployeeService, freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService})
[_1] (StructObject UserType) app_constraints_specialization.FrontendImpl struct{employeeService app_constraints_specialization.EmployeeService, freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService}
[__2] (FieldObject FieldType) employeeService app_constraints_specialization.EmployeeService
[___3] (ServiceObject ServiceType) employeeService app_constraints_specialization.EmployeeService
[__2] (FieldObject FieldType) freelancerService app_constraints_specialization.FreelancerService
[___3] (ServiceObject ServiceType) freelancerService app_constraints_specialization.FreelancerService
[__2] (FieldObject FieldType) fulltimeService app_constraints_specialization.FulltimeService
[___3] (ServiceObject ServiceType) fulltimeService app_constraints_specialization.FulltimeService

[0] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(employees_db.Employee.EmployeeID, fulltimes_db.Fulltime.EmployeeID) {2}
[0] (BasicObject BasicType) employeeID string

    --> w-tainted: write(employees_db.Employee.Name) {1}
[0] (BasicObject BasicType) name string

    --> w-tainted: write(employees_db.Employee.IBAN) {1}
[0] (BasicObject BasicType) IBAN string

    --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[0] (BasicObject BasicType) fulltimeID string

    --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[0] (BasicObject BasicType) salary string

    --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[0] (BasicObject BasicType) position string

    --> w-tainted: write(employees_db.Employee) {1}
[0] (StructObject UserType) employee app_constraints_specialization.Employee struct{EmployeeID string, Name string, IBAN string, Specialization string}
     --> w-tainted: write(employees_db.Employee) {1}
[_1] (Reference UserType) ref <employee app_constraints_specialization.Employee struct{EmployeeID string, Name string, IBAN string, Specialization "fulltime" string}> @ EmployeeService
      --> w-tainted: write(employees_db.Employee.EmployeeID) {1}
[__2] (FieldObject FieldType) EmployeeID string
       --> w-tainted: write(employees_db.Employee.EmployeeID, fulltimes_db.Fulltime.EmployeeID) {2}
[___3] (BasicObject BasicType) employeeID string
        --> w-tainted: write(employees_db.Employee.EmployeeID, fulltimes_db.Fulltime.EmployeeID) {2}
[____4] (Reference BasicType) ref <employeeID string> @ Frontend
      --> w-tainted: write(employees_db.Employee.IBAN) {1}
[__2] (FieldObject FieldType) IBAN string
       --> w-tainted: write(employees_db.Employee.IBAN) {1}
[___3] (BasicObject BasicType) IBAN string
        --> w-tainted: write(employees_db.Employee.IBAN) {1}
[____4] (Reference BasicType) ref <IBAN string> @ Frontend
      --> w-tainted: write(employees_db.Employee.Name) {1}
[__2] (FieldObject FieldType) Name string
       --> w-tainted: write(employees_db.Employee.Name) {1}
[___3] (BasicObject BasicType) name string
        --> w-tainted: write(employees_db.Employee.Name) {1}
[____4] (Reference BasicType) ref <name string> @ Frontend
      --> w-tainted: write(employees_db.Employee.Specialization) {1}
[__2] (FieldObject FieldType) Specialization "fulltime" string
       --> w-tainted: write(employees_db.Employee.Specialization) {1}
[___3] (BasicObject BasicType) "fulltime" string

    --> w-tainted: write(fulltimes_db.Fulltime) {1}
[0] (StructObject UserType) fulltime app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}
     --> w-tainted: write(fulltimes_db.Fulltime) {1}
[_1] (Reference UserType) ref <fulltime app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}> @ EmployeeService
      --> w-tainted: write(fulltimes_db.Fulltime) {1}
[__2] (Reference UserType) ref <employee app_constraints_specialization.Fulltime struct{EmployeeID string, FulltimeID string, Salary string, Position string}> @ FulltimeService
       --> w-tainted: write(fulltimes_db.Fulltime.EmployeeID) {1}
[___3] (FieldObject FieldType) EmployeeID string
        --> w-tainted: write(fulltimes_db.Fulltime.EmployeeID, employees_db.Employee.EmployeeID) {2}
[____4] (BasicObject BasicType) employeeID string
         --> w-tainted: write(employees_db.Employee.EmployeeID, fulltimes_db.Fulltime.EmployeeID) {2}
[_____5] (Reference BasicType) ref <employeeID string> @ EmployeeService
          --> w-tainted: write(employees_db.Employee.EmployeeID, fulltimes_db.Fulltime.EmployeeID) {2}
[______6] (Reference BasicType) ref <employeeID string> @ Frontend
       --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[___3] (FieldObject FieldType) FulltimeID string
        --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[____4] (BasicObject BasicType) freelancerID string
         --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[_____5] (Reference BasicType) ref <fulltimeID string> @ EmployeeService
          --> w-tainted: write(fulltimes_db.Fulltime.FulltimeID) {1}
[______6] (Reference BasicType) ref <fulltimeID string> @ Frontend
       --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[___3] (FieldObject FieldType) Position string
        --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[____4] (BasicObject BasicType) position string
         --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[_____5] (Reference BasicType) ref <position string> @ EmployeeService
          --> w-tainted: write(fulltimes_db.Fulltime.Position) {1}
[______6] (Reference BasicType) ref <position string> @ Frontend
       --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[___3] (FieldObject FieldType) Salary string
        --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[____4] (BasicObject BasicType) salary string
         --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[_____5] (Reference BasicType) ref <salary string> @ EmployeeService
          --> w-tainted: write(fulltimes_db.Fulltime.Salary) {1}
[______6] (Reference BasicType) ref <salary string> @ Frontend

[0] (InterfaceObject UserType) err .error
[_1] (Reference BasicType) ref <nil> @ EmployeeService

