// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Seat;
class Flight;
class Passenger;
class Booking;
class AirlineManagementSystem;

// ===== Seat.hpp =====
class Seat {
private:
    int seatNumber;
    bool booked;

public:
    Seat(int number, bool isBooked = false);
    
    int getSeatNumber() const;
    bool isBooked() const;
    void book();
    void cancel();
};

// ===== Flight.hpp =====
class Flight {
private:
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
    int capacity;
    vector<Seat> seats;

public:
    Flight(string flightNumber, string origin, string destination, 
           string departureTime, int capacity);
    
    string getFlightNumber() const;
    string getOrigin() const;
    string getDestination() const;
    string getDepartureTime() const;
    int getCapacity() const;
    vector<Seat>& getSeats();
    
    void displayFlightInfo() const;
    bool bookSeat(int seatNumber);
    bool cancelSeat(int seatNumber);
};

// ===== Passenger.hpp =====
class Passenger {
private:
    string name;
    string passportNumber;
    string contactNumber;

public:
    Passenger(string name, string passportNumber, string contactNumber);
    
    string getName() const;
    string getPassportNumber() const;
    string getContactNumber() const;
    void displayInfo() const;
};

// ===== Booking.hpp =====
class Booking {
    
private:
    string bookingId;
    Flight* flight;
    Passenger* passenger;
    int seatNumber;

public:
    Booking(string bookingId, Flight* flight, Passenger* passenger, int seatNumber);
    
    string getBookingId() const;
    Flight* getFlight() const;
    Passenger* getPassenger() const;
    int getSeatNumber() const;
    void displayBookingInfo() const;
};

// ===== AirlineManagementSystem.hpp =====
class AirlineManagementSystem {
private:
    vector<Flight*> flights;
    vector<Passenger*> passengers;
    vector<Booking*> bookings;
    int bookingIdCounter;

public:
    AirlineManagementSystem();
    ~AirlineManagementSystem();
    
    void addFlight(Flight* flight);
    void addPassenger(Passenger* passenger);
    string createBooking(Flight* flight, Passenger* passenger, int seatNumber);
    bool cancelBooking(string bookingId);
    
    void displayAllFlights() const;
    void displayAllPassengers() const;
    void displayAllBookings() const;
    
    Flight* findFlight(string flightNumber) const;
    Passenger* findPassenger(string passportNumber) const;
    Booking* findBooking(string bookingId) const;
};

// ===== AirlineManagementSystem.cpp =====
AirlineManagementSystem::AirlineManagementSystem() : bookingIdCounter(1) {}

AirlineManagementSystem::~AirlineManagementSystem() {
    for (auto flight : flights) delete flight;
    for (auto passenger : passengers) delete passenger;
    for (auto booking : bookings) delete booking;
}

void AirlineManagementSystem::addFlight(Flight* flight) {
    flights.push_back(flight);
}

void AirlineManagementSystem::addPassenger(Passenger* passenger) {
    passengers.push_back(passenger);
}

string AirlineManagementSystem::createBooking(Flight* flight, Passenger* passenger, int seatNumber) {
    if (!flight->bookSeat(seatNumber)) {
        return "";
    }
    
    string bookingId = "B" + to_string(bookingIdCounter++);
    Booking* booking = new Booking(bookingId, flight, passenger, seatNumber);
    bookings.push_back(booking);
    return bookingId;
}

bool AirlineManagementSystem::cancelBooking(string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking) return false;
    
    booking->getFlight()->cancelSeat(booking->getSeatNumber());
    
    auto it = find(bookings.begin(), bookings.end(), booking);
    if (it != bookings.end()) {
        bookings.erase(it);
        delete booking;
        return true;
    }
    return false;
}

void AirlineManagementSystem::displayAllFlights() const {
    cout << "\nAll Flights:" << endl;
    for (const auto& flight : flights) {
        flight->displayFlightInfo();
        cout << "------------------------" << endl;
    }
}

void AirlineManagementSystem::displayAllPassengers() const {
    cout << "\nAll Passengers:" << endl;
    for (const auto& passenger : passengers) {
        passenger->displayInfo();
        cout << "------------------------" << endl;
    }
}

void AirlineManagementSystem::displayAllBookings() const {
    cout << "\nAll Bookings:" << endl;
    for (const auto& booking : bookings) {
        booking->displayBookingInfo();
        cout << "------------------------" << endl;
    }
}

Flight* AirlineManagementSystem::findFlight(string flightNumber) const {
    for (auto flight : flights) {
        if (flight->getFlightNumber() == flightNumber) return flight;
    }
    return nullptr;
}

Passenger* AirlineManagementSystem::findPassenger(string passportNumber) const {
    for (auto passenger : passengers) {
        if (passenger->getPassportNumber() == passportNumber) return passenger;
    }
    return nullptr;
}

Booking* AirlineManagementSystem::findBooking(string bookingId) const {
    for (auto booking : bookings) {
        if (booking->getBookingId() == bookingId) return booking;
    }
    return nullptr;
} 

// ===== Booking.cpp =====
Booking::Booking(string bookingId, Flight* flight, Passenger* passenger, int seatNumber)
    : bookingId(bookingId), flight(flight), passenger(passenger), seatNumber(seatNumber) {}

string Booking::getBookingId() const { return bookingId; }
Flight* Booking::getFlight() const { return flight; }
Passenger* Booking::getPassenger() const { return passenger; }
int Booking::getSeatNumber() const { return seatNumber; }

void Booking::displayBookingInfo() const {
    cout << "\nBooking Details:" << endl;
    cout << "Booking ID: " << bookingId << endl;
    cout << "Seat Number: " << seatNumber << endl;
    passenger->displayInfo();
    flight->displayFlightInfo();
} 

// ===== Flight.cpp =====
Flight::Flight(string flightNumber, string origin, string destination, 
               string departureTime, int capacity) 
    : flightNumber(flightNumber), origin(origin), destination(destination),
      departureTime(departureTime), capacity(capacity) {
    
    // Initialize seats
    for (int i = 1; i <= capacity; i++) {
        seats.push_back(Seat(i, false));
    }
}

string Flight::getFlightNumber() const { return flightNumber; }
string Flight::getOrigin() const { return origin; }
string Flight::getDestination() const { return destination; }
string Flight::getDepartureTime() const { return departureTime; }
int Flight::getCapacity() const { return capacity; }
vector<Seat>& Flight::getSeats() { return seats; }

void Flight::displayFlightInfo() const {
    cout << "Flight " << flightNumber << endl;
    cout << "From: " << origin << " To: " << destination << endl;
    cout << "Departure Time: " << departureTime << endl;
    cout << "Capacity: " << capacity << " seats" << endl;
}

bool Flight::bookSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > capacity) return false;
    if (seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].book();
    return true;
}

bool Flight::cancelSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > capacity) return false;
    if (!seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].cancel();
    return true;
} 

// ===== Passenger.cpp =====
Passenger::Passenger(string name, string passportNumber, string contactNumber)
    : name(name), passportNumber(passportNumber), contactNumber(contactNumber) {}

string Passenger::getName() const { return name; }
string Passenger::getPassportNumber() const { return passportNumber; }
string Passenger::getContactNumber() const { return contactNumber; }

void Passenger::displayInfo() const {
    cout << "Passenger Details:" << endl;
    cout << "Name: " << name << endl;
    cout << "Passport Number: " << passportNumber << endl;
    cout << "Contact Number: " << contactNumber << endl;
} 

// ===== Seat.cpp =====
Seat::Seat(int number, bool isBooked) 
    : seatNumber(number), booked(isBooked) {}

int Seat::getSeatNumber() const { return seatNumber; }
bool Seat::isBooked() const { return booked; }
void Seat::book() { booked = true; }
void Seat::cancel() { booked = false; } 

// ===== AirlineManagementSystemDemo.cpp =====
int main() {
    AirlineManagementSystem ams;
    
    // Create flights
    Flight* flight1 = new Flight("FL001", "New York", "London", "2024-03-20 10:00", 100);
    Flight* flight2 = new Flight("FL002", "London", "Paris", "2024-03-21 15:30", 80);
    ams.addFlight(flight1);
    ams.addFlight(flight2);
    
    // Create passengers
    Passenger* passenger1 = new Passenger("John Doe", "P123456", "+1-555-0123");
    Passenger* passenger2 = new Passenger("Jane Smith", "P789012", "+1-555-0124");
    ams.addPassenger(passenger1);
    ams.addPassenger(passenger2);
    
    // Display all flights and passengers
    ams.displayAllFlights();
    ams.displayAllPassengers();
    
    // Create bookings
    string booking1 = ams.createBooking(flight1, passenger1, 1);
    string booking2 = ams.createBooking(flight2, passenger2, 1);
    
    if (!booking1.empty()) {
        cout << "\nBooking created successfully: " << booking1 << endl;
    }
    if (!booking2.empty()) {
        cout << "Booking created successfully: " << booking2 << endl;
    }
    
    // Display all bookings
    ams.displayAllBookings();
    
    // Cancel a booking
    if (ams.cancelBooking(booking1)) {
        cout << "\nBooking " << booking1 << " cancelled successfully" << endl;
    }
    
    // Display updated bookings
    ams.displayAllBookings();
    
    return 0;
} 

