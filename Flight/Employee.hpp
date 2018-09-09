#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "Human.hpp"

class Employee : public Human {
private:
	int id;
public:
	Employee(const std::string &name, int id);
	int getID() const;
	~Employee();
};

#endif
