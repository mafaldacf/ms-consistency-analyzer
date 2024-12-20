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

    --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[0] (BasicObject BasicType) employeeID string

    --> w-tainted: write(employees_db.Employee.Name) {1}
[0] (BasicObject BasicType) name string

    --> w-tainted: write(employees_db.Employee.IBAN) {1}
[0] (BasicObject BasicType) IBAN string

    --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[0] (BasicObject BasicType) freelancerID string

    --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[0] (BasicObject BasicType) rate string

    --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[0] (BasicObject BasicType) terms string

    --> w-tainted: write(employees_db.Employee) {1}
[0] (StructObject UserType) employee app_constraints_specialization.Employee struct{EmployeeID string, Name string, IBAN string, SpecFlag string}
     --> w-tainted: write(employees_db.Employee) {1}
[_1] (Reference UserType) ref <employee app_constraints_specialization.Employee struct{EmployeeID string, Name string, IBAN string, SpecFlag "freelancer" string}> @ EmployeeService
      --> w-tainted: write(employees_db.Employee.EmployeeID) {1}
[__2] (FieldObject FieldType) EmployeeID string
       --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[___3] (BasicObject BasicType) employeeID string
        --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
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
      --> w-tainted: write(employees_db.Employee.SpecFlag) {1}
[__2] (FieldObject FieldType) SpecFlag "freelancer" string
       --> w-tainted: write(employees_db.Employee.SpecFlag) {1}
[___3] (BasicObject BasicType) "freelancer" string

    --> w-tainted: write(freelancers_db.Freelancer) {1}
[0] (StructObject UserType) freelancer app_constraints_specialization.Freelancer struct{EmployeeID string, FreelancerID string, Rate string, Terms string}
     --> w-tainted: write(freelancers_db.Freelancer) {1}
[_1] (Reference UserType) ref <freelancer app_constraints_specialization.Freelancer struct{EmployeeID string, FreelancerID string, Rate string, Terms string}> @ EmployeeService
      --> w-tainted: write(freelancers_db.Freelancer) {1}
[__2] (Reference UserType) ref <employee app_constraints_specialization.Freelancer struct{EmployeeID string, FreelancerID string, Rate string, Terms string}> @ FreelancerService
       --> w-tainted: write(freelancers_db.Freelancer.EmployeeID) {1}
[___3] (FieldObject FieldType) EmployeeID string
        --> w-tainted: write(freelancers_db.Freelancer.EmployeeID, employees_db.Employee.EmployeeID) {2}
[____4] (BasicObject BasicType) employeeID string
         --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[_____5] (Reference BasicType) ref <employeeID string> @ EmployeeService
          --> w-tainted: write(employees_db.Employee.EmployeeID, freelancers_db.Freelancer.EmployeeID) {2}
[______6] (Reference BasicType) ref <employeeID string> @ Frontend
       --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[___3] (FieldObject FieldType) FreelancerID string
        --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[____4] (BasicObject BasicType) freelancerID string
         --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[_____5] (Reference BasicType) ref <freelancerID string> @ EmployeeService
          --> w-tainted: write(freelancers_db.Freelancer.FreelancerID) {1}
[______6] (Reference BasicType) ref <freelancerID string> @ Frontend
       --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[___3] (FieldObject FieldType) Rate string
        --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[____4] (BasicObject BasicType) rate string
         --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[_____5] (Reference BasicType) ref <rate string> @ EmployeeService
          --> w-tainted: write(freelancers_db.Freelancer.Rate) {1}
[______6] (Reference BasicType) ref <rate string> @ Frontend
       --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[___3] (FieldObject FieldType) Terms string
        --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[____4] (BasicObject BasicType) terms string
         --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[_____5] (Reference BasicType) ref <terms string> @ EmployeeService
          --> w-tainted: write(freelancers_db.Freelancer.Terms) {1}
[______6] (Reference BasicType) ref <terms string> @ Frontend

[0] (InterfaceObject UserType) err .error
[_1] (Reference BasicType) ref <nil> @ EmployeeService

