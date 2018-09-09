#include "FlightManagementSystem.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

FlightManagementSystem::FlightManagementSystem() {
	customerPosition = 0;
}

std::string FlightManagementSystem::author() {
    return "acha932";
}
// Checks if the customer exists or not.
bool FlightManagementSystem::customerExists(const std::string &passportNumber){
	bool customerExists = false;
	int numOfCustomer = customers.size();
	for (int i = 0; i < numOfCustomer;i++){
		string customerPassportNumber = customers[i]->getPassportNumber() ;
		if(customerPassportNumber == passportNumber){
			customerPosition = i;
			return true;
		}
	}
	return customerExists;
}

// Books the ticket of a customer if route, time and and passport number matches and the quantity is more than or equal to available seats.
bool FlightManagementSystem::bookTicket(Route* route, Date *time, const std::string &passportNumber, int quantity) {
	if (!customerExists(passportNumber)){
		return false;
	}

	Country* destination = route->getDestination();
	Country* source = route->getSource();

	// Checks if there is a flight and time which the user requested, if so ticket is booked and returned true. Capacity in the airplane decreases.
		for(unsigned int i=0;i<flights.size();i++){
			if ((flights[i]->getRoute()->getDestination() == destination) && (flights[i]->getRoute()->getSource() == source )  && (times[i]->getDay() == time->getDay()) &&(times[i]->getHour() == time->getHour()) ){
				if(capacity[i]>=quantity){
					capacity[i]= (capacity[i] - quantity);
					int customerPoints = quantity * flights[i]->getRoute()->getHours();
					customers[customerPosition]->addLoyaltyPoints(customerPoints);
					return true;
				}
				else{
					return false;
				}
			}
		}
		return false;
	}

// Adds customers, also checks whether a customer already exists or not. If customer exists then returns false. Otherwise customer is added and returned true.
bool FlightManagementSystem::addCustomer(Customer *customer) {
	int numOfCustomer = customers.size();
	for (int i = 0; i < numOfCustomer;i++){
		if(customers[i]->getPassportNumber() == customer->getPassportNumber()){
			return false;
		}
	}
	customers.push_back(customer);
	return true;
}

// Returns the capacity of a desired route and time.
int FlightManagementSystem::getCapacity(const Route* route, const Date* time) const {
	for(unsigned int i = 0; i<flights.size();i++){
		if((flights[i]->getRoute()==route) && (times[i]==time)){
			return capacity[i];
		}
	}
	return -1;
}

// Adds new flight and time.
void FlightManagementSystem::addFlight(Flight* flight, Date* time) {
	flights.push_back(flight);
	times.push_back(time);
	capacity.push_back(flight->getAvailableSeats());
}

// Returns customer's points.
int FlightManagementSystem::getCustomerPoints(const std::string &passportNumber) const {
	int numOfCustomer = customers.size();
	for(int i =0;i<numOfCustomer;i++){
		if(customers[i]->getPassportNumber() == passportNumber){
			return customers[i]->getLoyaltyPoints();
		}
	}
	return -1;
}

// Returns the flights vector.
std::vector<Flight *> FlightManagementSystem::getFlights() const {
	return flights;
}

// Returns the customers vector.
std::vector<Customer *> FlightManagementSystem::getCustomers() const {
	return customers;
}

// Destructor.
FlightManagementSystem::~FlightManagementSystem() {
	for(unsigned int i = 0; i<flights.size();i++){
		delete flights[i];
		flights[i] = 0;
	}
	for(unsigned int i = 0; i<times.size();i++){
		delete times[i];
		times[i] = 0;
	}
	for(unsigned int i = 0; i<customers.size();i++){
		delete customers[i];
		customers[i] = 0;
	}
}



