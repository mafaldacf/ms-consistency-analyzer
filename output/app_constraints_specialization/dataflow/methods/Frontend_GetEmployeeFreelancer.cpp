[0] (PointerObject PointerType) u (*app_constraints_specialization.FrontendImpl struct{employeeService app_constraints_specialization.EmployeeService, freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService})
[_1] (StructObject UserType) app_constraints_specialization.FrontendImpl struct{employeeService app_constraints_specialization.EmployeeService, freelancerService app_constraints_specialization.FreelancerService, fulltimeService app_constraints_specialization.FulltimeService}
[__2] (FieldObject FieldType) employeeService app_constraints_specialization.EmployeeService
[___3] (ServiceObject ServiceType) employeeService app_constraints_specialization.EmployeeService
[__2] (FieldObject FieldType) freelancerService app_constraints_specialization.FreelancerService
[___3] (ServiceObject ServiceType) freelancerService app_constraints_specialization.FreelancerService
[__2] (FieldObject FieldType) fulltimeService app_constraints_specialization.FulltimeService
[___3] (ServiceObject ServiceType) fulltimeService app_constraints_specialization.FulltimeService

[0] (InterfaceObject UserType) ctx context.Context

    --> r-tainted: read(freelancers_db.Freelancer.FreelancerID) {1}
[0] (BasicObject BasicType) freelancerID string

