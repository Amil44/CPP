#include <iostream>
#include <string>

class Driver;
class Company;
class Passenger;
 
class Vehicle {
protected:
    std::string _plate;
    std::string _model;
public:
    Vehicle() : _plate(""), _model("") {}
    Vehicle(std::string plate, std::string model)
        : _plate(plate), _model(model) {
    }

    virtual float calculateFare(float distance) const = 0;   

    virtual void showInfo() const {
        std::cout << "Plate: " << _plate << " | Model: " << _model;
    }

    virtual ~Vehicle() {}
};
 
class Car : public Vehicle {
public:
    Car() {}
    Car(std::string plate, std::string model)
        : Vehicle(plate, model) {
    }

    float calculateFare(float distance) const override {
        return distance * 0.50f;
    }

    void showInfo() const override {
        std::cout << "[Car] ";
        Vehicle::showInfo();
        std::cout << " | Rate: 0.50 AZN/km\n";
    }
};
 
class Van : public Vehicle {
public:
    Van() {}
    Van(std::string plate, std::string model)
        : Vehicle(plate, model) {
    }

    float calculateFare(float distance) const override {
        return distance * 0.80f;
    }

    void showInfo() const override {
        std::cout << "[Van] ";
        Vehicle::showInfo();
        std::cout << " | Rate: 0.80 AZN/km\n";
    }
};
 
class Driver {
    std::string _name;
    std::string _licencia;
    float _HowMuchCost;
    short _totalTrip;
    short _rating;
    Vehicle* _vehicle;   

    friend void completeTrip(Passenger& p, Driver& d, Company& c, float distance);

public:
    Driver() : _name(""), _licencia(""), _HowMuchCost(0),
        _totalTrip(0), _rating(0), _vehicle(nullptr) {
    }

    Driver(const std::string name, const std::string licencia,
        float HowMuchCost, short totalTrip, short rating, Vehicle* vehicle)
        : _name(name), _licencia(licencia), _HowMuchCost(HowMuchCost),
        _totalTrip(totalTrip), _rating(rating), _vehicle(vehicle) {
    }
     
    Driver(const Driver& other)
        : _name(other._name), _licencia(other._licencia),
        _HowMuchCost(other._HowMuchCost), _totalTrip(other._totalTrip),
        _rating(other._rating), _vehicle(nullptr) {
        if (other._vehicle) { 
            if (dynamic_cast<Car*>(other._vehicle))
                _vehicle = new Car(*dynamic_cast<Car*>(other._vehicle));
            else if (dynamic_cast<Van*>(other._vehicle))
                _vehicle = new Van(*dynamic_cast<Van*>(other._vehicle));
        }
    }
     
    Driver& operator=(const Driver& other) {
        if (this == &other) return *this;
        delete _vehicle;
        _name = other._name;
        _licencia = other._licencia;
        _HowMuchCost = other._HowMuchCost;
        _totalTrip = other._totalTrip;
        _rating = other._rating;
        _vehicle = nullptr;
        if (other._vehicle) {
            if (dynamic_cast<Car*>(other._vehicle))
                _vehicle = new Car(*dynamic_cast<Car*>(other._vehicle));
            else if (dynamic_cast<Van*>(other._vehicle))
                _vehicle = new Van(*dynamic_cast<Van*>(other._vehicle));
        }
        return *this;
    }

    ~Driver() {
        delete _vehicle;
        _vehicle = nullptr;
    }

    std::string getName()     const { return _name; }
    std::string getLisencia() const { return _licencia; }
    float getCost()           const { return _HowMuchCost; }
    short getTotalTrip()      const { return _totalTrip; }
    short getRating()         const { return _rating; }
    Vehicle* getVehicle()     const { return _vehicle; }

    float calculateFare(float distance) const {
        if (_vehicle) return _vehicle->calculateFare(distance);
        return distance * 0.50f;   
    }

    void getAllInfo() const {
        std::cout << "Name: " << _name
            << " | Licencia: " << _licencia
            << " | Cost: " << _HowMuchCost
            << " | Total Trip: " << _totalTrip
            << " | Rating: " << _rating << " | ";
        if (_vehicle) _vehicle->showInfo();
        else std::cout << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Driver& d) {
        os << "[ " << d._name << " ] Lisencia: " << d._licencia
            << " | Cost: " << d._HowMuchCost
            << " | Total Trip: " << d._totalTrip << "\n";
        return os;
    }
};
 
class Company {
    std::string _CompanyName;
    float _percentage;
    Driver* _drivers;
    static short _totalDriver;
    friend void completeTrip(Passenger& p, Driver& d, Company& c, float distance);

public:
    Company() : _CompanyName(""), _percentage(0), _drivers(nullptr) {}

    Company(const std::string CompanyName, float percentage)
        : _CompanyName(CompanyName), _percentage(percentage), _drivers(nullptr) {
    }

    ~Company() {
        delete[] _drivers;
        _drivers = nullptr;
    }

    void addDriver(const Driver& driver) {
        _totalDriver++;
        Driver* temp = new Driver[_totalDriver];
        for (int i = 0; i < _totalDriver - 1; i++)
            temp[i] = _drivers[i];
        temp[_totalDriver - 1] = driver;
        delete[] _drivers;
        _drivers = temp;
    }

    Driver mostValuableDriver() const {
        Driver best = _drivers[0];
        for (int i = 1; i < _totalDriver; i++)
            if (_drivers[i].getRating() > best.getRating())
                best = _drivers[i];
        return best;
    }

    short getTotalDriver() const { return _totalDriver; }

    friend std::ostream& operator<<(std::ostream& os, const Company& c) {
        os << "[ " << c._CompanyName << " ] Commission: " << c._percentage
            << "% | Total Drivers: " << c._totalDriver << "\n";
        return os;
    }
};

short Company::_totalDriver = 0;
 
class Passenger {
    std::string _name;
    float _wallet;
    friend void completeTrip(Passenger& p, Driver& d, Company& c, float distance);

public:
    Passenger() : _name(""), _wallet(0) {}

    Passenger(const std::string name, float wallet)
        : _name(name), _wallet(wallet) {
    }

    std::string getPassangerName() const { return _name; }
    float getWallet() const { return _wallet; }

    float pay(Driver dr) {
        if (_wallet >= dr.getCost()) {
            _wallet -= dr.getCost();
            std::cout << "Operation successful. Balance: ";
            return _wallet;
        }
        std::cout << "\nInsufficient balance.\n";
        return 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Passenger& p) {
        os << "[ " << p._name << " ] Wallet: " << p._wallet << "\n";
        return os;
    }
};
 
void completeTrip(Passenger& p, Driver& d, Company& c, float distance) {
    float cost = d.calculateFare(distance);   
    float commission = cost * (c._percentage / 100.0f);
    float driverEarning = cost - commission;

    if (p._wallet < cost) {
        std::cout << "Trip not started — insufficient balance!\n";
        return;
    }

    p._wallet -= cost;
    d._totalTrip++;

    std::cout << "--- Trip Completed ---\n"
        << "Driver    : " << d._name << "\n"
        << "Passenger : " << p._name << "\n"
        << "Distance  : " << distance << " km\n"
        << "Total     : " << cost << " AZN\n"
        << "Bolt cut  : " << commission << " AZN (" << c._percentage << "%)\n"
        << "Driver    : " << driverEarning << " AZN\n"
        << "----------------------\n";

    if (d._vehicle) d._vehicle->showInfo();

    std::cout << "[ " << p._name << " ] Balance: " << p._wallet << " AZN\n";
    std::cout << "[ " << c._CompanyName << " ] Commission: "
        << c._percentage << "% | Total Drivers: " << c._totalDriver << "\n";
}
 
template <typename T>
class BoltPool {
    T* _pool;
    int _size;
public:
    BoltPool() : _pool(nullptr), _size(0) {}

    ~BoltPool() {
        delete[] _pool;
        _pool = nullptr;
    }

    void add(const T& item) {
        T* temp = new T[_size + 1];
        for (int i = 0; i < _size; i++)
            temp[i] = _pool[i];
        temp[_size] = item;
        delete[] _pool;
        _pool = temp;
        _size++;
    }

    void printAll() const {
        for (int i = 0; i < _size; i++)
            std::cout << _pool[i];
    }

    int getSize() const { return _size; }
    T& get(int index) { return _pool[index]; }
};
 
int main() { 
    Car car1("10-AA-001", "Toyota Prius");
    Van van1("77-BB-002", "Ford Transit");
    Car car2("20-CC-003", "Honda Civic");
    Car car3("30-DD-004", "Hyundai Elantra");

    Passenger psg1("Nicat", 30.6);
    std::cout << psg1;
    Passenger psg2("Murad", 2.5);
    std::cout << psg2;

    Company company("Bolt AZ", 20);
    std::cout << company;

    Driver driver1("Yusuf", "AB123", 5.4, 30, 5, new Car("10-AA-001", "Toyota Prius"));
    Driver driver2("Ali", "CD456", 7.2, 45, 4, new Van("77-BB-002", "Ford Transit"));
    Driver driver3("Leyla", "EF789", 6.1, 25, 3, new Car("20-CC-003", "Honda Civic"));
    Driver driver4("Nihad", "GH012", 4.8, 18, 3, new Car("30-DD-004", "Hyundai Elantra"));

    driver1.getAllInfo();
    driver2.getAllInfo();
    driver3.getAllInfo();
    driver4.getAllInfo();

    company.addDriver(driver1);
    company.addDriver(driver2);
    company.addDriver(driver3);
    company.addDriver(driver4);

    std::cout << "Total Drivers: " << company.getTotalDriver() << "\n";
     
    std::cout << "\n--- Car Trip (driver1) ---\n";
    completeTrip(psg1, driver1, company, 10);
     
    std::cout << "\n--- Van Trip (driver2) ---\n";
    completeTrip(psg1, driver2, company, 10);

    Driver mvd = company.mostValuableDriver();
    std::cout << "\nMost Valuable Driver: " << mvd;

    BoltPool<Driver> drivers;
    drivers.add(driver1);
    drivers.add(driver2);
    drivers.add(driver3);
    drivers.printAll();

    BoltPool<Passenger> passengers;
    passengers.add(psg1);
    passengers.add(psg2);
    passengers.printAll();

    return 0;
}
