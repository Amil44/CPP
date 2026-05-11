#include <iostream>
#include <string>

class Person {
protected:
    std::string _name;
    short unsigned _age;
    std::string _email;
public:
    Person() : _name(""), _age(0), _email("") {}
    Person(std::string name, short age, std::string email)
        : _name(name), _age(age), _email(email) {
    }

    virtual void showInfo() const {
        std::cout << "[ " << _name << " ] " << _age << " years old. "
            << "Email: " << _email << std::endl;
    }
};

class Student : public Person {
    short unsigned _studentId;
    float _GPA;
public:
    Student() : _studentId(0), _GPA(0) {}
    Student(std::string name, short age, std::string email, short studentId, float GPA)
        : Person(name, age, email), _studentId(studentId), _GPA(GPA) {
    }

    void showInfo() const override {
        std::cout << "[ " << _name << " ] " << _age << " years old. "
            << "Email: " << _email
            << " | Student Id: " << _studentId
            << " | GPA: " << _GPA << std::endl;
    }
};

class Professor : public Person {
    std::string _degree;
public:
    Professor() : _degree("") {}
    Professor(std::string name, short age, std::string email, std::string degree)
        : Person(name, age, email), _degree(degree) {
    }

    void showInfo() const override {
        std::cout << "[ " << _name << " ] " << _age << " years old. "
            << "Email: " << _email
            << " | Degree: " << _degree << std::endl;
    }
};

class Address {
    std::string _city;
    std::string _street;
    short unsigned _houseNumber;
public:
    Address() : _city(""), _street(""), _houseNumber(0) {}
    Address(std::string city, std::string street, short houseNumber)
        : _city(city), _street(street), _houseNumber(houseNumber) {
    }

    void showInfo() const {
        std::cout << "[ " << _city << " ] | Street: " << _street
            << " | House Number: " << _houseNumber << std::endl;
    }
};

class University {
public:
    Address addr;

    University() {}
    University(std::string city, std::string street, short houseNumber)
        : addr(city, street, houseNumber) {
    }

    void showUniAddr() const { addr.showInfo(); }
};

class Schedule {
    std::string _lesson;
    std::string _time;
public:
    Schedule() : _lesson(""), _time("") {}
    Schedule(std::string lesson, std::string time) : _lesson(lesson), _time(time) {}

    void addClass() {
        std::cout << "Lesson: ";
        std::cin >> _lesson;
        std::cout << "Time: ";
        std::cin >> _time;
    }
};

class Course {
    std::string _name;
    short unsigned _credit;
    Professor* _professor;
    Student* _students[100];        
    int _studentCount;
public:
    Course() : _name(""), _credit(0), _professor(nullptr), _studentCount(0) {
        for (int i = 0; i < 100; i++) _students[i] = nullptr;
    }
    Course(std::string name, short credit, Professor* prof)
        : _name(name), _credit(credit), _professor(prof), _studentCount(0) {
        for (int i = 0; i < 100; i++) _students[i] = nullptr;
    }

    void enrollStudent(Student* s) {
        if (_studentCount < 100) {
            _students[_studentCount++] = s;
        }
        else {
            std::cout << "Course is full!\n";
        }
    }

    void showInfo() const {
        std::cout << "[ " << _name << " ] Credits: " << _credit;
        if (_professor) {
            std::cout << " | Professor: ";
            _professor->showInfo();
        }
        else {
            std::cout << " | No professor assigned.\n";
        }
        if (_studentCount == 0) {
            std::cout << "  No students enrolled.\n";
        }
        else {
            std::cout << "  Enrolled students:\n";
            for (int i = 0; i < _studentCount; i++) {
                std::cout << "    ";
                _students[i]->showInfo();
            }
        }
    }
};

class Department {
    Schedule _schedule;
    Professor* _professor;
    Course* _courses[50];         
    int _courseCount;
public:
    Department() : _schedule(), _professor(nullptr), _courseCount(0) {
        for (int i = 0; i < 50; i++) _courses[i] = nullptr;
    }
    Department(std::string lesson, std::string time)
        : _schedule(lesson, time), _professor(nullptr), _courseCount(0) {
        for (int i = 0; i < 50; i++) _courses[i] = nullptr;
    }
    Department(std::string lesson, std::string time, Professor* professor)
        : _schedule(lesson, time), _professor(professor), _courseCount(0) {
        for (int i = 0; i < 50; i++) _courses[i] = nullptr;
    }

    void addProfessor(Professor* p) { _professor = p; }

    void addCourse(Course* c) {
        if (_courseCount < 50) {
            _courses[_courseCount++] = c;
        }
        else {
            std::cout << "Department course limit reached!\n";
        }
    }

    void showCourses() const {
        if (_courseCount == 0) {
            std::cout << "No courses in this department.\n";
        }
        else {
            for (int i = 0; i < _courseCount; i++) {
                _courses[i]->showInfo();
            }
        }
    }
};

int main() {
    std::cout << "========== STUDENTS ==========\n";
    Student s1("Bob", 20, "Bob20@gmail.com", 101, 88.3);
    Student s2("Mike", 21, "Mike21@gmail.com", 102, 45.2);
    s1.showInfo();
    s2.showInfo();

    std::cout << "\n========== PROFESSORS ==========\n";
    Professor p1("Jhon", 40, "Jhon40@gmail.com", "NASA CERTIFICATED");
    p1.showInfo();

    std::cout << "\n========== UNIVERSITY ==========\n";
    University university1("New York", "5th Avenue", 123);
    university1.showUniAddr();

    std::cout << "\n========== SCHEDULE ==========\n";
    Schedule schedule1;
    schedule1.addClass();

    std::cout << "\n========== COURSE ==========\n";
    Course course1("Math 101", 3, &p1);
    course1.enrollStudent(&s1);
    course1.enrollStudent(&s2);
    course1.showInfo();

    std::cout << "\n========== DEPARTMENT ==========\n";
    Department department1;
    department1.addProfessor(&p1);
    department1.addCourse(&course1);
    department1.showCourses();

    return 0;
}