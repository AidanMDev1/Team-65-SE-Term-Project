using namespace std;

class Employee {
public:
    Employee();
    void submitRequest() {} // request a time change for a manager
    void clockHours() {} // have the ability to clock in and out
    void checkPersonalHours() {}
    void accessAssignedProj() {}
};
class Manager : public Employee {
public:
    Manager();
    void accessProjTimes() {} // comprehensive list of times of a proj (that a manager is in charge of) of employees
    void createAnnouncement() {}
    void createProj() {}
    void assignToProj() {} // assign employees to projects
    void checkRequests() {} // checks employee requests for time changes
};
class Administrator : public Manager {
    Administrator();
    void accessAllTimes() {} // comprehensive list of all proj not just those assigned to them etc.
    void createUser() {}
    void assignRole() {}
};
