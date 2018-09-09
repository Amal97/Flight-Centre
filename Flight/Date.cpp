#include "Date.hpp"

// Sets the day and hour of the flight.
Date::Date(int day, int hour) {
	if(day<0){
		day = 0;
	}
	if (hour<0){
		hour = 0;
	}
	if (hour>23){
		this->day = day + (hour/24);
		this->hour = (hour%24);
	}
	else{
		this->day = day;
		this->hour = hour;
	}
}

// Returns the hour of the flight.
int Date::getHour() const {
    return hour;
}

// Returns the day of the flight.
int Date::getDay() const {
    return day;
}

// Change the day and hour of the flight.
void Date::changeDateTo(int day, int hour) {
	if ((day>0)&&(hour>0)){
		if (hour>23){
			this->day = this->day+ day + (hour/24);
			this->hour = (hour%24)+this->hour;
		}
		else{
			this->day = day;
			this->hour = hour;
		}
	}
}

// Adds time, converts hours into days.
void Date::addTime(int count) {
	if (count<0){
		count = 0;
	}
	else if (count>23){
		day = (count/24)+day;
		hour = (count%24) + this->hour;
	}
	else{
		hour = hour + count;
		if(hour>23){
			day = (hour/24) + day;
			hour = (hour%24);
		}
	}
}

// Checks if the date is less than the provided date.
bool Date::isLessThan(const Date &other) const {
	if (this->day < other.day){
		return true;
	}
	else if (this->day == other.day){
		if (this->hour < other.hour){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

// Destructor.
Date::~Date(){
}
