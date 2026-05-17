#include <iostream>
#include <string>

class Aircraft {
	std::string _registrationNumber;
	std::string _modelName;
	short _maxPassengers;
	float _maxFlightRange;
public:
	Aircraft() : _registrationNumber(""), _modelName(""), _maxPassengers(0), _maxFlightRange(0) {}
	Aircraft(std::string regNum, std::string model,short passengers, float range){
		_registrationNumber = regNum;
		_modelName = model;
		_maxPassengers = passengers;
		_maxFlightRange = range;
	}

	virtual void fly() = 0;
	virtual void land() = 0;
	virtual void getType() = 0;

	void showInfo() {
		std::cout << 
			"Registration Number: " << _registrationNumber <<
			"\nModel Name: " << _modelName <<
			"\nMax Passengers: " << _maxPassengers <<
			"\nMax Flight Range: " << _maxFlightRange << std::endl;
	}

	std::string getRegistrationNumber() const { return _registrationNumber; }
	std::string getModelName() const { return _modelName; }
	short getMaxPassengers() const { return _maxPassengers; }
	float getMaxFlightRange() const { return _maxFlightRange; }
	virtual ~Aircraft() {}
};

class PassengerPlane : public Aircraft{
	short _businessClassSeats;
public:
	PassengerPlane() : _businessClassSeats(0) {}
	PassengerPlane(std::string regNum, std::string model, short passengers, float range, short businessSeats): Aircraft(regNum, model, passengers, range){
		_businessClassSeats = businessSeats;
	}

	void fly() override {
		std::cout << "Passanger Plane [" << getModelName() << "] is flying.\n";
	}

	void land() override {
		std::cout << "Passanger Plane [" << getModelName() << "] is landing." << std::endl;
	}

	void getType() override {
		std::cout << "Type: Passenger Plane" << std::endl;
	}
};

class CargoPlane : public Aircraft{
	float _maxCargoVolume;
public:
	CargoPlane() : _maxCargoVolume(0) {}
	CargoPlane(std::string regNum, std::string model, short passengers, float range, float maxCargo): Aircraft(regNum, model, passengers, range){
		_maxCargoVolume = maxCargo;
	}

	void fly() override {
		std::cout << "Passanger Plane [" << getModelName() << "] is flying.\n";
	}

	void land() override {
		std::cout << "Cargo Plane [" << getModelName() << "] is landing." << std::endl;
	}

	void getType() override {
		std::cout << "Type: Cargo Plane" << std::endl;
	}
};

class PrivateJet : public Aircraft {
	std::string _ownerName;

public:
	PrivateJet(std::string regNum, std::string model, short passengers, float range, std::string owner) : Aircraft(regNum, model, passengers, range){
		_ownerName = owner;
	}

	void fly() override {
		std::cout << "Private Jet [" << getModelName() << "] - [" << _ownerName << "]" << std::endl;
	}

	void land() override {
		std::cout << "Private Jet [" << getModelName() << "] is landing." << std::endl;
	}

	void getType() override {
		std::cout << "Type: Private Jet" << std::endl;
	}

	std::string getOwnerName() const { return _ownerName; }
};

class Passenger {
private:
	std::string _name;
	std::string _passportNumber;
	double _balance;

public:
	Passenger() : _name(""), _passportNumber(""), _balance(0){}
	Passenger(std::string name, std::string passportNumber, double balance){
		_name = name;
		_passportNumber = passportNumber;
		_balance = balance;
	}

 	std::string getName() const { return _name; }
	std::string getPassportNumber() const { return _passportNumber; }
	double getBalance() const { return _balance; }

	void showInfo() const {
		std::cout << "Passenger: " << _name << "\nPassport: " << _passportNumber << "\nBalance: $" << _balance << "\n";
	}
};

enum TicketClass {
	Economy,
	Business,
	First
};

class Ticket{
public:  
	struct Seat {
		short rowNumber;
		char letter;
		Seat() : rowNumber(0), letter(' ') {}
		Seat(short row, char let) : rowNumber(row), letter(let) {}
		void show() const {
			std::cout << "Seat: " << rowNumber << letter << "\n";
		}
	};
private:
	std::string _ticketNumber;
	std::string _flightNumber;
	double _price;
	Passenger _passenger;
	Seat _seat;
	TicketClass _ticketClass;
public:
	Ticket() : _ticketNumber(""), _flightNumber(""), _price(0) {}
	Ticket(std::string ticketNumber, std::string flightNumber, double price, TicketClass ticketClass, Passenger passenger, Seat seat) : _ticketNumber(ticketNumber), _flightNumber(flightNumber), _price(price), _ticketClass(ticketClass), _passenger(passenger), _seat(seat) {}

	std::string getTicketNumber() const { return _ticketNumber; }
	std::string getFlightNumber() const { return _flightNumber; }
	double getPrice() const { return _price; }
	Seat getSeat() const { return _seat; }
	Passenger getPassenger() const { return _passenger; }

	static std::string getTicketClass(TicketClass tc) {
		switch (tc) {
			case TicketClass::Economy: return "Economy";
			case TicketClass::Business: return "Business";
			case TicketClass::First: return "First";
		}
		return "Unknown";
	}

	void showInfo() const {
		std::cout
			<< "Ticket: " << _ticketNumber
			<< "\nFlight: " << _flightNumber
			<< "\nClass: " << getTicketClass(Economy)
			<< "\nPrice: $" << _price
			<< "\n";
		_seat.show();
		_passenger.showInfo();
	}
};

class Flight {
	std::string _flightNo;
	Aircraft* _aircraft = {};
	int _ticketCount;
	Ticket* _tickets[50] = {};
	std::string _flyToCity;
	std::string _landToCity;
	std::string _flightTime;
	enum status { Scheduled, Boarding, InFlight, Landed, Cancelled } _status;
public:
	Flight(std::string flightNo, Aircraft* aircraft, std::string from, std::string to, std::string time) : _ticketCount(0), _flightNo(flightNo), _aircraft(aircraft), _flyToCity(from), _landToCity(to), _flightTime(time), _status(Scheduled) {
		for (int i = 0; i < 50; i++) _tickets[i] = nullptr;
	}

	void addPassenger(Ticket* t) {
		if (_ticketCount >= _aircraft->getMaxPassengers()) {
			std::cout << "Flight " << _flightNo << " is full!\n";
			return;
		}
		_tickets[_ticketCount++] = t;
		std::cout << "Passenger [" << t->getPassenger().getName() << "] added.\n";
	}


	void departFlight() {
		_status = InFlight;
		std::cout << "Flight " << _flightNo << " is departing!\n";
		_aircraft->fly();
	}

	void landFlight() {
		_status = Landed;
		std::cout << "Flight " << _flightNo << " has landed!\n";
		_aircraft->land();
	}

	void cancelFlight() {
		_status = Cancelled;
		std::cout << "Flight " << _flightNo << " has been cancelled.\n";
	}

	void showManifest() const {
		std::cout << "===== MANIFEST: " << _flightNo << " =====\n";
		for (int i = 0; i < _ticketCount; i++) {
			if (_tickets[i] != nullptr) {
				std::cout << "  " << (i + 1) << ". ";
				_tickets[i]->getPassenger().showInfo();
			}
		}
	} 

	std::string getStatusStr() const {
		switch (_status) {
			case Scheduled:  
				return "Scheduled";
			case Boarding:   
				return "Boarding";
			case InFlight:   
				return "InFlight";
			case Landed:     
				return "Landed";
			case Cancelled:  
				return "Cancelled";
		}
		return "Unknown";
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Flight& f) {
		os << "[" << f._flightNo << "] "
			<< f._flyToCity << " -> " << f._landToCity
			<< "\nAircraft : " << f._aircraft->getModelName()
			<< " | Passangers: " << f._ticketCount << "/" << f._aircraft->getMaxPassengers()
			<< "\nStatus  : " << f.getStatusStr();
		return os;
	}
};

class Airport {
public:
	struct Address { 
		std::string _city;
		std::string _country;

		Address() : _city(""), _country("") {}
		Address(std::string street, std::string city, std::string country) : _city(city), _country(country) {}

		void showInfo() const {
			std::cout << _city << ", " << _country;
		}
	};

private:
	std::string _name;
	Address _address;          
	Aircraft* _aircrafts[100];  
	int _aircraftCount;
	Flight* _flights[100];      
	int _flightCount;
public:
	Airport(std::string name, Address address) : _name(name), _address(address), _aircraftCount(0), _flightCount(0) {
		for (int i = 0; i < 100; i++) _aircrafts[i] = nullptr;
		for (int i = 0; i < 100; i++) _flights[i] = nullptr;
	}

	void addAircraft(Aircraft* a) {
		if (_aircraftCount >= 100) {
			std::cout << "Aircraft capacity full!\n";
			return;
		}
		_aircrafts[_aircraftCount++] = a;
		std::cout << "Aircraft [" << a->getModelName() << "] added to " << _name << ".\n";
	}

	void addFlight(Flight* f) {
		if (_flightCount >= 100) {
			std::cout << "Flight capacity full!\n";
			return;
		}
		_flights[_flightCount++] = f;
		std::cout << "Flight added to " << _name << ".\n";
	}

	void showInfo() const {
		std::cout << "Airport : " << _name << "\nAddress : ";
		_address.showInfo();
		std::cout << "\nAircrafts: " << _aircraftCount << " | Flights: " << _flightCount << "\n";
	}

	void showAllFlights() const {
		std::cout << "===== ALL FLIGHTS @ " << _name << " =====\n";
		for (int i = 0; i < _flightCount; i++) {
			if (_flights[i] != nullptr) { 
				std::cout << *_flights[i] << "\n\n"; }
		}
	}

	void showAllAircrafts() const {
		std::cout << "===== ALL AIRCRAFTS @ " << _name << " =====\n";
		for (int i = 0; i < _aircraftCount; i++) {
			if (_aircrafts[i] != nullptr) {
				_aircrafts[i]->showInfo();
			}
			std::cout << "\n";
		}
	}

	std::string getName() const { return _name; }
	Address getAddress() const { return _address; }
};

int main(){
	std::cout << "=========== CARGO PLANE ===========\n";
	CargoPlane cargoplane("AA-84", "Cargo X5", 6, 4300.53, 100);
	cargoplane.showInfo();
	cargoplane.getType();
	cargoplane.fly();
	cargoplane.land();

	std::cout << "\n=========== PRIVATE JET ===========\n";
	PrivateJet pjet( "AB-12", "Jet Black", 12, 13900, "Eyvazli" );
	pjet.showInfo();
	pjet.getType();
	pjet.fly();
	pjet.land();

	std::cout << "\n=========== TICKET ===========\n";
	Passenger p1("Amil Eyvazli", "AZE1234", 3200.0);
	Ticket::Seat seat1(20, 'A');    
	Ticket t1("TK-001", "J2 - 101", 599.99, TicketClass::Business, p1, seat1);
	t1.showInfo();

	std::cout << "\n=========== FLIGHT ===========\n";
	PassengerPlane plane1("TC-737", "Boeing 737", 180, 5000, 30);

	Passenger p2("Tural Hasanov", "AZE5678", 1500.0);
	Passenger p3("Leyla Mammadova", "AZE9999", 2800.0);

	Ticket::Seat s2(12, 'B');
	Ticket::Seat s3(15, 'C');

	Ticket t2("TK-002", "FLY-1042", 450.00, TicketClass::Economy, p2, s2);
	Ticket t3("TK-003", "FLY-1042", 850.00, TicketClass::Business, p3, s3);

	Flight flight1("FLY-1042", &plane1, "Baki", "Istanbul", "14:30");

	flight1.addPassenger(&t2);
	flight1.addPassenger(&t3);

	flight1.departFlight();

	std::cout << "\n" << flight1 << "\n";

	flight1.showManifest();

	flight1.landFlight();

	std::cout << "\n=========== AIRPORT ===========\n";

	Airport::Address addr("Binagadi Highway 1", "Baku", "Azerbaijan");
	Airport airport("Heydar Aliyev International Airport", addr);

	PassengerPlane plane2("TC-737", "Boeing 737", 180, 5000, 30);
	CargoPlane cargo2("AA-84", "Cargo X5", 6, 4300, 100);

	airport.addAircraft(&plane2);
	airport.addAircraft(&cargo2);

	Ticket::Seat s4(12, 'B');
	Ticket::Seat s5(15, 'C');
	Passenger p4("Tural Hasanov", "AZE5678", 1500.0);
	Passenger p5("Leyla Mammadova", "AZE9999", 2800.0);
	Ticket t4("TK-002", "FLY-1042", 450.00, TicketClass::Economy, p4, s4);
	Ticket t5("TK-003", "FLY-1042", 850.00, TicketClass::Business, p5, s5);

	Flight flight2("FLY-1042", &plane1, "Baku", "Istanbul", "14:30");
	flight2.addPassenger(&t4);
	flight2.addPassenger(&t5);
	flight2.departFlight();

	airport.addFlight(&flight1);

	airport.showInfo();
	airport.showAllFlights();
	airport.showAllAircrafts();

	return 0;
}