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

    --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[0] (BasicObject BasicType) employeeID string
     --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[_1] (Reference BasicType) ref <employeeID string> @ Frontend

    --> w-tainted: write(employees_db.Employee.Name) {1}
[0] (BasicObject BasicType) name string
     --> w-tainted: write(employees_db.Employee.Name) {1}
[_1] (Reference BasicType) ref <name string> @ Frontend

    --> w-tainted: write(employees_db.Employee.IBAN) {1}
[0] (BasicObject BasicType) IBAN string
     --> w-tainted: write(employees_db.Employee.IBAN) {1}
[_1] (Reference BasicType) ref <IBAN string> @ Frontend

    --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[0] (BasicObject BasicType) freelancerID string
     --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[_1] (Reference BasicType) ref <freelancerID string> @ Frontend

    --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[0] (BasicObject BasicType) rate string
     --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[_1] (Reference BasicType) ref <rate string> @ Frontend

    --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[0] (BasicObject BasicType) terms string
     --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[_1] (Reference BasicType) ref <terms string> @ Frontend

    --> w-tainted: write(employees_db.Employee) {1}
[0] (StructObject UserType) employee app_constraints_specialization.Employee struct{EmployeeID string, Name string, IBAN string, Specialization "freelancer" string}
     --> w-tainted: write(employees_db.Employee.EmployeeID) {1}
[_1] (FieldObject FieldType) EmployeeID string
      --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[__2] (BasicObject BasicType) employeeID string
       --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[___3] (Reference BasicType) ref <employeeID string> @ Frontend
     --> w-tainted: write(employees_db.Employee.IBAN) {1}
[_1] (FieldObject FieldType) IBAN string
      --> w-tainted: write(employees_db.Employee.IBAN) {1}
[__2] (BasicObject BasicType) IBAN string
       --> w-tainted: write(employees_db.Employee.IBAN) {1}
[___3] (Reference BasicType) ref <IBAN string> @ Frontend
     --> w-tainted: write(employees_db.Employee.Name) {1}
[_1] (FieldObject FieldType) Name string
      --> w-tainted: write(employees_db.Employee.Name) {1}
[__2] (BasicObject BasicType) name string
       --> w-tainted: write(employees_db.Employee.Name) {1}
[___3] (Reference BasicType) ref <name string> @ Frontend
     --> w-tainted: write(employees_db.Employee.Specialization) {1}
[_1] (FieldObject FieldType) Specialization "freelancer" string
      --> w-tainted: write(employees_db.Employee.Specialization) {1}
[__2] (BasicObject BasicType) "freelancer" string

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = employees, collection = employees}

[0] (InterfaceObject UserType) err .error

[0] (InterfaceObject UserType) err .error

    --> w-tainted: write(freelancers_db.Freelancer) {1}
[0] (StructObject UserType) freelancer app_constraints_specialization.Freelancer struct{EmployeeID string, FreelancerID string, Rate string, Terms string}
     --> w-tainted: write(freelancers_db.Freelancer) {1}
[_1] (Reference UserType) ref <employee app_constraints_specialization.Freelancer struct{EmployeeID string, FreelancerID string, Rate string, Terms string}> @ FreelancerService
      --> w-tainted: write(freelancers_db.Freelancer.EmployeeID) {1}
[__2] (FieldObject FieldType) EmployeeID string
       --> w-tainted: write(freelancers_db.Freelancer.EmployeeID, employees_db.Employee.EmployeeID) {2}
[___3] (BasicObject BasicType) employeeID string
        --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[____4] (Reference BasicType) ref <employeeID string> @ EmployeeService
         --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[_____5] (Reference BasicType) ref <employeeID string> @ Frontend
      --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[__2] (FieldObject FieldType) FreelancerID string
       --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[___3] (BasicObject BasicType) freelancerID string
        --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[____4] (Reference BasicType) ref <freelancerID string> @ EmployeeService
         --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[_____5] (Reference BasicType) ref <freelancerID string> @ Frontend
      --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[__2] (FieldObject FieldType) Rate string
       --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[___3] (BasicObject BasicType) rate string
        --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[____4] (Reference BasicType) ref <rate string> @ EmployeeService
         --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[_____5] (Reference BasicType) ref <rate string> @ Frontend
      --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[__2] (FieldObject FieldType) Terms string
       --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[___3] (BasicObject BasicType) terms string
        --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[____4] (Reference BasicType) ref <terms string> @ EmployeeService
         --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[_____5] (Reference BasicType) ref <terms string> @ Frontend

[0] (InterfaceObject UserType) err .error
[_1] (Reference UserType) ref <err .error> @ FreelancerService

