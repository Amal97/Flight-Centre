#include "Country.hpp"

// Sets the name and the language of a country.
Country::Country(const string &name, Language language) {
	this->name = name;
	this->language = language;
}

// Returns the language of the country.
Country::Language Country::getLanguage() const {
	return this->language;
}

// Returns the name of the country.
std::string Country::getName() const {
	return this->name;
}

// Destructor.
Country::~Country(){
}
