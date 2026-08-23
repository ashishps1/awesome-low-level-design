// Ride-Sharing Service — single translation unit (no header files).
//
// Everything (declarations + definitions) lives in this one .cpp file, in
// dependency order: a type is fully defined before anything that uses it.
// Because there is only ONE translation unit, no headers are needed and the
// One Definition Rule is never violated.
//
// Build & run:
//   g++ -std=c++17 main.cpp -o ride && ./ride

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

// ============================================================================
// Location
// ============================================================================
class Location {
private:
    double latitude;
    double longitude;
    string address;

public:
    Location(double latitude, double longitude, string address)
        : latitude(latitude), longitude(longitude), address(address) {}

    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    string getAddress() const { return address; }

    double calculateDistance(const Location& other) const {
        // Simple Euclidean distance for demonstration.
        double dx = latitude - other.latitude;
        double dy = longitude - other.longitude;
        return sqrt(dx * dx + dy * dy);
    }

    void displayInfo() const {
        cout << "Location: " << address << endl;
        cout << "Coordinates: (" << latitude << ", " << longitude << ")" << endl;
    }
};

// ============================================================================
// User
// ============================================================================
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
         Location* location)
        : userId(userId), name(name), phone(phone), type(type),
          currentLocation(location), active(true), rating(5.0), totalRatings(0) {}

    ~User() {
        delete currentLocation;
    }

    string getUserId() const { return userId; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    UserType getType() const { return type; }
    Location* getCurrentLocation() const { return currentLocation; }
    bool isActive() const { return active; }
    double getRating() const { return rating; }

    void updateLocation(Location* location) {
        delete currentLocation;
        currentLocation = location;
    }

    void setActive(bool status) {
        active = status;
    }

    void updateRating(double newRating) {
        if (newRating >= 1.0 && newRating <= 5.0) {
            rating = ((rating * totalRatings) + newRating) / (totalRatings + 1);
            totalRatings++;
        }
    }

    void displayInfo() const {
        cout << "User: " << name << " (ID: " << userId << ")" << endl;
        cout << "Type: " << (type == UserType::RIDER ? "Rider" : "Driver") << endl;
        cout << "Phone: " << phone << endl;
        cout << "Rating: " << fixed << setprecision(1) << rating << endl;
        cout << "Status: " << (active ? "Active" : "Inactive") << endl;
        if (currentLocation) {
            currentLocation->displayInfo();
        }
    }
};

// ============================================================================
// Ride
// ============================================================================
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
    Ride(string rideId, User* rider, Location* pickup, Location* dropoff)
        : rideId(rideId), rider(rider), driver(nullptr), pickup(pickup), dropoff(dropoff),
          distance(0.0), fare(0.0), status(RideStatus::REQUESTED) {
        requestTime = time(nullptr);
        completionTime = 0;
        distance = pickup->calculateDistance(*dropoff);
    }

    ~Ride() {
        delete pickup;
        delete dropoff;
    }

    string getRideId() const { return rideId; }
    User* getRider() const { return rider; }
    User* getDriver() const { return driver; }
    Location* getPickup() const { return pickup; }
    Location* getDropoff() const { return dropoff; }
    double getDistance() const { return distance; }
    double getFare() const { return fare; }
    time_t getRequestTime() const { return requestTime; }
    time_t getCompletionTime() const { return completionTime; }
    RideStatus getStatus() const { return status; }

    void assignDriver(User* driver) {
        if (driver && driver->getType() == UserType::DRIVER) {
            this->driver = driver;
            status = RideStatus::ACCEPTED;
        }
    }

    void calculateFare() {
        // Simple fare calculation: base fare + distance-based fare.
        const double BASE_FARE = 5.0;
        const double RATE_PER_KM = 2.0;
        fare = BASE_FARE + (distance * RATE_PER_KM);
    }

    void updateStatus(RideStatus status) {
        this->status = status;
        if (status == RideStatus::COMPLETED) {
            completionTime = time(nullptr);
            calculateFare();
        }
    }

    void displayInfo() const {
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
};

// ============================================================================
// RideService  (facade / orchestrator)
// ============================================================================
class RideService {
private:
    vector<User*> users;
    vector<Ride*> rides;
    int userIdCounter;
    int rideIdCounter;

    User* findUser(const string& userId) const {
        auto it = find_if(users.begin(), users.end(),
            [userId](User* user) { return user->getUserId() == userId; });
        return it != users.end() ? *it : nullptr;
    }

    Ride* findRide(const string& rideId) const {
        auto it = find_if(rides.begin(), rides.end(),
            [rideId](Ride* ride) { return ride->getRideId() == rideId; });
        return it != rides.end() ? *it : nullptr;
    }

    User* findNearestDriver(const Location& pickup) const {
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

    string generateUserId() { return "U" + to_string(userIdCounter++); }
    string generateRideId() { return "R" + to_string(rideIdCounter++); }

public:
    RideService() : userIdCounter(1), rideIdCounter(1) {}

    ~RideService() {
        for (auto user : users) delete user;
        for (auto ride : rides) delete ride;
    }

    User* registerUser(const string& name, const string& phone,
                       UserType type, Location* location) {
        string userId = generateUserId();
        User* user = new User(userId, name, phone, type, location);
        users.push_back(user);
        return user;
    }

    void removeUser(const string& userId) {
        auto it = find_if(users.begin(), users.end(),
            [userId](User* user) { return user->getUserId() == userId; });
        if (it != users.end()) {
            delete *it;
            users.erase(it);
        }
    }

    Ride* requestRide(const string& riderId, Location* pickup, Location* dropoff) {
        User* rider = findUser(riderId);
        if (!rider || rider->getType() != UserType::RIDER) return nullptr;

        string rideId = generateRideId();
        Ride* ride = new Ride(rideId, rider, pickup, dropoff);
        rides.push_back(ride);

        // Try to find and assign nearest driver.
        User* driver = findNearestDriver(*pickup);
        if (driver) {
            ride->assignDriver(driver);
        }
        return ride;
    }

    bool assignDriver(const string& rideId, const string& driverId) {
        Ride* ride = findRide(rideId);
        User* driver = findUser(driverId);
        if (!ride || !driver || driver->getType() != UserType::DRIVER) return false;
        ride->assignDriver(driver);
        return true;
    }

    bool updateRideStatus(const string& rideId, RideStatus status) {
        Ride* ride = findRide(rideId);
        if (!ride) return false;
        ride->updateStatus(status);
        return true;
    }

    bool rateUser(const string& userId, double rating) {
        User* user = findUser(userId);
        if (!user) return false;
        user->updateRating(rating);
        return true;
    }

    void displayUsers() const {
        cout << "\n=== Registered Users ===" << endl;
        for (const auto& user : users) {
            user->displayInfo();
            cout << "------------------------" << endl;
        }
    }

    void displayRides() const {
        cout << "\n=== All Rides ===" << endl;
        for (const auto& ride : rides) {
            ride->displayInfo();
        }
    }

    void displayUserHistory(const string& userId) const {
        cout << "\n=== Ride History for User " << userId << " ===" << endl;
        for (const auto& ride : rides) {
            if ((ride->getRider()->getUserId() == userId) ||
                (ride->getDriver() && ride->getDriver()->getUserId() == userId)) {
                ride->displayInfo();
            }
        }
    }
};

// ============================================================================
// Demo
// ============================================================================
int main() {
    RideService service;

    // Register users.
    User* rider1 = service.registerUser("John", "123-456-7890", UserType::RIDER,
        new Location(40.7128, -74.0060, "New York City"));

    service.registerUser("Alice", "123-456-7891", UserType::RIDER,
        new Location(34.0522, -118.2437, "Los Angeles"));

    service.registerUser("Bob", "123-456-7892", UserType::DRIVER,
        new Location(40.7300, -74.0100, "Near NYC"));

    service.registerUser("Carol", "123-456-7893", UserType::DRIVER,
        new Location(34.0500, -118.2400, "Near LA"));

    cout << "Initial users:" << endl;
    service.displayUsers();

    // Request a ride.
    Location* pickup1 = new Location(40.7128, -74.0060, "NYC Downtown");
    Location* dropoff1 = new Location(40.7589, -73.9851, "Central Park");

    cout << "\nRequesting ride..." << endl;
    Ride* ride1 = service.requestRide(rider1->getUserId(), pickup1, dropoff1);

    if (ride1) {
        cout << "Ride requested successfully:" << endl;
        ride1->displayInfo();

        // Update ride status.
        cout << "\nUpdating ride status..." << endl;
        service.updateRideStatus(ride1->getRideId(), RideStatus::IN_PROGRESS);
        this_thread::sleep_for(chrono::seconds(1));

        service.updateRideStatus(ride1->getRideId(), RideStatus::COMPLETED);

        // Rate users.
        cout << "\nRating users..." << endl;
        service.rateUser(ride1->getDriver()->getUserId(), 5.0);  // Rate driver.
        service.rateUser(ride1->getRider()->getUserId(), 4.5);   // Rate rider.
    }

    // Display final status.
    cout << "\nFinal user status:" << endl;
    service.displayUsers();

    cout << "\nRide history:" << endl;
    service.displayRides();

    return 0;
}
