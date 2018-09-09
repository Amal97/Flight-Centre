#include "FlightAttendant.hpp"
#include "Employee.hpp"
#include "Human.hpp"
#include "Country.hpp"

#include <vector>

// Sets the name in human class and ID in the employee class of the flight attendant.
FlightAttendant::FlightAttendant(const string &name, int id) : Employee(name, id) {
}

// Adds the languages the flight attendant can speak.
void FlightAttendant::addLanguage(Country::Language language) {
	spokenLanguages.push_back(language);
}

// Checks the languages the flight attendant can speak.
bool FlightAttendant::canSpeak(Country::Language language) const {
	int numOfLanguage = spokenLanguages.size();	// Number of languages the flight attendant can speak.
	for(int i = 0;i<numOfLanguage;i++){
		if (spokenLanguages[i] == language){
			return true;
		}
	}
	return false;
}

// Destructor.
FlightAttendant::~FlightAttendant() {
}

