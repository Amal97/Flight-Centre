#include "Customer.hpp"

// Sets the name of the customer in the human class and sets the passport number and sets the
// loyalty points to 0
Customer::Customer(const std::string &name, const std::string &passportNumber) : Human(name) {
	this->passportNumber = passportNumber;
	loyaltyPoints = 0;
}

// Adds loyalty points.
void Customer::addLoyaltyPoints(int points) {
	if(points<0){		// If points is less than 0 then points is set to 0, we can't have negative points.
		points = 0;
	}
	loyaltyPoints = loyaltyPoints + points;
}

// Subtracts loyalty points
void Customer::decreaseLoyaltyPoints(int points) {
	if(points<0){		// If points is less than 0 then points is set to 0, we can't have negative points.
		points = 0;
	}
	loyaltyPoints = loyaltyPoints - points;
	if (loyaltyPoints<0){	// If loyalty points is less than 0 then it is set to 0 (0 is the min points)
		loyaltyPoints = 0;
	}
}

// Returns loyalty points
int Customer::getLoyaltyPoints() const {
	return loyaltyPoints;
}

// Returns passport number
std::string Customer::getPassportNumber() const {
    return this->passportNumber;
}

// Destructor.
Customer::~Customer(){
}
