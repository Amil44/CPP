#include <iostream>
#include <string>

class Vehicle {
protected:                          
    std::string _brand;
    short _speed;
public:
    Vehicle() : _brand(""), _speed(0) {}
    Vehicle(std::string brand, short speed) : _brand(brand), _speed(speed) {}

    virtual void showInfo() = 0;    
    virtual ~Vehicle() {}
};

class Car : virtual public Vehicle {   
    std::string _name;
public:
    Car() : _name("") {}
    Car(std::string name, std::string brand, short speed)
        : Vehicle(brand, speed), _name(name) {
    }

    void showInfo() override {
        std::cout << "Car name is " << _name << std::endl;
    }

    void drive() {
        std::cout << _name << " is driving" << std::endl;
    }
};

class Boat : virtual public Vehicle {  
    std::string _name;
public:
    Boat() : _name("") {}
    Boat(std::string name, std::string brand, short speed)
        : Vehicle(brand, speed), _name(name) {
    }

    void showInfo() override {
        std::cout << "Boat name is " << _name << std::endl;
    }

    void sail() {
        std::cout << _name << " is sailing" << std::endl;
    }
};

class AmphibiousVehicle : public Car, public Boat {
    std::string _name;
public:
    AmphibiousVehicle() : _name("") {}
    AmphibiousVehicle(std::string name, std::string brand, short speed)
        : Vehicle(brand, speed), Car(name, brand, speed),
        Boat(name, brand, speed), _name(name) {
    }

    void showInfo() override {       
        std::cout << "Amphibious Vehicle: " << _name
            << " | Brand: " << _brand
            << " | Speed: " << _speed << std::endl;
    }
};

int main() {
    AmphibiousVehicle amphibiousVehicle("Hydra", "AmphibiCo", 120);
    amphibiousVehicle.drive();
    amphibiousVehicle.sail();
    amphibiousVehicle.showInfo();

    return 0;
}