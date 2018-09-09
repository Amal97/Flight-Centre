#include "Employee.hpp"

// Sets the name of the employee in the human class and sets the id of the employee.
Employee::Employee(const std::string &name, int id) : Human(name) {
	this->id = id;
}

// Returns the id of the employee.
int Employee::getID() const {
	return this->id;
}

// Destructor.
Employee::~Employee(){
}