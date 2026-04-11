//#include <iostream>
//
//class Taxi {
//public:
//    float baseFare;
//    float perKm;
//
//    float calculateFare(float distance) {
//        float fare = baseFare + (perKm * distance);
//
//        if (fare < 3.0) {
//            fare = 3.0;
//        }
//
//        return fare;
//    }
//};
//
//int main() {
//    Taxi TakeTaxi;
//    TakeTaxi.baseFare = 5.3;
//    TakeTaxi.perKm = 3.8;
//
//    float distance = 1.0;
//
//    std::cout << "Fare: " << TakeTaxi.calculateFare(distance) << " AZN";
//
//    return 0;
//}