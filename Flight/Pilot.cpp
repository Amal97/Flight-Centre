#include "Pilot.hpp"

// Sets the name of the pilot in human class and id in the employee and sets the level of the pilot
 Pilot::Pilot(const std::string &name, int ID) :  Employee(name, ID) {
	 setLevel = CO_PILOT;
 }

 // Returns the level of the pilot
 Pilot::Level Pilot::getLevel() const {
	 return this->setLevel;
 }

 // Promotes the pilot from co_pilot to captain
 bool Pilot::promote() {
	 if(setLevel==CO_PILOT){
		 setLevel = CAPTAIN;
		 return true;
	 }
	 else{
		 return false;
	 }
 }

 // Demotes the pilot from captain to co_pilot
 bool Pilot::demote() {
	 if(setLevel==CAPTAIN){
		 setLevel = CO_PILOT;
		 return true;
	 }
	 else{
		 return false;
	 }
 }

 // Destructor.
 Pilot::~Pilot() {
 }

