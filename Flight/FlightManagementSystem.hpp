#ifndef FLIGHTMANAGEMENTSYSTEM_HPP
#define FLIGHTMANAGEMENTSYSTEM_HPP

#include <vector>
#include <string>

#include "Flight.hpp"
#include "Customer.hpp"

class FlightManagementSystem{
private:
	std::vector<Date*> times;
	std::vector<Customer *> customers;
    std::vector<Flight *> flights;
    std::vector<int> capacity;
    int customerPosition;
    bool customerExists(const std::string &passportNumber);

public:
    FlightManagementSystem();

    static std::string author();
    bool bookTicket(Route* route, Date *time, const std::string &passportNumber, int quantity);
    bool addCustomer(Customer *customer);

    int getCapacity(const Route* route, const Date* time) const;
    void addFlight(Flight* flight, Date* time);
    int getCustomerPoints(const std::string &passportNumber) const;

    std::vector<Flight *> getFlights() const;
    std::vector<Customer *> getCustomers() const;

    ~FlightManagementSystem();
};

#endif
