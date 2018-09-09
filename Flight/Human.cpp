#include "Human.hpp"

// Sets the name of the human
Human::Human(const std::string &name) {
	this->name = name;
}

// Returns the name of the human
std::string Human::getName() const {
    return this->name;
}

// Destructor
Human::~Human() {
}
