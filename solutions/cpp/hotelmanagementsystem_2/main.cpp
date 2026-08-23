// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Guest;
class Room;
class Booking;
class HotelManager;

// ===== Guest.hpp =====
class Guest {
private:
    string guestId;
    string name;
    string email;
    string phone;
    string address;

public:
    Guest(string guestId, string name, string email,
          string phone, string address);
    
    string getGuestId() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    string getAddress() const;
    void displayInfo() const;
};

// ===== Room.hpp =====
enum class RoomType {
    STANDARD,
    DELUXE,
    SUITE
};

enum class RoomStatus {
    AVAILABLE,
    OCCUPIED,
    UNDER_MAINTENANCE
};

class Room {
private:
    string roomNumber;
    RoomType type;
    RoomStatus status;
    double pricePerNight;
    int capacity;

public:
    Room(string roomNumber, RoomType type, double pricePerNight, int capacity);
    
    string getRoomNumber() const;
    RoomType getType() const;
    RoomStatus getStatus() const;
    double getPricePerNight() const;
    int getCapacity() const;
    
    void setStatus(RoomStatus status);
    void displayInfo() const;
};

// ===== Booking.hpp =====
enum class BookingStatus {
    CONFIRMED,
    CHECKED_IN,
    CHECKED_OUT,
    CANCELLED
};

class Booking {
private:
    string bookingId;
    Guest* guest;
    Room* room;
    string checkInDate;
    string checkOutDate;
    int numberOfNights;
    double totalAmount;
    BookingStatus status;

public:
    Booking(string bookingId, Guest* guest, Room* room,
           string checkInDate, string checkOutDate, int numberOfNights);
    
    string getBookingId() const;
    Guest* getGuest() const;
    Room* getRoom() const;
    string getCheckInDate() const;
    string getCheckOutDate() const;
    int getNumberOfNights() const;
    double getTotalAmount() const;
    BookingStatus getStatus() const;
    
    void calculateTotalAmount();
    void setStatus(BookingStatus status);
    void displayInfo() const;
};

// ===== HotelManager.hpp =====
class HotelManager {
private:
    vector<Room*> rooms;
    vector<Guest*> guests;
    vector<Booking*> bookings;
    int bookingIdCounter;

public:
    HotelManager();
    ~HotelManager();
    
    void addRoom(Room* room);
    void addGuest(Guest* guest);
    
    Booking* createBooking(string guestId, string roomNumber,
                          string checkInDate, string checkOutDate,
                          int numberOfNights);
    
    bool checkIn(string bookingId);
    bool checkOut(string bookingId);
    bool cancelBooking(string bookingId);
    
    void displayAvailableRooms() const;
    void displayBookingHistory(string guestId) const;
    void displayAllGuests() const;
    void displayAllBookings() const;
    
private:
    Room* findRoom(const string& roomNumber) const;
    Guest* findGuest(const string& guestId) const;
    Booking* findBooking(const string& bookingId) const;
    string generateBookingId();
};

// ===== Booking.cpp =====
Booking::Booking(string bookingId, Guest* guest, Room* room,
                string checkInDate, string checkOutDate, int numberOfNights)
    : bookingId(bookingId), guest(guest), room(room),
      checkInDate(checkInDate), checkOutDate(checkOutDate),
      numberOfNights(numberOfNights), status(BookingStatus::CONFIRMED) {
    calculateTotalAmount();
}

string Booking::getBookingId() const { return bookingId; }
Guest* Booking::getGuest() const { return guest; }
Room* Booking::getRoom() const { return room; }
string Booking::getCheckInDate() const { return checkInDate; }
string Booking::getCheckOutDate() const { return checkOutDate; }
int Booking::getNumberOfNights() const { return numberOfNights; }
double Booking::getTotalAmount() const { return totalAmount; }
BookingStatus Booking::getStatus() const { return status; }

void Booking::calculateTotalAmount() {
    totalAmount = room->getPricePerNight() * numberOfNights;
}

void Booking::setStatus(BookingStatus status) {
    this->status = status;
}

void Booking::displayInfo() const {
    cout << "\nBooking Details:" << endl;
    cout << "Booking ID: " << bookingId << endl;
    cout << "Guest: " << guest->getName() << endl;
    cout << "Room: " << room->getRoomNumber() << endl;
    cout << "Check-in Date: " << checkInDate << endl;
    cout << "Check-out Date: " << checkOutDate << endl;
    cout << "Number of Nights: " << numberOfNights << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) 
              << totalAmount << endl;
    cout << "Status: ";
    switch (status) {
        case BookingStatus::CONFIRMED: cout << "Confirmed"; break;
        case BookingStatus::CHECKED_IN: cout << "Checked In"; break;
        case BookingStatus::CHECKED_OUT: cout << "Checked Out"; break;
        case BookingStatus::CANCELLED: cout << "Cancelled"; break;
    }
    cout << endl;
} 

// ===== Guest.cpp =====
Guest::Guest(string guestId, string name, string email,
            string phone, string address)
    : guestId(guestId), name(name), email(email), phone(phone), address(address) {}

string Guest::getGuestId() const { return guestId; }
string Guest::getName() const { return name; }
string Guest::getEmail() const { return email; }
string Guest::getPhone() const { return phone; }
string Guest::getAddress() const { return address; }

void Guest::displayInfo() const {
    cout << "Guest: " << name << " (ID: " << guestId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
} 

// ===== HotelManager.cpp =====
HotelManager::HotelManager() : bookingIdCounter(1) {}

HotelManager::~HotelManager() {
    for (auto room : rooms) delete room;
    for (auto guest : guests) delete guest;
    for (auto booking : bookings) delete booking;
}

void HotelManager::addRoom(Room* room) {
    rooms.push_back(room);
}

void HotelManager::addGuest(Guest* guest) {
    guests.push_back(guest);
}

Booking* HotelManager::createBooking(string guestId, string roomNumber,
                                   string checkInDate, string checkOutDate,
                                   int numberOfNights) {
    Guest* guest = findGuest(guestId);
    Room* room = findRoom(roomNumber);
    
    if (!guest || !room || room->getStatus() != RoomStatus::AVAILABLE) {
        return nullptr;
    }
    
    Booking* booking = new Booking(generateBookingId(), guest, room,
                                 checkInDate, checkOutDate, numberOfNights);
    bookings.push_back(booking);
    return booking;
}

bool HotelManager::checkIn(string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() != BookingStatus::CONFIRMED) {
        return false;
    }
    
    booking->setStatus(BookingStatus::CHECKED_IN);
    booking->getRoom()->setStatus(RoomStatus::OCCUPIED);
    return true;
}

bool HotelManager::checkOut(string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() != BookingStatus::CHECKED_IN) {
        return false;
    }
    
    booking->setStatus(BookingStatus::CHECKED_OUT);
    booking->getRoom()->setStatus(RoomStatus::AVAILABLE);
    return true;
}

bool HotelManager::cancelBooking(string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() != BookingStatus::CONFIRMED) {
        return false;
    }
    
    booking->setStatus(BookingStatus::CANCELLED);
    booking->getRoom()->setStatus(RoomStatus::AVAILABLE);
    return true;
}

void HotelManager::displayAvailableRooms() const {
    cout << "\nAvailable Rooms:" << endl;
    for (const auto& room : rooms) {
        if (room->getStatus() == RoomStatus::AVAILABLE) {
            room->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void HotelManager::displayBookingHistory(string guestId) const {
    cout << "\nBooking History:" << endl;
    for (const auto& booking : bookings) {
        if (booking->getGuest()->getGuestId() == guestId) {
            booking->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void HotelManager::displayAllGuests() const {
    cout << "\nAll Guests:" << endl;
    for (const auto& guest : guests) {
        guest->displayInfo();
        cout << "------------------------" << endl;
    }
}

void HotelManager::displayAllBookings() const {
    cout << "\nAll Bookings:" << endl;
    for (const auto& booking : bookings) {
        booking->displayInfo();
        cout << "------------------------" << endl;
    }
}

Room* HotelManager::findRoom(const string& roomNumber) const {
    for (auto room : rooms) {
        if (room->getRoomNumber() == roomNumber) return room;
    }
    return nullptr;
}

Guest* HotelManager::findGuest(const string& guestId) const {
    for (auto guest : guests) {
        if (guest->getGuestId() == guestId) return guest;
    }
    return nullptr;
}

Booking* HotelManager::findBooking(const string& bookingId) const {
    for (auto booking : bookings) {
        if (booking->getBookingId() == bookingId) return booking;
    }
    return nullptr;
}

string HotelManager::generateBookingId() {
    return "BK" + to_string(bookingIdCounter++);
} 

// ===== Room.cpp =====
Room::Room(string roomNumber, RoomType type, double pricePerNight, int capacity)
    : roomNumber(roomNumber), type(type), status(RoomStatus::AVAILABLE),
      pricePerNight(pricePerNight), capacity(capacity) {}

string Room::getRoomNumber() const { return roomNumber; }
RoomType Room::getType() const { return type; }
RoomStatus Room::getStatus() const { return status; }
double Room::getPricePerNight() const { return pricePerNight; }
int Room::getCapacity() const { return capacity; }

void Room::setStatus(RoomStatus status) {
    this->status = status;
}

void Room::displayInfo() const {
    cout << "Room " << roomNumber << endl;
    cout << "Type: ";
    switch (type) {
        case RoomType::STANDARD: cout << "Standard"; break;
        case RoomType::DELUXE: cout << "Deluxe"; break;
        case RoomType::SUITE: cout << "Suite"; break;
    }
    cout << endl;
    
    cout << "Status: ";
    switch (status) {
        case RoomStatus::AVAILABLE: cout << "Available"; break;
        case RoomStatus::OCCUPIED: cout << "Occupied"; break;
        case RoomStatus::UNDER_MAINTENANCE: cout << "Under Maintenance"; break;
    }
    cout << endl;
    
    cout << "Price per night: $" << fixed << setprecision(2) 
              << pricePerNight << endl;
    cout << "Capacity: " << capacity << " persons" << endl;
} 

// ===== HotelDemo.cpp =====
int main() {
    HotelManager hotel;
    
    // Add rooms
    Room* room1 = new Room("101", RoomType::STANDARD, 100.0, 2);
    Room* room2 = new Room("201", RoomType::DELUXE, 150.0, 3);
    Room* room3 = new Room("301", RoomType::SUITE, 250.0, 4);
    
    hotel.addRoom(room1);
    hotel.addRoom(room2);
    hotel.addRoom(room3);
    
    // Add guests
    Guest* guest1 = new Guest("G001", "John Doe", "john@example.com",
                            "+1-555-0123", "123 Main St");
    hotel.addGuest(guest1);
    
    // Display available rooms
    hotel.displayAvailableRooms();
    
    // Create a booking
    Booking* booking = hotel.createBooking("G001", "101", "2024-01-01",
                                         "2024-01-03", 2);
    if (booking) {
        cout << "\nBooking created successfully!" << endl;
        booking->displayInfo();
        
        // Check in
        if (hotel.checkIn(booking->getBookingId())) {
            cout << "\nChecked in successfully!" << endl;
        }
        
        // Display available rooms after check-in
        hotel.displayAvailableRooms();
        
        // Check out
        if (hotel.checkOut(booking->getBookingId())) {
            cout << "\nChecked out successfully!" << endl;
        }
        
        // Display booking history
        hotel.displayBookingHistory("G001");
    }
    
    return 0;
} 

