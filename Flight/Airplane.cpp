#include "Airplane.hpp"

// Sets the capacity of the airplane.
Airplane::Airplane(int capacity) {
	this->capacity = capacity;
}

// Returns the capacity of the airplane.
int Airplane::getCapacity() const {
	return capacity;
}

// Destructor.
Airplane::~Airplane(){
}