#ifndef CAR_HPP
#define CAR_HPP

#include <string>

class Car {
private:
    std::string carId;
    std::string brand;
    std::string model;
    double basePrice;
    bool available;

public:
    Car(std::string carId, std::string brand, std::string model, double basePrice);
    
    std::string getCarId() const;
    std::string getBrand() const;
    std::string getModel() const;
    double getBasePrice() const;
    bool isAvailable() const;
    
    void setAvailable(bool status);
    void displayInfo() const;
};

#endif 