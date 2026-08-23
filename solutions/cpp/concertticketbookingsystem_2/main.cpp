// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Seat;
class Concert;
class Booking;
class BookingSystem;

// ===== Seat.hpp =====
class Seat {
private:
    int seatNumber;
    bool booked;

public:
    Seat(int number);
    
    int getSeatNumber() const;
    bool isBooked() const;
    void book();
    void cancel();
};

// ===== Concert.hpp =====
class Concert {
private:
    string concertId;
    string name;
    string venue;
    string date;
    double basePrice;
    vector<Seat> seats;
    int totalSeats;

public:
    Concert(string concertId, string name, string venue, 
            string date, double basePrice, int totalSeats);
    
    string getConcertId() const;
    string getName() const;
    string getVenue() const;
    string getDate() const;
    double getBasePrice() const;
    int getTotalSeats() const;
    int getAvailableSeats() const;
    
    bool bookSeat(int seatNumber);
    bool cancelSeat(int seatNumber);
    bool isSeatAvailable(int seatNumber) const;
    void displayInfo() const;
};

// ===== Booking.hpp =====
class Booking {
private:
    string bookingId;
    string customerName;
    Concert* concert;
    int seatNumber;
    double totalPrice;

public:
    Booking(string bookingId, string customerName, Concert* concert, 
            int seatNumber, double totalPrice);
    
    string getBookingId() const;
    string getCustomerName() const;
    Concert* getConcert() const;
    int getSeatNumber() const;
    double getTotalPrice() const;
    void displayInfo() const;
};

// ===== BookingSystem.hpp =====
class BookingSystem {
private:
    vector<Concert*> concerts;
    vector<Booking*> bookings;
    int bookingIdCounter;

public:
    BookingSystem();
    ~BookingSystem();
    
    void addConcert(Concert* concert);
    string createBooking(string customerName, Concert* concert, int seatNumber);
    bool cancelBooking(string bookingId);
    
    void displayAllConcerts() const;
    void displayAllBookings() const;
    void displayAvailableSeats(Concert* concert) const;
    
    Concert* findConcert(string concertId) const;
    Booking* findBooking(string bookingId) const;
};

// ===== Booking.cpp =====
Booking::Booking(string bookingId, string customerName, Concert* concert, 
                int seatNumber, double totalPrice)
    : bookingId(bookingId), customerName(customerName), concert(concert), 
      seatNumber(seatNumber), totalPrice(totalPrice) {}

string Booking::getBookingId() const { return bookingId; }
string Booking::getCustomerName() const { return customerName; }
Concert* Booking::getConcert() const { return concert; }
int Booking::getSeatNumber() const { return seatNumber; }
double Booking::getTotalPrice() const { return totalPrice; }

void Booking::displayInfo() const {
    cout << "\nBooking Details:" << endl;
    cout << "Booking ID: " << bookingId << endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Seat Number: " << seatNumber << endl;
    cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;
    cout << "\nConcert Information:" << endl;
    concert->displayInfo();
} 

// ===== BookingSystem.cpp =====
BookingSystem::BookingSystem() : bookingIdCounter(1) {}

BookingSystem::~BookingSystem() {
    for (auto concert : concerts) delete concert;
    for (auto booking : bookings) delete booking;
}

void BookingSystem::addConcert(Concert* concert) {
    concerts.push_back(concert);
}

string BookingSystem::createBooking(string customerName, Concert* concert, int seatNumber) {
    if (!concert->bookSeat(seatNumber)) {
        cout << "Failed to book seat: Seat " << seatNumber << " is not available" << endl;
        return "";
    }
    
    string bookingId = "B" + to_string(bookingIdCounter++);
    double totalPrice = concert->getBasePrice();  // Could add premium pricing logic here
    
    Booking* booking = new Booking(bookingId, customerName, concert, seatNumber, totalPrice);
    bookings.push_back(booking);
    return bookingId;
}

bool BookingSystem::cancelBooking(string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking) return false;
    
    booking->getConcert()->cancelSeat(booking->getSeatNumber());
    
    auto it = find(bookings.begin(), bookings.end(), booking);
    if (it != bookings.end()) {
        bookings.erase(it);
        delete booking;
        return true;
    }
    return false;
}

void BookingSystem::displayAllConcerts() const {
    cout << "\nAvailable Concerts:" << endl;
    for (const auto& concert : concerts) {
        concert->displayInfo();
        cout << "------------------------" << endl;
    }
}

void BookingSystem::displayAllBookings() const {
    cout << "\nCurrent Bookings:" << endl;
    for (const auto& booking : bookings) {
        booking->displayInfo();
        cout << "------------------------" << endl;
    }
}

void BookingSystem::displayAvailableSeats(Concert* concert) const {
    cout << "\nAvailable seats for concert " << concert->getName() << ":" << endl;
    for (int i = 1; i <= concert->getTotalSeats(); i++) {
        if (concert->isSeatAvailable(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

Concert* BookingSystem::findConcert(string concertId) const {
    for (auto concert : concerts) {
        if (concert->getConcertId() == concertId) return concert;
    }
    return nullptr;
}

Booking* BookingSystem::findBooking(string bookingId) const {
    for (auto booking : bookings) {
        if (booking->getBookingId() == bookingId) return booking;
    }
    return nullptr;
} 

// ===== Concert.cpp =====
Concert::Concert(string concertId, string name, string venue, 
                string date, double basePrice, int totalSeats)
    : concertId(concertId), name(name), venue(venue), date(date), 
      basePrice(basePrice), totalSeats(totalSeats) {
    
    // Initialize seats
    for (int i = 1; i <= totalSeats; i++) {
        seats.push_back(Seat(i));
    }
}

string Concert::getConcertId() const { return concertId; }
string Concert::getName() const { return name; }
string Concert::getVenue() const { return venue; }
string Concert::getDate() const { return date; }
double Concert::getBasePrice() const { return basePrice; }
int Concert::getTotalSeats() const { return totalSeats; }

int Concert::getAvailableSeats() const {
    int available = 0;
    for (const auto& seat : seats) {
        if (!seat.isBooked()) available++;
    }
    return available;
}

bool Concert::bookSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > totalSeats) return false;
    if (seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].book();
    return true;
}

bool Concert::cancelSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > totalSeats) return false;
    if (!seats[seatNumber - 1].isBooked()) return false;
    
    seats[seatNumber - 1].cancel();
    return true;
}

bool Concert::isSeatAvailable(int seatNumber) const {
    if (seatNumber < 1 || seatNumber > totalSeats) return false;
    return !seats[seatNumber - 1].isBooked();
}

void Concert::displayInfo() const {
    cout << "Concert: " << name << endl;
    cout << "ID: " << concertId << endl;
    cout << "Venue: " << venue << endl;
    cout << "Date: " << date << endl;
    cout << "Price: $" << fixed << setprecision(2) << basePrice << endl;
    cout << "Available Seats: " << getAvailableSeats() << "/" << totalSeats << endl;
} 

// ===== Seat.cpp =====
Seat::Seat(int number) : seatNumber(number), booked(false) {}

int Seat::getSeatNumber() const { return seatNumber; }
bool Seat::isBooked() const { return booked; }
void Seat::book() { booked = true; }
void Seat::cancel() { booked = false; } 

// ===== ConcertBookingDemo.cpp =====
int main() {
    BookingSystem bookingSystem;
    
    // Create some concerts
    Concert* concert1 = new Concert("C001", "Rock Festival", "Stadium A", "2024-07-15", 100.0, 50);
    Concert* concert2 = new Concert("C002", "Jazz Night", "Hall B", "2024-07-20", 75.0, 30);
    
    bookingSystem.addConcert(concert1);
    bookingSystem.addConcert(concert2);
    
    // Display all concerts
    bookingSystem.displayAllConcerts();
    
    // Make some bookings
    string booking1 = bookingSystem.createBooking("John Doe", concert1, 1);
    string booking2 = bookingSystem.createBooking("Jane Smith", concert1, 2);
    string booking3 = bookingSystem.createBooking("Alice Johnson", concert2, 1);
    
    if (!booking1.empty()) {
        cout << "\nBooking created successfully: " << booking1 << endl;
    }
    if (!booking2.empty()) {
        cout << "Booking created successfully: " << booking2 << endl;
    }
    if (!booking3.empty()) {
        cout << "Booking created successfully: " << booking3 << endl;
    }
    
    // Display all bookings
    bookingSystem.displayAllBookings();
    
    // Display available seats for concert1
    bookingSystem.displayAvailableSeats(concert1);
    
    // Cancel a booking
    if (bookingSystem.cancelBooking(booking1)) {
        cout << "\nBooking " << booking1 << " cancelled successfully" << endl;
    }
    
    // Display updated available seats
    bookingSystem.displayAvailableSeats(concert1);
    
    return 0;
} 

