#ifndef FLIGHTATTENDANT_HPP
#define FLIGHTATTENDANT_HPP

#include "Employee.hpp"
#include "Country.hpp"
#include <vector>

class FlightAttendant : public Employee {
private:
	FlightAttendant& operator=(const FlightAttendant& other);
	FlightAttendant(const FlightAttendant& other);
    std::vector<Country::Language> spokenLanguages;

public:
    FlightAttendant(const std::string &name, int id);
    void addLanguage(Country::Language language);
    bool canSpeak(Country::Language language) const;
    int numOfLanguage();
    ~FlightAttendant();

};

#endif
