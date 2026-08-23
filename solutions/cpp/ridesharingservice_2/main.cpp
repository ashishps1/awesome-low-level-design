// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Location;
class User;
class Ride;
class RideService;

// ===== Location.hpp =====
class Location {
private:
    double latitude;
    double longitude;
    string address;

public:
    Location(double latitude, double longitude, string address);
    
    double getLatitude() const;
    double getLongitude() const;
    string getAddress() const;
    
    double calculateDistance(const Location& other) const;
    void displayInfo() const;
};

// ===== User.hpp =====
enum class UserType {
    RIDER,
    DRIVER
};

class User {
private:
    string userId;
    string name;
    string phone;
    UserType type;
    Location* currentLocation;
    bool active;
    double rating;
    int totalRatings;

public:
    User(string userId, string name, string phone, UserType type,
         Location* location);
    ~User();
    
    string getUserId() const;
    string getName() const;
    string getPhone() const;
    UserType getType() const;
    Location* getCurrentLocation() const;
    bool isActive() const;
    double getRating() const;
    
    void updateLocation(Location* location);
    void setActive(bool status);
    void updateRating(double newRating);
    void displayInfo() const;
};

// ===== Ride.hpp =====
enum class RideStatus {
    REQUESTED,
    ACCEPTED,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

class Ride {
private:
    string rideId;
    User* rider;
    User* driver;
    Location* pickup;
    Location* dropoff;
    double distance;
    double fare;
    time_t requestTime;
    time_t completionTime;
    RideStatus status;

public:
    Ride(string rideId, User* rider, Location* pickup, Location* dropoff);
    ~Ride();
    
    string getRideId() const;
    User* getRider() const;
    User* getDriver() const;
    Location* getPickup() const;
    Location* getDropoff() const;
    double getDistance() const;
    double getFare() const;
    time_t getRequestTime() const;
    time_t getCompletionTime() const;
    RideStatus getStatus() const;
    
    void assignDriver(User* driver);
    void calculateFare();
    void updateStatus(RideStatus status);
    void displayInfo() const;
};

// ===== RideService.hpp =====
class RideService {
private:
    vector<User*> users;
    vector<Ride*> rides;
    int userIdCounter;
    int rideIdCounter;

public:
    RideService();
    ~RideService();
    
    User* registerUser(const string& name, const string& phone,
                      UserType type, Location* location);
    void removeUser(const string& userId);
    
    Ride* requestRide(const string& riderId, Location* pickup, Location* dropoff);
    bool assignDriver(const string& rideId, const string& driverId);
    bool updateRideStatus(const string& rideId, RideStatus status);
    bool rateUser(const string& userId, double rating);
    
    void displayUsers() const;
    void displayRides() const;
    void displayUserHistory(const string& userId) const;

private:
    User* findUser(const string& userId) const;
    Ride* findRide(const string& rideId) const;
    User* findNearestDriver(const Location& pickup) const;
    string generateUserId();
    string generateRideId();
};

// ===== Location.cpp =====
Location::Location(double latitude, double longitude, string address)
    : latitude(latitude), longitude(longitude), address(address) {}

double Location::getLatitude() const { return latitude; }
double Location::getLongitude() const { return longitude; }
string Location::getAddress() const { return address; }

double Location::calculateDistance(const Location& other) const {
    // Simple Euclidean distance for demonstration
    double dx = latitude - other.latitude;
    double dy = longitude - other.longitude;
    return sqrt(dx * dx + dy * dy);
}

void Location::displayInfo() const {
    cout << "Location: " << address << endl;
    cout << "Coordinates: (" << latitude << ", " << longitude << ")" << endl;
} 

// ===== Ride.cpp =====
Ride::Ride(string rideId, User* rider, Location* pickup, Location* dropoff)
    : rideId(rideId), rider(rider), driver(nullptr), pickup(pickup), dropoff(dropoff),
      distance(0.0), fare(0.0), status(RideStatus::REQUESTED) {
    requestTime = time(nullptr);
    completionTime = 0;
    distance = pickup->calculateDistance(*dropoff);
}

Ride::~Ride() {
    delete pickup;
    delete dropoff;
}

string Ride::getRideId() const { return rideId; }
User* Ride::getRider() const { return rider; }
User* Ride::getDriver() const { return driver; }
Location* Ride::getPickup() const { return pickup; }
Location* Ride::getDropoff() const { return dropoff; }
double Ride::getDistance() const { return distance; }
double Ride::getFare() const { return fare; }
time_t Ride::getRequestTime() const { return requestTime; }
time_t Ride::getCompletionTime() const { return completionTime; }
RideStatus Ride::getStatus() const { return status; }

void Ride::assignDriver(User* driver) {
    if (driver && driver->getType() == UserType::DRIVER) {
        this->driver = driver;
        status = RideStatus::ACCEPTED;
    }
}

void Ride::calculateFare() {
    // Simple fare calculation: base fare + distance-based fare
    const double BASE_FARE = 5.0;
    const double RATE_PER_KM = 2.0;
    fare = BASE_FARE + (distance * RATE_PER_KM);
}

void Ride::updateStatus(RideStatus status) {
    this->status = status;
    if (status == RideStatus::COMPLETED) {
        completionTime = time(nullptr);
        calculateFare();
    }
}

void Ride::displayInfo() const {
    cout << "\nRide Details:" << endl;
    cout << "ID: " << rideId << endl;
    cout << "Rider: " << rider->getName() << endl;
    if (driver) {
        cout << "Driver: " << driver->getName() << endl;
    }
    cout << "Status: ";
    switch (status) {
        case RideStatus::REQUESTED: cout << "Requested"; break;
        case RideStatus::ACCEPTED: cout << "Accepted"; break;
        case RideStatus::IN_PROGRESS: cout << "In Progress"; break;
        case RideStatus::COMPLETED: cout << "Completed"; break;
        case RideStatus::CANCELLED: cout << "Cancelled"; break;
    }
    cout << endl;
    
    cout << "Pickup: " << pickup->getAddress() << endl;
    cout << "Dropoff: " << dropoff->getAddress() << endl;
    cout << "Distance: " << fixed << setprecision(2) << distance << " km" << endl;
    
    if (status == RideStatus::COMPLETED) {
        cout << "Fare: $" << fixed << setprecision(2) << fare << endl;
        cout << "Request Time: " << ctime(&requestTime);
        cout << "Completion Time: " << ctime(&completionTime);
    }
} 

// ===== RideService.cpp =====
RideService::RideService() : userIdCounter(1), rideIdCounter(1) {}

RideService::~RideService() {
    for (auto user : users) delete user;
    for (auto ride : rides) delete ride;
}

User* RideService::registerUser(const string& name, const string& phone,
                              UserType type, Location* location) {
    string userId = generateUserId();
    User* user = new User(userId, name, phone, type, location);
    users.push_back(user);
    return user;
}

void RideService::removeUser(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
    }
}

Ride* RideService::requestRide(const string& riderId, Location* pickup, Location* dropoff) {
    User* rider = findUser(riderId);
    if (!rider || rider->getType() != UserType::RIDER) return nullptr;
    
    string rideId = generateRideId();
    Ride* ride = new Ride(rideId, rider, pickup, dropoff);
    rides.push_back(ride);
    
    // Try to find and assign nearest driver
    User* driver = findNearestDriver(*pickup);
    if (driver) {
        ride->assignDriver(driver);
    }
    
    return ride;
}

bool RideService::assignDriver(const string& rideId, const string& driverId) {
    Ride* ride = findRide(rideId);
    User* driver = findUser(driverId);
    
    if (!ride || !driver || driver->getType() != UserType::DRIVER) return false;
    
    ride->assignDriver(driver);
    return true;
}

bool RideService::updateRideStatus(const string& rideId, RideStatus status) {
    Ride* ride = findRide(rideId);
    if (!ride) return false;
    
    ride->updateStatus(status);
    return true;
}

bool RideService::rateUser(const string& userId, double rating) {
    User* user = findUser(userId);
    if (!user) return false;
    
    user->updateRating(rating);
    return true;
}

void RideService::displayUsers() const {
    cout << "\n=== Registered Users ===" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

void RideService::displayRides() const {
    cout << "\n=== All Rides ===" << endl;
    for (const auto& ride : rides) {
        ride->displayInfo();
    }
}

void RideService::displayUserHistory(const string& userId) const {
    cout << "\n=== Ride History for User " << userId << " ===" << endl;
    for (const auto& ride : rides) {
        if ((ride->getRider()->getUserId() == userId) ||
            (ride->getDriver() && ride->getDriver()->getUserId() == userId)) {
            ride->displayInfo();
        }
    }
}

User* RideService::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Ride* RideService::findRide(const string& rideId) const {
    auto it = find_if(rides.begin(), rides.end(),
        [rideId](Ride* ride) { return ride->getRideId() == rideId; });
    return it != rides.end() ? *it : nullptr;
}

User* RideService::findNearestDriver(const Location& pickup) const {
    User* nearestDriver = nullptr;
    double minDistance = numeric_limits<double>::max();
    
    for (auto user : users) {
        if (user->getType() == UserType::DRIVER && user->isActive()) {
            double distance = pickup.calculateDistance(*user->getCurrentLocation());
            if (distance < minDistance) {
                minDistance = distance;
                nearestDriver = user;
            }
        }
    }
    
    return nearestDriver;
}

string RideService::generateUserId() {
    return "U" + to_string(userIdCounter++);
}

string RideService::generateRideId() {
    return "R" + to_string(rideIdCounter++);
} 

// ===== User.cpp =====
User::User(string userId, string name, string phone, UserType type,
           Location* location)
    : userId(userId), name(name), phone(phone), type(type),
      currentLocation(location), active(true), rating(5.0), totalRatings(0) {}

User::~User() {
    delete currentLocation;
}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getPhone() const { return phone; }
UserType User::getType() const { return type; }
Location* User::getCurrentLocation() const { return currentLocation; }
bool User::isActive() const { return active; }
double User::getRating() const { return rating; }

void User::updateLocation(Location* location) {
    delete currentLocation;
    currentLocation = location;
}

void User::setActive(bool status) {
    active = status;
}

void User::updateRating(double newRating) {
    if (newRating >= 1.0 && newRating <= 5.0) {
        rating = ((rating * totalRatings) + newRating) / (totalRatings + 1);
        totalRatings++;
    }
}

void User::displayInfo() const {
    cout << "User: " << name << " (ID: " << userId << ")" << endl;
    cout << "Type: " << (type == UserType::RIDER ? "Rider" : "Driver") << endl;
    cout << "Phone: " << phone << endl;
    cout << "Rating: " << fixed << setprecision(1) << rating << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    if (currentLocation) {
        currentLocation->displayInfo();
    }
} 

// ===== RideDemo.cpp =====
int main() {
    RideService service;
    
    // Register users
    User* rider1 = service.registerUser("John", "123-456-7890", UserType::RIDER,
        new Location(40.7128, -74.0060, "New York City"));
    
    User* rider2 = service.registerUser("Alice", "123-456-7891", UserType::RIDER,
        new Location(34.0522, -118.2437, "Los Angeles"));
    
    User* driver1 = service.registerUser("Bob", "123-456-7892", UserType::DRIVER,
        new Location(40.7300, -74.0100, "Near NYC"));
    
    User* driver2 = service.registerUser("Carol", "123-456-7893", UserType::DRIVER,
        new Location(34.0500, -118.2400, "Near LA"));
    
    cout << "Initial users:" << endl;
    service.displayUsers();
    
    // Request rides
    Location* pickup1 = new Location(40.7128, -74.0060, "NYC Downtown");
    Location* dropoff1 = new Location(40.7589, -73.9851, "Central Park");
    
    cout << "\nRequesting ride..." << endl;
    Ride* ride1 = service.requestRide(rider1->getUserId(), pickup1, dropoff1);
    
    if (ride1) {
        cout << "Ride requested successfully:" << endl;
        ride1->displayInfo();
        
        // Update ride status
        cout << "\nUpdating ride status..." << endl;
        service.updateRideStatus(ride1->getRideId(), RideStatus::IN_PROGRESS);
        this_thread::sleep_for(chrono::seconds(1));
        
        service.updateRideStatus(ride1->getRideId(), RideStatus::COMPLETED);
        
        // Rate users
        cout << "\nRating users..." << endl;
        service.rateUser(ride1->getDriver()->getUserId(), 5.0);  // Rate driver
        service.rateUser(ride1->getRider()->getUserId(), 4.5);   // Rate rider
    }
    
    // Display final status
    cout << "\nFinal user status:" << endl;
    service.displayUsers();
    
    cout << "\nRide history:" << endl;
    service.displayRides();
    
    return 0;
} 

