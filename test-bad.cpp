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

	Date t1(1,9);
	Date t2(1,9);
	Date t3(10,23);
	Date t4(11,0);

	ASSERT(!t1.isLessThan(t2));
	ASSERT(t3.isLessThan(t4));

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
	ben->decreaseLoyaltyPoints(1000);
	ASSERT(ben->getLoyaltyPoints() == 0);

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

	Airplane *plane1 = new Airplane(100);
	Route *path1 = new Route(source, destination, 7);
	Flight flight1(path1, plane1);

	ASSERT(flight1.getAirplane() == plane1);
    ASSERT(flight1.getRoute() == path1);
	ASSERT(flight1.getAvailableSeats() == 97);


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

    Route *path = new Route(source, destination, 7);
    Airplane *airplane = new Airplane(300);
    Flight flight(path, airplane);

    //Pilots
    vector<Pilot*> pilots;
    Pilot *jack = new Pilot("Jack",123);
    Pilot *jenny = new Pilot("Jenny",10);
    pilots.push_back(jack);
    pilots.push_back(jenny);
    ASSERT(!flight.setPilots(pilots));

	Pilot* frank = new Pilot("Frank", 1);
	pilots.push_back(frank);
	ASSERT(!flight.setPilots(pilots));

	pilots.erase(pilots.begin() + 2);
	jenny->promote();
    ASSERT(flight.setPilots(pilots));
    ASSERT(flight.getAvailableSeats() == 297);

	pilots.push_back(frank);
	Pilot* dracula = new Pilot("Dracula", 2);
	pilots.push_back(dracula);
	ASSERT(!flight.setPilots(pilots));

	Route *path2 = new Route(source, destination, 10);
	Flight flight2(path2, airplane);

	ASSERT(!flight2.setPilots(pilots));
	ASSERT(flight2.getPilots().size() == 0);
	ASSERT(!flight2.setPilots(pilots));

	dracula->promote();
	ASSERT(flight2.setPilots(pilots));
	ASSERT(flight2.getPilots().size() == 4);

	vector <Pilot*> pilots2;
	Route *path3 = new Route(source, destination, 10);
	Flight flight3(path3, airplane);
	Pilot *ankle = new Pilot("ankle",11); ankle->promote();
    Pilot *arm = new Pilot("arm",12); arm->promote();
	Pilot *ass = new Pilot("ass",13);
    Pilot *appendix = new Pilot("appendix",14);
	pilots2.push_back(ankle);
	pilots2.push_back(arm);
	pilots2.push_back(ass);
	pilots2.push_back(appendix);
	ASSERT(flight3.setPilots(pilots2));

    return TR_PASS;
}

/*
 * Check correctly adding flight attendants to the flight
 */
TestResult testFlightAddFlightAttendants() {
	Country *source = new Country("Cairo", Country::ARABIC);
	Country *destination = new Country("Madrid", Country::SPANISH);

	Route *path = new Route(source, destination, 4);
    Airplane *airplane = new Airplane(300);
    Flight flight(path, airplane);

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

	flightAttendants.clear();
	Country *source2 = new Country("CANDYLAND", Country::ARABIC);
	Country *destination2 = new Country("BONG", Country::SPANISH);
	Country::Language src = Country::ARABIC;
	Country::Language dest = Country::SPANISH;
	Route *path2 = new Route(source2, destination2, 10);
	Flight flight2(path2, airplane);
	FlightAttendant *john = new FlightAttendant("John", 40);
	FlightAttendant *liam = new FlightAttendant("Liam", 41);
	FlightAttendant *lydia = new FlightAttendant("Lydia", 42);
	FlightAttendant *hannah = new FlightAttendant("Hannah", 43);
	FlightAttendant *michael = new FlightAttendant("Michael", 44);
	FlightAttendant *will = new FlightAttendant("Will", 45);
	john->addLanguage(Country::ENGLISH); flightAttendants.push_back(john);
	liam->addLanguage(src); flightAttendants.push_back(liam);
	lydia->addLanguage(dest); flightAttendants.push_back(lydia);
	hannah->addLanguage(Country::ENGLISH); flightAttendants.push_back(hannah);
	hannah->addLanguage(src);
	michael->addLanguage(dest); flightAttendants.push_back(michael);
	will->addLanguage(dest); flightAttendants.push_back(will);
	ASSERT(flight2.setFlightAttendants(flightAttendants));

	flightAttendants.clear();
	Country *source3 = new Country("CANDYLAND", Country::ENGLISH);
	Country *destination3 = new Country("BONG", Country::SPANISH);
	Country::Language src3 = Country::ENGLISH;
	Country::Language dest3 = Country::SPANISH;
	Route *path3 = new Route(source3, destination3, 10);
	Flight flight3(path3, airplane);
	FlightAttendant *a = new FlightAttendant("a", 46);
	FlightAttendant *b = new FlightAttendant("b", 47);
	FlightAttendant *c = new FlightAttendant("c", 48);
	FlightAttendant *d = new FlightAttendant("d", 49);
	FlightAttendant *e = new FlightAttendant("e", 50);
	FlightAttendant *f = new FlightAttendant("f", 51);
	a->addLanguage(src3); flightAttendants.push_back(a);
	b->addLanguage(src3); flightAttendants.push_back(b);
	c->addLanguage(src3); flightAttendants.push_back(c);
	d->addLanguage(src3); flightAttendants.push_back(d);
	e->addLanguage(dest3); flightAttendants.push_back(e);
	f->addLanguage(dest3); flightAttendants.push_back(f);
	ASSERT(flight3.setFlightAttendants(flightAttendants));

	flightAttendants.clear();
	Country *source4 = new Country("CANDYLAND", Country::HINDI);
	Country *destination4 = new Country("BONG", Country::ENGLISH);
	Country::Language src4 = Country::HINDI;
	Country::Language dest4 = Country::ENGLISH;
	Route *path4 = new Route(source4, destination4, 10);
	Flight flight4(path4, airplane);
	FlightAttendant *g = new FlightAttendant("a", 52);
	FlightAttendant *h = new FlightAttendant("b", 53);
	FlightAttendant *i = new FlightAttendant("c", 54);
	FlightAttendant *j = new FlightAttendant("d", 55);
	FlightAttendant *k = new FlightAttendant("e", 56);
	FlightAttendant *l = new FlightAttendant("f", 57);
	g->addLanguage(src4); flightAttendants.push_back(g);
	g->addLanguage(Country::ENGLISH);
	h->addLanguage(dest4); flightAttendants.push_back(h);
	i->addLanguage(dest4); flightAttendants.push_back(i);
	j->addLanguage(dest4); flightAttendants.push_back(j);
	k->addLanguage(src4); flightAttendants.push_back(k);
	l->addLanguage(src4); flightAttendants.push_back(l);
	ASSERT(flight4.setFlightAttendants(flightAttendants));

	flightAttendants.clear();
	Country *source5 = new Country("CANDYLAND", Country::HINDI);
	Country *destination5 = new Country("BONG", Country::CHINESE);
	Country::Language src5 = Country::HINDI;
	Country::Language dest5 = Country::CHINESE;
	Route *path5 = new Route(source5, destination5, 8);
	Flight flight5(path5, airplane);
	FlightAttendant *m = new FlightAttendant("a", 52);
	FlightAttendant *n = new FlightAttendant("b", 53);
	FlightAttendant *o = new FlightAttendant("c", 54);
	FlightAttendant *p = new FlightAttendant("d", 55);
	FlightAttendant *q = new FlightAttendant("e", 56);
	FlightAttendant *r = new FlightAttendant("f", 57);
	m->addLanguage(src5); flightAttendants.push_back(m);
	m->addLanguage(Country::ENGLISH);
	n->addLanguage(dest5); flightAttendants.push_back(n);
	n->addLanguage(Country::ENGLISH);
	o->addLanguage(src5); flightAttendants.push_back(o);
	o->addLanguage(dest5);
	p->addLanguage(src5); flightAttendants.push_back(p);
	p->addLanguage(dest5);
	q->addLanguage(dest5); flightAttendants.push_back(q);
	q->addLanguage(Country::ENGLISH);
	r->addLanguage(src5); flightAttendants.push_back(r);
	r->addLanguage(dest5);
	r->addLanguage(Country::ENGLISH);
	ASSERT(flight5.setFlightAttendants(flightAttendants));

	flightAttendants.clear();
	Country *source6 = new Country("CANDYLAND", Country::ENGLISH);
	Country *destination6 = new Country("BONG", Country::ENGLISH);
	Country::Language src6 = Country::ENGLISH;
	Country::Language dest6 = Country::ENGLISH;
	Route *path6 = new Route(source6, destination6, 1);
	Flight flight6(path6, airplane);
	FlightAttendant *s = new FlightAttendant("a", 52);
	FlightAttendant *t = new FlightAttendant("b", 53);
	FlightAttendant *u = new FlightAttendant("c", 54);
	s->addLanguage(src6); flightAttendants.push_back(s);
	t->addLanguage(src6); flightAttendants.push_back(t);
	u->addLanguage(dest6); flightAttendants.push_back(u);
	ASSERT(flight6.setFlightAttendants(flightAttendants));

	FlightAttendant *v = new FlightAttendant("a", 52);
	v->addLanguage(src6); flightAttendants.push_back(v);
	ASSERT(!flight6.setFlightAttendants(flightAttendants));

	FlightAttendant *w = new FlightAttendant("a", 52);
	FlightAttendant *x = new FlightAttendant("a", 52);
	w->addLanguage(src6); flightAttendants.push_back(w);
	x->addLanguage(src6); flightAttendants.push_back(x);
	ASSERT(!flight6.setFlightAttendants(flightAttendants));

	flightAttendants.clear();
	Country *source7 = new Country("CANDYLAND", Country::ARABIC);
	Country *destination7 = new Country("BONG", Country::SPANISH);
	Country::Language src7 = Country::ARABIC;
	Country::Language dest7 = Country::SPANISH;
	Route *path7 = new Route(source7, destination7, 7);
	Flight flight7(path7, airplane);
	FlightAttendant *dog = new FlightAttendant("John", 40);
	FlightAttendant *cat = new FlightAttendant("Liam", 41);
	FlightAttendant *wolf = new FlightAttendant("Lydia", 42);
	dog->addLanguage(Country::ENGLISH); flightAttendants.push_back(dog);
	cat->addLanguage(src7); flightAttendants.push_back(cat);
	wolf->addLanguage(dest7); flightAttendants.push_back(wolf);
	ASSERT(flight7.setFlightAttendants(flightAttendants));

	flightAttendants.clear();
	Country *source8 = new Country("CANDYLAND", Country::ARABIC);
	Country *destination8 = new Country("BONG", Country::ENGLISH);
	Country::Language src8 = Country::ARABIC;
	//Country::Language dest8 = Country::ENGLISH;
	Route *path8 = new Route(source8, destination8, 7);
	Flight flight8(path8, airplane);
	FlightAttendant *frank = new FlightAttendant("John", 40);
	FlightAttendant *fart = new FlightAttendant("Liam", 41);
	FlightAttendant *felicity = new FlightAttendant("Lydia", 42);
	frank->addLanguage(Country::ENGLISH); flightAttendants.push_back(frank);
	fart->addLanguage(src8); flightAttendants.push_back(fart);
	felicity->addLanguage(Country::ENGLISH); flightAttendants.push_back(felicity);
	ASSERT(flight8.setFlightAttendants(flightAttendants));

	flightAttendants.clear();
	Country *source9 = new Country("CANDYLAND", Country::ARABIC);
	Country *destination9 = new Country("PANCAKETOWN", Country::CHINESE);
	Country::Language src9 = Country::ARABIC;
	Country::Language dest9 = Country::CHINESE;
	Route *path9 = new Route(source9, destination9, 7);
	Flight flight9(path9, airplane);
	FlightAttendant *flip = new FlightAttendant("John", 40);
	FlightAttendant *flop = new FlightAttendant("Liam", 41);
	FlightAttendant *flap = new FlightAttendant("Lydia", 42);
	flip->addLanguage(Country::SPANISH); flightAttendants.push_back(flip);
	flop->addLanguage(src9); flightAttendants.push_back(flop);
	flap->addLanguage(dest9); flightAttendants.push_back(flap);
	ASSERT(!flight9.setFlightAttendants(flightAttendants));

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
    ASSERT(customers.size() == 0);

    ASSERT(fms.addCustomer(ben));
    customers = fms.getCustomers();
    ASSERT(customers.size() == 1);

    Customer *luke = new Customer("Luke", "M20231");
    ASSERT(fms.addCustomer(luke));
    customers = fms.getCustomers();
    ASSERT(customers.size() == 2);

    // Customer with a different name, but same passport number -- shouldn't be added
    Customer *ben2 = new Customer("Not Ben Again", "K43681");
    ASSERT(!fms.addCustomer(ben2));
	customers = fms.getCustomers();
	ASSERT(customers.size() == 2);

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

	Route *path = new Route(miami, lima, 10);
	Airplane *plane = new Airplane(100);
	Flight *trip = new Flight(path, plane);
	Date *time = new Date(1,1);
	fms.addFlight(trip, time);
	Customer *tinkywinky = new Customer("tinkywinky", "999");
	fms.addCustomer(tinkywinky);
	ASSERT(fms.bookTicket(path, time, "999", 20));
    ASSERT(fms.getCapacity(path, time) == 72);
    ASSERT(fms.getCustomerPoints("999") == 200);
	ASSERT(!fms.bookTicket(path, time, "999", 200));

	Route *badPath = new Route(miami, lima, 99);
	Date *badTime = new Date(13,8);

	ASSERT(!fms.bookTicket(badPath, time, "999", 20));
    ASSERT(!fms.bookTicket(path, badTime, "999", 20));
	ASSERT(fms.getCustomerPoints("999") == 200);



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
