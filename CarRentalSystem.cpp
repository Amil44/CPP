#include <iostream>
#include <string>

struct Cars {
	std::string brands;
	std::string models[2];
	bool isTaken[2];
};

class Car {
public:
	void rent(Cars cars[]) {
		std::cout << "\n===== Our Cars =====\n";
		for (int i = 0; i < 10; i++) {
			std::cout << i + 1 << "." << cars[i].brands << std::endl;
		}

		std::cout << "Select car: ";
		short int selectC;
		std::cin >> selectC;

		if (selectC > 0 && selectC < 11) {
			std::cout << "Select model: ";
			std::cout << cars[selectC - 1].models[0] << "(1) & " << cars[selectC - 1].models[1] << "(2): ";

			short int selectM;
			std::cin >> selectM;

			if (selectM > 0 && selectM < 3) {
				if (!cars[selectC - 1].isTaken[selectM - 1]) {
					cars[selectC - 1].isTaken[selectM - 1] = true;
					std::cout << "Car Was Successfully Rented!\n";
				}
				else {
					std::cout << "This Car is full.\n";
				}
			}
			else {
				std::cout << "Invalid Model!\n";
			}
		}
		else {
			std::cout << "Invalid Operation!\n";
		}
	}

	void returnCar(Cars cars[]) {
		std::cout << "\n===== Return Cars =====\n";
		for (int i = 0; i < 10; i++) {
			std::cout << i + 1 << "." << cars[i].brands << std::endl;
		}

		std::cout << "Select car: ";
		short int selectC;
		std::cin >> selectC;

		if (selectC > 0 && selectC < 11) {
			std::cout << "Select model: ";
			std::cout << cars[selectC - 1].models[0] << "(1) & " << cars[selectC - 1].models[1] << "(2): ";

			short int selectM;
			std::cin >> selectM;

			if (selectM > 0 && selectM < 3) {
				if (cars[selectC - 1].isTaken[selectM - 1]) {
					cars[selectC - 1].isTaken[selectM - 1] = false;
					std::cout << "Rent Was Successfully Removed!\n";
				}
				else {
					std::cout << "This Car is not full.\n";
				}
			}
			else {
				std::cout << "Invalid Model!\n";
			}
		}
		else {
			std::cout << "Invalid Operation!\n";
		}
	}

	void showStatus(Cars cars[]) {
		std::cout << "\n===== Car Status =====\n";

		for (int i = 0; i < 10; i++) {
			std::cout << cars[i].brands << ": ";

			for (int j = 0; j < 2; j++) {
				std::cout << cars[i].models[j] << "(" << (cars[i].isTaken[j] ? "Taken" : "Free") << ") ";
			}

			std::cout << std::endl;
		}
	}
};

void menu(Car& carObj, Cars cars[]) {
	bool isT = true;

	while (isT) {
		std::cout << "\n===== MENU =====\n";
		std::cout << "1.Rent Car\n2.Cancel Rent\n3.Show Status\n4.Exit\n";

		std::cout << "Select: ";
		short int select;
		std::cin >> select;

		switch (select) {
		case 1:
			carObj.rent(cars);
			break;

		case 2:
			carObj.returnCar(cars);
			break;

		case 3:
			carObj.showStatus(cars);
			break;

		case 4:
			std::cout << "Program is closing...\n";
			isT = false;
			break;

		default:
			std::cout << "Invalid Operation!\n";
		}
	}
}

int main() {
	Car car1;

	Cars cars[10] = {
		{"Toyota", {"Corolla", "Camry"}, {false, false}},
		{"BMW", {"3 Series", "X5"}, {false, false}},
		{"Mercedes", {"C-Class", "E-Class"}, {false, false}},
		{"Audi", {"A4", "Q7"}, {false, false}},
		{"Honda", {"Civic", "Accord"}, {false, false}},
		{"Ford", {"Mustang", "Focus"}, {false, false}},
		{"Chevrolet", {"Malibu", "Camaro"}, {false, false}},
		{"Nissan", {"Altima", "GT-R"}, {false, false}},
		{"Hyundai", {"Elantra", "Tucson"}, {false, false}},
		{"Kia", {"Sportage", "Sorento"}, {false, false}}
	};

	menu(car1, cars);
}