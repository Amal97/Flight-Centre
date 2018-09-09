#include <iostream>

#include "Flight.hpp"
#include "Route.hpp"
#include "Country.hpp"

// TODO implement the constructor, destructor and methods

// Sets the route and the airplane of a flight.
Flight::Flight(Route *route, Airplane* airplane) {
	this->route = route;
    this->airplane = airplane;
}

// Checks if the correct flight attendants are set to a flight.
bool Flight::setFlightAttendants(vector<FlightAttendant*> flightAttendants) {
	if (allFlightAttendants.size()==flightAttendants.size()){
		return false;
	}

    Country::Language source = route->getSource()->getLanguage();	// Language of the source country.
	Country::Language destination = route->getDestination()->getLanguage();	// Language of the destination country.

	int numFlightAttendants = flightAttendants.size();	// Number of flight attendants.

    if (route->getHours() < 8){	// Short flight.
    	if(numFlightAttendants!=3){	// Short flight needs 3 flight attendants.
    		return false;
    	}
// Checks the different combination to check if the flight attendants meets the requirements of the flight.
    	if (flightAttendants[0]->canSpeak(source) && flightAttendants[1]->canSpeak(destination) && flightAttendants[2]->canSpeak(Country::ENGLISH) ){
    		allFlightAttendants = flightAttendants;
    		return true;
			}
    	else if (flightAttendants[0]->canSpeak(source) && flightAttendants[2]->canSpeak(destination) && flightAttendants[1]->canSpeak(Country::ENGLISH) ){
    		allFlightAttendants = flightAttendants;
    		return true;
			}
    	else if (flightAttendants[1]->canSpeak(source) && flightAttendants[2]->canSpeak(destination) && flightAttendants[0]->canSpeak(Country::ENGLISH) ){
    		allFlightAttendants = flightAttendants;
    		return true;
			}
    	else if (flightAttendants[1]->canSpeak(source) && flightAttendants[0]->canSpeak(destination) && flightAttendants[2]->canSpeak(Country::ENGLISH) ){
    		allFlightAttendants = flightAttendants;
    		return true;
			}
    	else if (flightAttendants[2]->canSpeak(source) && flightAttendants[0]->canSpeak(destination) && flightAttendants[1]->canSpeak(Country::ENGLISH) ){
    		allFlightAttendants = flightAttendants;
    		return true;
			}
    	else if (flightAttendants[2]->canSpeak(source) && flightAttendants[1]->canSpeak(destination) && flightAttendants[0]->canSpeak(Country::ENGLISH) ){
    		allFlightAttendants = flightAttendants;
    		return true;
			}
    	else{
    		return false;
    	}
    }
    else if (route->getHours() >= 8){	// Long flight.
    	if(numFlightAttendants!=6){	// Long flight needs 6 flight attendants.
    		return false;
    	}

    	bool canSpeakEnglish = false;
		bool canSpeakSourceLanguage = false;
		bool canSpeakDestinationLanguage = false;

		int twoEnglishSpeaker = 0;	// Variable to check if there 2 flight attendants who can speak English.
		int twoDestinationSpeaker = 0;	// Variable to check if there 2 flight attendants who can speak the destination country language.
		int twoSourceSpeaker = 0;	// Variable to check if there 2 flight attendants who can speak the cource country language.

    	for (int i=0;i<numFlightAttendants;i++){
      		 if (flightAttendants[i]->canSpeak(Country::ENGLISH)){	// Checks if the flight attendant can speak English or not.
      			 twoEnglishSpeaker++;
      			 if (twoEnglishSpeaker>=2){
      				 canSpeakEnglish = true;
      			 }
      		 }
      		 if (flightAttendants[i]->canSpeak(destination)){	// Checks if the flight attendant can speak destination country language or not.
      			 twoDestinationSpeaker++;
      			 if (twoDestinationSpeaker>=2){
      				 canSpeakDestinationLanguage = true;
      			 }
      		 }
      		 if (flightAttendants[i]->canSpeak(source)){	// Checks if the flight attendant can speak source country language or not.
      			 twoSourceSpeaker++;
      			 if (twoSourceSpeaker>=2){
      				 canSpeakSourceLanguage = true;
      			 }
      		 }
    	}
    	//	Checks if there are at least 2 flight attendants in the flight that can speak English,
    	//	Source country language and destination country language.
    	if (canSpeakEnglish && canSpeakSourceLanguage && canSpeakDestinationLanguage){
    		allFlightAttendants = flightAttendants;
    		return true;
    	}
    	return false;
    }
    return false;
}

// Checks if there are correct number of Captain and Co_pilots in a flight.
bool Flight::setPilots(vector<Pilot*> pilots) {
	if (allPilots.size()==pilots.size()){
		return false;
	}

	int numPilots = pilots.size();
	bool isCaptain = false;
    bool isCo_Pilot = false;

	if (route->getHours()<8){	// Short flight.
		if(numPilots!=2){	// Short flight requires 2 pilots
			return false;
		}
        for (int i=0;i<numPilots;i++){
        	if(pilots[i]->getLevel() == Pilot::CAPTAIN){	// Checks if the pilot is Captain or not.
        		isCaptain = true;
    		}
        	else if(pilots[i]->getLevel() == Pilot::CO_PILOT){	// Checks if the pilot is Co_Pilot or not.
    			isCo_Pilot = true;
    		}
        }
        if (isCaptain && isCo_Pilot){	//	Checks if there is 1 Captain and 1 Co_pilot.
        		allPilots = pilots;
    			return true;
        	}
	}

	if(route->getHours()>=8){	// Long flight.
		if(numPilots!=4){	// Long flight requires 4 pilots.
			return false;
		}

        int twoCaptain = 0;
        int twoCo_Pilot = 0;

        for(int i = 0;i<numPilots;i++){
        	if(pilots[i]->getLevel() == Pilot::CAPTAIN){	// Checks if the pilot is Captain or not.
        		twoCaptain++;
        		if(twoCaptain==2){	// Long flight needs 2 Captain.
        			isCaptain = true;
        		}
        	}
        	else if(pilots[i]->getLevel() == Pilot::CO_PILOT){	// Checks if the pilot is Co_Pilot or not.
        		twoCo_Pilot++;
    			if(twoCo_Pilot==2){	// Long flight needs 2 Co_Pilot.
    				isCo_Pilot = true;
    			}
            }
        }
        if (isCaptain && isCo_Pilot){	//	Checks if there is 2 Captain and 2 Co_pilot.
        	allPilots = pilots;
        	return true;
        }
        return false;
	}
	return false;
}

//	Checks if there are seats available in the airplane or not, 
//	and if there is seats available then returns true else returns false.
bool Flight::bookTicket(int quantity) {
	if(getAvailableSeats()>=quantity){
		return true;
	}
	else{
		return false;
	}
}

// Returns the number of seats that is available.
int Flight::getAvailableSeats() const {
	if (route->getHours()<8){
		return airplane->getCapacity() - 3;	// Subtracts 3 from Airplane capacity because of 3 flight attendants.
	}
	else{
		return airplane->getCapacity() - 8;	// Subtracts 8 from Airplane capacity because of 6 flight attendants and 2 extra pilots.
	}
}

// Returns route
Route* Flight::getRoute() const {
	return this->route;
}

// Returns the airplane.
Airplane* Flight::getAirplane() const {
	return this->airplane;
}

// Returns the FlightAttendant vector.
std::vector<FlightAttendant *> Flight::getFlightAttendants() const{
	return allFlightAttendants;
}

// Returns the Pilot vector.
std::vector<Pilot *> Flight::getPilots() const{
	return allPilots;
}

// Destructor.
Flight::~Flight(){
}


