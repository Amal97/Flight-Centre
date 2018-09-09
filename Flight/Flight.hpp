#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include "Pilot.hpp"
#include "Route.hpp"
#include "FlightAttendant.hpp"
#include "Airplane.hpp"
#include "Date.hpp"

class Flight{
private:
	Route* route;
	Airplane* airplane;
	std::vector<Pilot*> allPilots;
	std::vector<FlightAttendant*> allFlightAttendants;
    Flight& operator=(const Flight& other);
    Flight(const Flight& other);

public:
    Flight(Route *route, Airplane* airplane);

    bool setFlightAttendants(vector<FlightAttendant*> flightAttendants);
    bool setPilots(vector<Pilot*> pilots);

    bool bookTicket(int quantity);
    int getAvailableSeats() const;
    Route* getRoute() const;
    Airplane* getAirplane() const;
    vector<Pilot *> getPilots() const;
    vector<FlightAttendant *> getFlightAttendants() const;

    ~Flight();
};

#endif
