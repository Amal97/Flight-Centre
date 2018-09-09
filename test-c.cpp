#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

// flags to enable tests for the later parts of the assignment
#define ENABLE_T2_TESTS
#define ENABLE_T3_TESTS
#define ENABLE_T4_TESTS

// include headers for classes being tested
#include "Flight/FlightManagementSystem.hpp"
#include "Flight/Country.hpp"
#include "Flight/Airplane.hpp"
#include "Flight/Date.hpp"

#ifdef ENABLE_T2_TESTS
#include "Flight/Customer.hpp"
#include "Flight/Pilot.hpp"
#include "Flight/FlightAttendant.hpp"

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
#include "Flight/Flight.hpp"
#include "Flight/Route.hpp"

#endif /*ENABLE_T3_TESTS*/

using namespace std;

enum TestResult { TR_PASS, TR_FAIL };

#define ASSERT(condition)                                                         \
    if ((condition) == false) {                                                   \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpression '" << #condition << "' evaluated to false" << endl; \
        return TR_FAIL;                                                           \
    }

/*
 This checks that you are returning your UoA username (formally known as UPI)
 */
TestResult testUPI() {
    string upi = FlightManagementSystem::author();

    // UPIs should be at least 4 characters long
    ASSERT(upi.size() >= 4);
    // First character should be alphabetic
    ASSERT(isalpha(upi[0]));
    // Last 3 characters should be numeric
    ASSERT(isdigit(upi[upi.size() - 1]));
    ASSERT(isdigit(upi[upi.size() - 2]));
    ASSERT(isdigit(upi[upi.size() - 3]));

    // If nothing went wrong, the test passed
    return TR_PASS;
}

/*
 * Test creating an instance of the Country class creates it with the correct name and language,
 * and that the getName() and getLanguage() methods work properly.
 * */
TestResult testCountry() {
    Country newZealand("New Zealand", Country::ENGLISH);
    ASSERT(newZealand.getLanguage() == Country::ENGLISH);
    ASSERT(newZealand.getName() == "New Zealand");

    return TR_PASS;
}

/*
 * Test creating an instance of the Airplane class creates it with the correct capacity.
 * */
TestResult testAirplane(){
    Airplane airplane(300);
    ASSERT(airplane.getCapacity() == 300);

    return TR_PASS;
}

/*
 * Test creating an instance of the Date class creates it with the correct day and hour, and that the
 * getDay() and getHour() methods work properly.
 * */
TestResult testTime1() {
    Date time(1, 4);
    ASSERT(time.getDay() == 1);
    ASSERT(time.getHour() == 4);

    return TR_PASS;
}

/*
 * Check the addTime function works for Date
 * */
TestResult testTime2() {
    Date time(1, 4);
    time.addTime(5);
    ASSERT(time.getDay() == 1);
    ASSERT(time.getHour() == 9);

    time.addTime(24);
    ASSERT(time.getDay() == 2);
    ASSERT(time.getHour() == 9);

    time.addTime(18);
    ASSERT(time.getDay() == 3);
    ASSERT(time.getHour() == 3);

    return TR_PASS;
}

/*
 * Now check that isLessthan, addTime and changeTime methods all work.
 * */
TestResult testTime3() {
    Date time(1, 4);

    time.addTime(24);
    ASSERT(time.getDay() == 2);
    ASSERT(time.getHour() == 4);

    Date nextTime(10, 4);
    ASSERT(time.isLessThan(nextTime));

    time.changeDateTo(3, 4);
    ASSERT(time.getDay() == 3);
    ASSERT(time.getHour() == 4);

    //If inputs are negative, do nothing
    time.changeDateTo(-5, 3);
    ASSERT(time.getDay() == 3);
	ASSERT(time.getHour() == 4);

    time.changeDateTo(6, -2);
    ASSERT(time.getDay() == 3);
	ASSERT(time.getHour() == 4);

    time.changeDateTo(-4, -8);
    ASSERT(time.getDay() == 3);
	ASSERT(time.getHour() == 4);
    return TR_PASS;
}

TestResult testMoreStuff() {
	//assuming all invalid inputs make values = 1 or 0
//	Date timeInvalid1(4, 65);
//	ASSERT(timeInvalid1.getDay() == 4);
//	ASSERT(timeInvalid1.getHour() == 0);

//	Date timeInvalid2(-5, 23);
//	ASSERT(timeInvalid2.getDay() == 1);
//	ASSERT(timeInvalid2.getHour() == 23);
//
//	Date timeInvalid3(-5, -23);
//	ASSERT(timeInvalid3.getDay() == 1);
//	ASSERT(timeInvalid3.getHour() == 0);

	Date time(4, 20);
	ASSERT(time.getDay() == 4);
	ASSERT(time.getHour() == 20);

	time.addTime(24);
	ASSERT(time.getDay() == 5);
	ASSERT(time.getHour() == 20);

	time.addTime(1);
	ASSERT(time.getDay() == 5);
	ASSERT(time.getHour() == 21);

	time.addTime(-6);
	ASSERT(time.getDay() == 5);
	ASSERT(time.getHour() == 21);

	Date nextTime(10, 4);
	ASSERT(time.isLessThan(nextTime));
	ASSERT(!nextTime.isLessThan(time));

	Date smolTime(10, 3);
	ASSERT(smolTime.isLessThan(nextTime));
	ASSERT(!nextTime.isLessThan(smolTime));

	time.changeDateTo(3, 4);
	ASSERT(time.getDay() == 3);
	ASSERT(time.getHour() == 4);

	time.changeDateTo(-5, 2);
	ASSERT(time.getDay() == 3);
	ASSERT(time.getHour() == 4);

	return TR_PASS;
}





#ifdef ENABLE_T2_TESTS

/* Test the behavior of the Customer class */
TestResult testCustomer() {

    Customer *ben = new Customer("Ben", "PW2342");
    ASSERT(ben->getPassportNumber() == "PW2342");
    ASSERT(ben->getLoyaltyPoints() == 0);
    ben->addLoyaltyPoints(340);
    ASSERT(ben->getLoyaltyPoints() == 340);
    ben->decreaseLoyaltyPoints(34);
    ASSERT(ben->getLoyaltyPoints() == 306);
    ben->decreaseLoyaltyPoints(306);
    ASSERT(ben->getLoyaltyPoints() == 0);
    ben->decreaseLoyaltyPoints(69);
    ASSERT(ben->getLoyaltyPoints() == 0);
    ben->addLoyaltyPoints(420);
    ASSERT(ben->getLoyaltyPoints() == 420);

    Human *benHuman = ben;
    ASSERT(benHuman->getName() == "Ben");

    delete ben;
    return TR_PASS;
}

/* Test the behavior of the FlightAttendant class */
TestResult testFlightAttendant() {

    FlightAttendant *sara = new FlightAttendant("Sara", 123);
    ASSERT(sara->getName() == "Sara");
    ASSERT(sara->getID() == 123);
    sara->addLanguage(Country::ENGLISH);
    sara->addLanguage(Country::SPANISH);
    sara->addLanguage(Country::CHINESE);

    ASSERT( sara->canSpeak(Country::CHINESE) );
    ASSERT( sara->canSpeak(Country::ENGLISH) );
    ASSERT( sara->canSpeak(Country::SPANISH) );
    ASSERT( ! sara->canSpeak(Country::ARABIC) );
    ASSERT( ! sara->canSpeak(Country::HINDI) );

    Human *saraHuman = sara;
    ASSERT(saraHuman->getName() == "Sara");

    Employee *saraEmployee = sara;
    ASSERT(saraEmployee->getName() == "Sara");
    ASSERT(saraEmployee->getID() == 123);

    delete sara;
    return TR_PASS;
}

/* Test the behavior ofthe Pilot class */
TestResult testPilot() {

    Pilot *jenny = new Pilot("Jenny", 456);
    ASSERT(jenny->getName() == "Jenny");
    ASSERT(jenny->getID() == 456);
    ASSERT(jenny->getLevel() == Pilot::CO_PILOT);

    ASSERT(jenny->promote());
    ASSERT(jenny->getLevel() == Pilot::CAPTAIN);
    ASSERT(!jenny->promote());
    ASSERT(jenny->getLevel() == Pilot::CAPTAIN);

    ASSERT(jenny->demote());
    ASSERT(jenny->getLevel() == Pilot::CO_PILOT);
    ASSERT(!jenny->demote());
    ASSERT(jenny->getLevel() == Pilot::CO_PILOT);

    Human *jennyHuman = jenny;
    ASSERT(jennyHuman->getName() == "Jenny");

    Employee *jennyEmployee = jenny;
    ASSERT(jennyEmployee->getName() == "Jenny");
    ASSERT(jennyEmployee->getID() == 456);

    delete jenny;
    return TR_PASS;
}

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS

/*
 * Checking the Route class
 */
TestResult testRoute() {
    Country *source = new Country("Auckland", Country::ENGLISH);
    Country *destination = new Country("Shanghai", Country::CHINESE);

    Route path(source, destination, 12);
    ASSERT(path.getSource()->getName() == "Auckland");
    ASSERT(path.getDestination()->getName() == "Shanghai");
    ASSERT(path.getHours() == 12);

    return TR_PASS;
}

/*
 * Check the Flight class
 */
TestResult testFlightConstructor() {
    Country *source = new Country("Auckland", Country::ENGLISH);
    Country *destination = new Country("Shanghai", Country::CHINESE);
    Route *path = new Route(source, destination, 12);
    Airplane *airplane = new Airplane(300);

    Flight flight(path, airplane);
    ASSERT(flight.getAirplane() == airplane);
    ASSERT(flight.getRoute() == path);

    // 6 seats required for flight attendants, & 2 seats for spare captain/pilot
    ASSERT(flight.getAvailableSeats() == 292);

    return TR_PASS;
}

/*
 * Check correctly adding pilots to a Flight
 */
TestResult testFlightAddPilots() {
    Country *source = new Country("London", Country::ENGLISH);
    Country *destination = new Country("Madrid", Country::SPANISH);

    Route *path = new Route(source, destination, 3);
    Airplane *airplane = new Airplane(300);
    Flight flight(path, airplane);

    //Pilots
    vector<Pilot*> pilots;
    vector<Pilot*> anotherOne;
    Pilot *jack 	= new Pilot("Jack",123);
    Pilot *jenny 	= new Pilot("Jenny",10);
    Pilot *namu 	= new Pilot("Namu",3);
    Pilot *tae 		= new Pilot("Tae",8);
    pilots.push_back(jack);
    pilots.push_back(jenny);
    anotherOne.push_back(namu);
    anotherOne.push_back(tae);
    ASSERT(!flight.setPilots(pilots));

    jenny->promote();
    ASSERT(flight.setPilots(pilots));

    //Shouldn't be able to reassign pilots
    namu->promote();
    ASSERT(!flight.setPilots(anotherOne));

    //300 - 3 = 297 since short flight
    ASSERT(flight.getAvailableSeats() == 297);

    return TR_PASS;
}

/*
 * Check correctly adding flight attendants to the flight
 */
TestResult testFlightAddFlightAttendants() {

	//------------------------------------------IMPROVED ON THIS

	Country *source = new Country("Cairo", Country::ARABIC);
	Country *destination = new Country("Madrid", Country::SPANISH);

	Route *path = new Route(source, destination, 4);
    Airplane *airplane = new Airplane(300);
    Flight flight(path, airplane);

    vector<FlightAttendant*> flightAttendants1;
	FlightAttendant *bobby = new FlightAttendant("Bobby", 76);
	bobby->addLanguage(Country::SPANISH);
	flightAttendants1.push_back(bobby);
	ASSERT(!flight.setFlightAttendants(flightAttendants1));

	FlightAttendant *jack  = new FlightAttendant("Jack", 37);
	jack->addLanguage(Country::SPANISH);
	flightAttendants1.push_back(jack);
	ASSERT(!flight.setFlightAttendants(flightAttendants1));

	FlightAttendant *sarah = new FlightAttendant("Sarah", 98);
	sarah->addLanguage(Country::ENGLISH);
	sarah->addLanguage(Country::ARABIC);
	flightAttendants1.push_back(sarah);

	ASSERT(!flight.setFlightAttendants(flightAttendants1)); //should still fail

	//------------------------------------------ORIGINAL

    vector<FlightAttendant*> flightAttendants;
    FlightAttendant *bob = new FlightAttendant("Bob", 23);
    bob->addLanguage(Country::SPANISH);
    flightAttendants.push_back(bob);
    ASSERT(!flight.setFlightAttendants(flightAttendants));

    FlightAttendant *jacky  = new FlightAttendant("Jacky", 34);
    jacky->addLanguage(Country::ARABIC);
    flightAttendants.push_back(jacky);
    ASSERT(!flight.setFlightAttendants(flightAttendants));

    FlightAttendant *sara = new FlightAttendant("Sara", 19);
    sara->addLanguage(Country::ENGLISH);
    flightAttendants.push_back(sara);
    ASSERT(flight.setFlightAttendants(flightAttendants));

    //------------------------------------------ORIGINAL


    vector<FlightAttendant*> flightAttendants2;
	FlightAttendant *mele = new FlightAttendant("Mele", 171);
	bob->addLanguage(Country::ENGLISH);
	flightAttendants2.push_back(mele);

	FlightAttendant *samisoni  = new FlightAttendant("Samisoni", 282);
	jacky->addLanguage(Country::SPANISH);
	flightAttendants2.push_back(samisoni);

	FlightAttendant *andrew = new FlightAttendant("Andrew", 474);
	sara->addLanguage(Country::ARABIC);
	flightAttendants2.push_back(andrew);

	//Cannot set new crew
	ASSERT(!flight.setFlightAttendants(flightAttendants2));


    return TR_PASS;
}
//ADDED TEST CASES
TestResult moreAddPilotAndEmployees() {
	//------------------------------------------ TESTING: Pilot
	Country *source 		= new Country("Clendon", Country::HINDI);
	Country *destination 	= new Country("Homai", Country::CHINESE);

	Route *path 			= new Route(source, destination, 15);
	Airplane *airplane 		= new Airplane(350);
	Flight flight(path, airplane);

	//Should reserve 8 seats for crew
	ASSERT(flight.getAvailableSeats() == 342);

	//------------------------------------------
	//Adding first set of pilots
    vector<Pilot*> pilots;
    Pilot *lee 		= new Pilot("Lee",420);
    Pilot *shannell = new Pilot("Shannell",262);
    Pilot *siosifa 	= new Pilot("Siosifa",987);
    Pilot *luke 	= new Pilot("Luke",15);

    pilots.push_back(lee);
    pilots.push_back(shannell);
    pilots.push_back(siosifa);
	pilots.push_back(luke);

    ASSERT(!flight.setPilots(pilots));
    lee->promote();
    ASSERT(!flight.setPilots(pilots));
    shannell->promote();

    //Should have two captains two co_pilots here
    ASSERT(flight.setPilots(pilots));

    vector<Pilot*> secondPilots;

    secondPilots.push_back(siosifa);
    secondPilots.push_back(lee);
    secondPilots.push_back(luke);
    secondPilots.push_back(shannell);

    //Can't reassign pilots
    ASSERT(!flight.setPilots(secondPilots));

    //Should return the first pilots
    ASSERT(flight.getPilots() == pilots);

    //------------------------------------------ TESTING: Flight Attendants

    vector<FlightAttendant*> flightAttendants1;
    vector<FlightAttendant*> flightAttendants2;

	FlightAttendant *ant 	= new FlightAttendant("Ant", 31);
	FlightAttendant *david 	= new FlightAttendant("David", 724);
	FlightAttendant *Amy  	= new FlightAttendant("Amy", 133);
	FlightAttendant *marq 	= new FlightAttendant("Marq", 69);
	FlightAttendant *mana 	= new FlightAttendant("Mana", 459);
	FlightAttendant *tony 	= new FlightAttendant("Tony", 420);

	ant->addLanguage(Country::ENGLISH);
	flightAttendants1.push_back(ant);
	david->addLanguage(Country::HINDI);
	flightAttendants1.push_back(david);
	Amy->addLanguage(Country::CHINESE);
	flightAttendants1.push_back(Amy);

	//Don't have enough crew members for this long flight
	ASSERT(!flight.setFlightAttendants(flightAttendants1));

	marq->addLanguage(Country::SPANISH);
	flightAttendants1.push_back(marq);
	mana->addLanguage(Country::ENGLISH);
	flightAttendants1.push_back(mana);
	tony->addLanguage(Country::ARABIC);
	flightAttendants1.push_back(tony);

	//Don't have enough source/destination language speakers
	ASSERT(!flight.setFlightAttendants(flightAttendants1));

	david->addLanguage(Country::CHINESE);
	tony->addLanguage(Country::HINDI);
	//tony->addLanguage(Country::CHINESE);

	//Crew meets requirements now. Checking if we can set the team
	ASSERT(flight.setFlightAttendants(flightAttendants1));

	flightAttendants2.push_back(mana);
	flightAttendants2.push_back(tony);
	flightAttendants2.push_back(ant);
	flightAttendants2.push_back(Amy);
	flightAttendants2.push_back(david);
	flightAttendants2.push_back(marq);

	//Can't reassign the team
	ASSERT(!flight.setFlightAttendants(flightAttendants2));

	//should return the first team
	ASSERT(flight.getFlightAttendants() == flightAttendants1);

	return TR_PASS;
}

TestResult manasTests() {

	// Test setting flight attendants for long flight
	Country *source2 = new Country("Beijing", Country::CHINESE);
	Country *destination2 = new Country("Barcelona", Country::SPANISH);

	Route *path2 = new Route(source2, destination2, 8);
	Airplane *airplane2 = new Airplane(500);
	Flight flight2(path2, airplane2);

	vector<FlightAttendant*> flightAttendants2;
	FlightAttendant *dylan = new FlightAttendant("Dylan", 45);
	dylan->addLanguage(Country::ENGLISH);
	dylan->addLanguage(Country::CHINESE);
	flightAttendants2.push_back(dylan);

	FlightAttendant *paul = new FlightAttendant("Paul", 99);
	paul->addLanguage(Country::SPANISH);
	flightAttendants2.push_back(paul);

	FlightAttendant *dave = new FlightAttendant("Dave", 22);
	dave->addLanguage(Country::CHINESE);
	flightAttendants2.push_back(dave);

	FlightAttendant *frank = new FlightAttendant("Frank", 47);
	frank->addLanguage(Country::SPANISH);
	flightAttendants2.push_back(frank);

	FlightAttendant *john = new FlightAttendant("John", 36);
	john->addLanguage(Country::CHINESE);
	flightAttendants2.push_back(john);

	FlightAttendant *bree = new FlightAttendant("Bree", 84);
	bree->addLanguage(Country::SPANISH);
	flightAttendants2.push_back(bree);

	// This test should fail as only one flight attendant speaks English,
	// therefore no team should be set
	ASSERT(!(flight2.setFlightAttendants(flightAttendants2)));
	ASSERT(flight2.getFlightAttendants().size() == 0);

	// Now at least two flight attendants speak English, so test should pass
	bree->addLanguage(Country::ENGLISH);
	ASSERT(flight2.setFlightAttendants(flightAttendants2));
	ASSERT(flight2.getFlightAttendants().size() == 6);
	ASSERT(flight2.getAvailableSeats() == 492);

	// Check if a new team can be set, needs to fail
	vector<FlightAttendant*> flightAttendants3;
	FlightAttendant *steve 	= new FlightAttendant("Steve", 1);
	FlightAttendant *tony 	= new FlightAttendant("Tony", 2);
	FlightAttendant *thor 	= new FlightAttendant("Thor", 3);
	FlightAttendant *bruce 	= new FlightAttendant("Bruce", 4);
	FlightAttendant *natasha = new FlightAttendant("Natasha", 5);
	FlightAttendant *clint 	= new FlightAttendant("Clint", 6);
	flightAttendants3.push_back(steve);
	flightAttendants3.push_back(tony);
	flightAttendants3.push_back(thor);
	flightAttendants3.push_back(bruce);
	flightAttendants3.push_back(natasha);
	flightAttendants3.push_back(clint);

	//Can't reassign the crew
	ASSERT(!flight2.setFlightAttendants(flightAttendants3));

	steve->addLanguage(Country::ENGLISH);
	steve->addLanguage(Country::SPANISH);
	steve->addLanguage(Country::CHINESE);
	tony->addLanguage(Country::SPANISH);
	tony->addLanguage(Country::CHINESE);
	tony->addLanguage(Country::ENGLISH);

	//Still cannot reassign the crew even if they speak the right languages
	ASSERT(!flight2.setFlightAttendants(flightAttendants3));

	return TR_PASS;
}

TestResult manasTest2() {

    //Test setting pilots for long flight
    Country *source1 = new Country("Beijing", Country::CHINESE);
    Country *destination1 = new Country("Barcelona", Country::SPANISH);

    Route *path1 = new Route(source1, destination1, 10);
    Airplane *airplane1 = new Airplane(300);
    Flight flight1(path1, airplane1);

    //Pilots
    vector<Pilot*> pilots1;
    Pilot *lloyd = new Pilot("Lloyd",48);
    Pilot *cole = new Pilot("Cole",96);
    Pilot *jay = new Pilot("Jay",42);
    Pilot *zane = new Pilot("Zane",21);
    pilots1.push_back(lloyd);
    pilots1.push_back(cole);
    pilots1.push_back(jay);
    pilots1.push_back(zane);
    ASSERT(!flight1.setPilots(pilots1));

    cole->promote();
    ASSERT(!flight1.setPilots(pilots1));

    zane->promote();
    ASSERT(flight1.setPilots(pilots1));

    ASSERT(flight1.getAvailableSeats() == 292);

    // Check if a new team can be set, needs to fail this
    vector<Pilot*> pilots2;
    Pilot *jason = new Pilot("Jason",876);
    Pilot *billy = new Pilot("Billy",654);
    Pilot *zack = new Pilot("Zack",844);
    Pilot *tommy = new Pilot("Tommy",687);
    pilots2.push_back(jason);
    pilots2.push_back(billy);
    pilots2.push_back(zack);
    pilots2.push_back(tommy);

    jason->promote();
    billy->promote();
    ASSERT(!flight1.setPilots(pilots2));

    return TR_PASS;
}


#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS

/*
 * Check adding customers to the Flight Management System
 */
TestResult testAddCustomer() {
    FlightManagementSystem fms;

    Customer *ben = new Customer("Ben", "K43681");
    vector<Customer *> customers = fms.getCustomers();
    ASSERT(customers.size() == 0)

    ASSERT(fms.addCustomer(ben));
    customers = fms.getCustomers();
    ASSERT(customers.size() == 1)

    Customer *luke = new Customer("Luke", "M20231");
    ASSERT(fms.addCustomer(luke));
    customers = fms.getCustomers();
    ASSERT(customers.size() == 2)

    // Customer with a different name, but same passport number -- shouldn't be added
    Customer *ben2 = new Customer("Not Ben Again", "K43681");
    ASSERT(!fms.addCustomer(ben2));

    return TR_PASS;
}

/*
 * Check adding flight to the FMS
 */
TestResult testAddFlight() {
    FlightManagementSystem fms;

    Country *source = new Country("Miami", Country::ENGLISH);
    Country *destination = new Country("Lima", Country::SPANISH);
    Route *path = new Route(source, destination, 7);
    Airplane *airplane = new Airplane(300);
    Flight *flight = new Flight(path, airplane);

    Date *time = new Date(3, 2);
    fms.addFlight(flight, time);

    vector <Flight *> flights;
    flights = fms.getFlights();

    ASSERT(flights.size() == 1);

    return TR_PASS;
}

/*
 * Check booking of tickets
 */
TestResult testBookTicket() {
    FlightManagementSystem fms;

    Country *miami = new Country("Miami", Country::ENGLISH);
    Country *lima = new Country("Lima", Country::SPANISH);
    Route *pathMtoL = new Route(miami, lima, 7);
    Airplane *airplaneMtoL = new Airplane(300);
    Flight *flightMtoL  = new Flight(pathMtoL, airplaneMtoL);
    Date *timeMtoL = new Date(3, 2);
    fms.addFlight(flightMtoL, timeMtoL);

    Country *dubai = new Country("Dubai", Country::ARABIC);
    Country *auckland = new Country("Auckland", Country::ENGLISH);
    Route *pathDtoA = new Route(dubai, auckland, 15);
    Airplane *airplaneDtoA = new Airplane(500);
    Flight *flightToDtoA = new Flight(pathDtoA, airplaneDtoA);
    Date *timeDtoA = new Date(3, 2);
    fms.addFlight(flightToDtoA, timeDtoA);

    Customer *ben = new Customer("Ben", "ABC436");
    fms.addCustomer(ben);
    Customer *lucy = new Customer("Lucy", "PW23091");
    fms.addCustomer(lucy);

    ASSERT(fms.bookTicket(pathDtoA, timeDtoA, "ABC436", 20));
    ASSERT(fms.getCapacity(pathDtoA, timeDtoA) == 472);
    ASSERT(fms.getCustomerPoints("ABC436") == 300);

    return TR_PASS;
}

// TODO keep private and split.. write others like this
TestResult testBookTicketFull() {
    FlightManagementSystem fms;

    Country *miami = new Country("Miami", Country::ENGLISH);
    Country *lima = new Country("Lima", Country::SPANISH);
    Route *pathMtoL = new Route(miami, lima, 7);
    Airplane *airplaneMtoL = new Airplane(50);
    Flight *flightMtoL  = new Flight(pathMtoL, airplaneMtoL);
    Date *timeMtoL = new Date(3, 2);
    fms.addFlight(flightMtoL, timeMtoL);

    Country *miami2 = new Country("Miami", Country::ENGLISH);
	Country *lima2 = new Country("Lima", Country::SPANISH);
	Route *pathMtoL2 = new Route(miami2, lima2, 7);
	Airplane *airplaneMtoL2 = new Airplane(100);
	Flight *flightMtoL2 = new Flight(pathMtoL2, airplaneMtoL2);
	Date *timeMtoL2 = new Date(5, 2);
	fms.addFlight(flightMtoL2, timeMtoL2);

    Customer *ben = new Customer("Ben", "ABC436");
    fms.addCustomer(ben);
    Customer *lucy = new Customer("Lucy", "PW23091");
    fms.addCustomer(lucy);

    ASSERT(fms.bookTicket(pathMtoL, timeMtoL, "ABC436", 40));
    ASSERT(fms.getCapacity(pathMtoL, timeMtoL) == 7);

    ASSERT(fms.getCapacity(pathMtoL2, timeMtoL2) == 97);

    ASSERT(!fms.bookTicket(pathMtoL, timeMtoL, "PW23091", 10));
    ASSERT(fms.bookTicket(pathMtoL, timeMtoL, "PW23091", 7));
    ASSERT(fms.getCapacity(pathMtoL, timeMtoL) == 0);

    ASSERT(!fms.bookTicket(pathMtoL, timeMtoL, "PW23091", 1));

    // book on another date
    ASSERT(fms.bookTicket(pathMtoL2, timeMtoL2, "PW23091", 10));
    ASSERT(fms.getCapacity(pathMtoL2, timeMtoL2) == 87);

    return TR_PASS;
}


#endif /*ENABLE_T4_TESTS*/

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/

vector<TestResult (*)()> generateTests() {
    vector<TestResult (*)()> tests;

    tests.push_back(&testUPI);

    tests.push_back(&testCountry);
    tests.push_back(&testTime1);
    tests.push_back(&testTime2);
    tests.push_back(&testTime3);
    tests.push_back(&testAirplane);
    tests.push_back(&testMoreStuff);

#ifdef ENABLE_T2_TESTS
    tests.push_back(&testCustomer);
    tests.push_back(&testFlightAttendant);
    tests.push_back(&testPilot);
#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
    tests.push_back(&testRoute);
    tests.push_back(&testFlightConstructor);
    tests.push_back(&testFlightAddPilots);
    tests.push_back(&testFlightAddFlightAttendants);
    tests.push_back(&moreAddPilotAndEmployees);
    tests.push_back(&manasTests);
    tests.push_back(&manasTest2);
#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS
    tests.push_back(&testAddCustomer);
    tests.push_back(&testAddFlight);
    tests.push_back(&testBookTicket);

    // TODO Remove
    // TODO Remove
    // TODO Remove
    tests.push_back(&testBookTicketFull);
#endif /*ENABLE_T4_TESTS*/

    return tests;
}

int main(int argc, char const* argv[]) {
    // If one or more test numbers are passed as command-line parameters, execute them
    vector<TestResult (*)()> tests_to_run = generateTests();
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    unsigned int run_count = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            unsigned int test_num = atoi(argv[i]);
            if (test_num > tests_to_run.size()) {
                cout << "ERROR: unknown test case " << test_num << endl;
                continue;
            }
            // run the test
            ++run_count;
            TestResult result = tests_to_run[test_num]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << test_num << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << test_num << " passed." << endl;
                ++pass_count;
            }
        }
    } else {
        // otherwise, run all tests
        // Make sure to update this section as you add more tests
        // Add the tests for the first task
        for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
            ++run_count;
            TestResult result = tests_to_run[t]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << t << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << t << " passed." << endl;
                ++pass_count;
            }
        }
    }
    cout << "\n-------------------------------------------------\n"
         << "Total Run: " << run_count << "\n"
         << "Total PASSED: " << pass_count << "\n"
         << "Total FAILED: " << fail_count << "\n"
         << "-------------------------------------------------\n" << endl;

    // Return 0 if everything was ok
    return 0;
}
