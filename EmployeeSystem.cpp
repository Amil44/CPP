#include <iostream>
#include <string>
#include <cstring>

class Person {
protected:
    char* name;
    short unsigned int age;
    bool isMan;
};

class Employee : public Person {
    short unsigned int salary;
    char* position;

public:
    static int totalEmployee;
    static int numberOfMen;
    static int numberOfWomen;

    const short int birthDate = 0;

    Employee(unsigned short int salary, short int birth) : birthDate(birth) {
        totalEmployee++;
        this->salary = salary;
    }

    Employee(unsigned short int salary, const char* position, short int year)
        : Employee(salary, year) {
        short int len = strlen(position) + 1;
        this->position = new char[len];
        strcpy_s(this->position, len, position);
    }

    Employee(const char* name, short unsigned int age, bool isMan,
        unsigned short int salary, const char* position, short int date)
        : Employee(salary, position, date) {

        this->age = age;
        this->isMan = isMan;

        short int len = strlen(name) + 1;
        this->name = new char[len];
        strcpy_s(this->name, len, name);

        if (isMan) numberOfMen++;
        else numberOfWomen++;

        totalEmployee = numberOfMen + numberOfWomen;
    }

    char* getName() { return this->name; }
    short int  getAge() { return this->age; }
    short int  getSalary() { return this->salary; }
    void setSalary(unsigned short int salary) {
        this->salary = salary;
    }
    char* getPosition() { return this->position; }
  
    ~Employee() {
         delete[] this->name;
         delete[] this->position;
    }

    short int getBirth() { return this->birthDate; }

    void printInfo() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Salary: " << salary << std::endl;
        std::cout << "Position: " << position << std::endl;
        std::cout << "Birth year: " << birthDate << std::endl << std::endl;
    }

    static float getMenRatio() {
        if (totalEmployee == 0) return 0;
        return (float)numberOfMen / totalEmployee * 100;
    }

    static float getWomenRatio() {
        if (totalEmployee == 0) return 0;
        return (float)numberOfWomen / totalEmployee * 100;
    }

    float raise(float percent) {
        //short unsigned salaryIncrease;
        //salaryIncrease = ;
        //x =
        salary = salary + (percent * salary) / 100;
        return salary;
    }
};

int Employee::numberOfMen = 0;
int Employee::numberOfWomen = 0;
int Employee::totalEmployee = 0;

int main() {
    Employee e1("Mike", 30, true, 2500, "Manager", 1995);
    Employee e2("Diana", 25, false, 1800, "Developer", 1999);
    Employee e3("Katerina", 30, false, 1700, "QA", 1995);

    std::cout << "------ Employee1 ------\n"; e1.printInfo();
    std::cout << "------ Employee2 ------\n"; e2.printInfo();
    std::cout << "------ Employee3 ------\n"; e3.printInfo();

    std::cout << e3.getName() << " got a raise: " << e3.raise(5.5) << std::endl;

    std::cout << "A number of males:  " << Employee::numberOfMen << std::endl;
    std::cout << "A number of females: " << Employee::numberOfWomen << std::endl;
    std::cout << "A number of people(Total Employees): " << Employee::totalEmployee << std::endl;
    std::cout << "Ratio of men: " << Employee::getMenRatio() << "%" << std::endl;
    std::cout << "Ratio of women: " << Employee::getWomenRatio() << "%" << std::endl;
}

