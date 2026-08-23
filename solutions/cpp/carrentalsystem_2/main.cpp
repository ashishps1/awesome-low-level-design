// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Car;
class Customer;
class Rental;
class CarRentalSystem;

// ===== Car.hpp =====
class Car {
private:
    string carId;
    string brand;
    string model;
    double basePrice;
    bool available;

public:
    Car(string carId, string brand, string model, double basePrice);
    
    string getCarId() const;
    string getBrand() const;
    string getModel() const;
    double getBasePrice() const;
    bool isAvailable() const;
    
    void setAvailable(bool status);
    void displayInfo() const;
};

// ===== Customer.hpp =====
class Customer {
private:
    string customerId;
    string name;
    string contactNumber;

public:
    Customer(string customerId, string name, string contactNumber);
    
    string getCustomerId() const;
    string getName() const;
    string getContactNumber() const;
    void displayInfo() const;
};

// ===== Rental.hpp =====
class Rental {
private:
    string rentalId;
    Car* car;
    Customer* customer;
    string startDate;
    int days;
    double totalPrice;

public:
    Rental(string rentalId, Car* car, Customer* customer, 
           string startDate, int days);
    
    string getRentalId() const;
    Car* getCar() const;
    Customer* getCustomer() const;
    string getStartDate() const;
    int getDays() const;
    double getTotalPrice() const;
    
    void displayInfo() const;
};

// ===== CarRentalSystem.hpp =====
class CarRentalSystem {
private:
    vector<Car*> cars;
    vector<Customer*> customers;
    vector<Rental*> rentals;
    int rentalIdCounter;

public:
    CarRentalSystem();
    ~CarRentalSystem();
    
    void addCar(Car* car);
    void addCustomer(Customer* customer);
    string rentCar(Car* car, Customer* customer, string startDate, int days);
    bool returnCar(string rentalId);
    
    void displayAvailableCars() const;
    void displayRentals() const;
    void displayCustomers() const;
    
    Car* findCar(string carId) const;
    Customer* findCustomer(string customerId) const;
    Rental* findRental(string rentalId) const;
};

// ===== Car.cpp =====
Car::Car(string carId, string brand, string model, double basePrice)
    : carId(carId), brand(brand), model(model), basePrice(basePrice), available(true) {}

string Car::getCarId() const { return carId; }
string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
double Car::getBasePrice() const { return basePrice; }
bool Car::isAvailable() const { return available; }

void Car::setAvailable(bool status) {
    available = status;
}

void Car::displayInfo() const {
    cout << "Car ID: " << carId << endl;
    cout << "Brand: " << brand << endl;
    cout << "Model: " << model << endl;
    cout << "Base Price per Day: $" << fixed << setprecision(2) << basePrice << endl;
    cout << "Status: " << (available ? "Available" : "Rented") << endl;
} 

// ===== CarRentalSystem.cpp =====
CarRentalSystem::CarRentalSystem() : rentalIdCounter(1) {}

CarRentalSystem::~CarRentalSystem() {
    for (auto car : cars) delete car;
    for (auto customer : customers) delete customer;
    for (auto rental : rentals) delete rental;
}

void CarRentalSystem::addCar(Car* car) {
    cars.push_back(car);
}

void CarRentalSystem::addCustomer(Customer* customer) {
    customers.push_back(customer);
}

string CarRentalSystem::rentCar(Car* car, Customer* customer, 
                                   string startDate, int days) {
    if (!car->isAvailable()) return "";
    
    string rentalId = "R" + to_string(rentalIdCounter++);
    Rental* rental = new Rental(rentalId, car, customer, startDate, days);
    rentals.push_back(rental);
    car->setAvailable(false);
    return rentalId;
}

bool CarRentalSystem::returnCar(string rentalId) {
    Rental* rental = findRental(rentalId);
    if (!rental) return false;
    
    rental->getCar()->setAvailable(true);
    
    auto it = find(rentals.begin(), rentals.end(), rental);
    if (it != rentals.end()) {
        rentals.erase(it);
        delete rental;
        return true;
    }
    return false;
}

void CarRentalSystem::displayAvailableCars() const {
    cout << "\nAvailable Cars:" << endl;
    for (const auto& car : cars) {
        if (car->isAvailable()) {
            car->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void CarRentalSystem::displayRentals() const {
    cout << "\nCurrent Rentals:" << endl;
    for (const auto& rental : rentals) {
        rental->displayInfo();
        cout << "------------------------" << endl;
    }
}

void CarRentalSystem::displayCustomers() const {
    cout << "\nRegistered Customers:" << endl;
    for (const auto& customer : customers) {
        customer->displayInfo();
        cout << "------------------------" << endl;
    }
}

Car* CarRentalSystem::findCar(string carId) const {
    for (auto car : cars) {
        if (car->getCarId() == carId) return car;
    }
    return nullptr;
}

Customer* CarRentalSystem::findCustomer(string customerId) const {
    for (auto customer : customers) {
        if (customer->getCustomerId() == customerId) return customer;
    }
    return nullptr;
}

Rental* CarRentalSystem::findRental(string rentalId) const {
    for (auto rental : rentals) {
        if (rental->getRentalId() == rentalId) return rental;
    }
    return nullptr;
} 

// ===== Customer.cpp =====
Customer::Customer(string customerId, string name, string contactNumber)
    : customerId(customerId), name(name), contactNumber(contactNumber) {}

string Customer::getCustomerId() const { return customerId; }
string Customer::getName() const { return name; }
string Customer::getContactNumber() const { return contactNumber; }

void Customer::displayInfo() const {
    cout << "Customer ID: " << customerId << endl;
    cout << "Name: " << name << endl;
    cout << "Contact Number: " << contactNumber << endl;
} 

// ===== Rental.cpp =====
Rental::Rental(string rentalId, Car* car, Customer* customer, 
               string startDate, int days)
    : rentalId(rentalId), car(car), customer(customer), 
      startDate(startDate), days(days) {
    totalPrice = car->getBasePrice() * days;
}

string Rental::getRentalId() const { return rentalId; }
Car* Rental::getCar() const { return car; }
Customer* Rental::getCustomer() const { return customer; }
string Rental::getStartDate() const { return startDate; }
int Rental::getDays() const { return days; }
double Rental::getTotalPrice() const { return totalPrice; }

void Rental::displayInfo() const {
    cout << "\nRental Details:" << endl;
    cout << "Rental ID: " << rentalId << endl;
    cout << "Start Date: " << startDate << endl;
    cout << "Duration: " << days << " days" << endl;
    cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;
    cout << "\nCustomer Information:" << endl;
    customer->displayInfo();
    cout << "\nCar Information:" << endl;
    car->displayInfo();
} 

// ===== CarRentalSystemDemo.cpp =====
int main() {
    CarRentalSystem rentalSystem;
    
    // Add some cars
    Car* car1 = new Car("C001", "Toyota", "Camry", 60.0);
    Car* car2 = new Car("C002", "Honda", "Accord", 70.0);
    Car* car3 = new Car("C003", "BMW", "3 Series", 100.0);
    
    rentalSystem.addCar(car1);
    rentalSystem.addCar(car2);
    rentalSystem.addCar(car3);
    
    // Add some customers
    Customer* customer1 = new Customer("CUST001", "John Doe", "+1-555-0123");
    Customer* customer2 = new Customer("CUST002", "Jane Smith", "+1-555-0124");
    
    rentalSystem.addCustomer(customer1);
    rentalSystem.addCustomer(customer2);
    
    // Display available cars
    rentalSystem.displayAvailableCars();
    
    // Rent some cars
    string rental1 = rentalSystem.rentCar(car1, customer1, "2024-03-20", 3);
    string rental2 = rentalSystem.rentCar(car2, customer2, "2024-03-21", 5);
    
    if (!rental1.empty()) {
        cout << "\nRental created successfully: " << rental1 << endl;
    }
    if (!rental2.empty()) {
        cout << "Rental created successfully: " << rental2 << endl;
    }
    
    // Display all rentals
    rentalSystem.displayRentals();
    
    // Display available cars after rentals
    rentalSystem.displayAvailableCars();
    
    // Return a car
    if (rentalSystem.returnCar(rental1)) {
        cout << "\nCar returned successfully for rental: " << rental1 << endl;
    }
    
    // Display available cars after return
    rentalSystem.displayAvailableCars();
    
    return 0;
} 

