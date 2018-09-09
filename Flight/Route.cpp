#include "Route.hpp"

// Initialize the source, destination and hours.
Route::Route(Country* source, Country* destination, int hours) : source(source), destination(destination), hours(hours) {
}

// Returns source.
Country* Route::getSource() const {
    return source;
}

// Returns destination.
Country* Route::getDestination() const {
    return destination;
}

// Returns hours.
int Route::getHours() const {
    return hours;
}

// Destructor.
Route::~Route() {
    delete source;
    delete destination;
}
