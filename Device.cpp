//#include <iostream>
//
//class Device {
//public:
//    int battery;
//
//    void use(int& battery) {
//        battery -= 20;
//        std::cout << "Charge successfully used.\n";
//    }
//
//    void charge(int& battery) {
//        std::cout << "Current Charge: " << battery << std::endl;
//        std::cout << "Fill Charge: ";
//        int fill;
//        std::cin >> fill;
//
//        if (fill + battery < 101) {
//            battery += fill;
//        }
//        else {
//            std::cout << "Charge cannot be more than 100!\n";
//        }
//    }
//
//    void fullCharge(int& battery) {
//        battery = 100;
//        std::cout << "Charge successfully fulled.\n";
//    }
//};
//
//int main() {
//    Device device;
//    device.battery = 70;
//
//    bool isRunning = true;
//
//    while (isRunning) {
//        std::cout << "\n===== MENU =====\n";
//        std::cout << "1. Use\n";
//        std::cout << "2. Charge\n";
//        std::cout << "3. Full Charge\n";
//        std::cout << "4. Exit\n";
//
//        std::cout << "Select: ";
//        int choice;
//        std::cin >> choice;
//
//        switch (choice) {
//            case 1:
//                device.use(device.battery);
//                break;
//            case 2:
//                device.charge(device.battery);
//                break;
//            case 3:
//                device.fullCharge(device.battery);
//                break;
//            case 4:
//                std::cout << "Program is closing...\n";
//                isRunning = false;
//                break;
//            default:
//                std::cout << "Invalid choice!\n";
//            }
//    }
//
//
//    return 0;
//}