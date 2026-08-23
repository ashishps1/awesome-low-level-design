// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Movie;
class Show;
class Booking;
class Theater;
class BookingSystem;

// ===== Movie.hpp =====
enum class MovieGenre {
    ACTION,
    COMEDY,
    DRAMA,
    HORROR,
    SCIFI,
    THRILLER
};

class Movie {
private:
    string movieId;
    string title;
    string description;
    MovieGenre genre;
    int durationMinutes;
    string language;
    vector<string> cast;
    bool active;

public:
    Movie(string movieId, string title, string description,
          MovieGenre genre, int durationMinutes, string language);
    
    string getMovieId() const;
    string getTitle() const;
    string getDescription() const;
    MovieGenre getGenre() const;
    int getDurationMinutes() const;
    string getLanguage() const;
    bool isActive() const;
    const vector<string>& getCast() const;
    
    void addCastMember(const string& actor);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Show.hpp =====
enum class ShowStatus {
    SCHEDULED,
    RUNNING,
    COMPLETED,
    CANCELLED
};

class Show {
private:
    string showId;
    Movie* movie;
    string date;
    string startTime;
    double ticketPrice;
    vector<bool> seats;  // true if seat is booked
    ShowStatus status;

public:
    Show(string showId, Movie* movie, string date,
         string startTime, double ticketPrice, int totalSeats);
    
    string getShowId() const;
    Movie* getMovie() const;
    string getDate() const;
    string getStartTime() const;
    double getTicketPrice() const;
    ShowStatus getStatus() const;
    
    bool isSeatAvailable(int seatNumber) const;
    bool bookSeat(int seatNumber);
    void cancelSeatBooking(int seatNumber);
    void setStatus(ShowStatus status);
    int getAvailableSeats() const;
    void displayInfo() const;
};

// ===== Booking.hpp =====
enum class BookingStatus {
    PENDING,
    CONFIRMED,
    CANCELLED
};

class Booking {
private:
    string bookingId;
    Show* show;
    string customerName;
    string customerPhone;
    vector<int> seatNumbers;
    double totalAmount;
    BookingStatus status;
    string timestamp;

public:
    Booking(string bookingId, Show* show, string customerName,
           string customerPhone, const vector<int>& seatNumbers);
    
    string getBookingId() const;
    Show* getShow() const;
    string getCustomerName() const;
    string getCustomerPhone() const;
    const vector<int>& getSeatNumbers() const;
    double getTotalAmount() const;
    BookingStatus getStatus() const;
    string getTimestamp() const;
    
    void calculateTotalAmount();
    void setStatus(BookingStatus status);
    void displayInfo() const;
};

// ===== Theater.hpp =====
class Theater {
private:
    string theaterId;
    string name;
    string location;
    int totalSeats;
    vector<Show*> shows;
    bool active;

public:
    Theater(string theaterId, string name, string location,
           int totalSeats);
    ~Theater();
    
    string getTheaterId() const;
    string getName() const;
    string getLocation() const;
    int getTotalSeats() const;
    bool isActive() const;
    const vector<Show*>& getShows() const;
    
    void addShow(Show* show);
    void removeShow(Show* show);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== BookingSystem.hpp =====
class BookingSystem {
private:
    vector<Movie*> movies;
    vector<Theater*> theaters;
    vector<Booking*> bookings;
    int bookingIdCounter;

public:
    BookingSystem();
    ~BookingSystem();
    
    void addMovie(Movie* movie);
    void addTheater(Theater* theater);
    
    Booking* createBooking(string showId, string customerName,
                          string customerPhone, const vector<int>& seats);
    bool cancelBooking(string bookingId);
    
    void displayMovies() const;
    void displayTheaters() const;
    void displayShows(string movieId) const;
    void displayBooking(string bookingId) const;
    
private:
    Show* findShow(const string& showId) const;
    Booking* findBooking(const string& bookingId) const;
    string generateBookingId();
};

// ===== Booking.cpp =====
Booking::Booking(string bookingId, Show* show, string customerName,
                string customerPhone, const vector<int>& seatNumbers)
    : bookingId(bookingId), show(show), customerName(customerName),
      customerPhone(customerPhone), seatNumbers(seatNumbers),
      status(BookingStatus::PENDING) {
    // Get current timestamp
    auto now = time(nullptr);
    auto tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    timestamp = oss.str();
    
    calculateTotalAmount();
}

string Booking::getBookingId() const { return bookingId; }
Show* Booking::getShow() const { return show; }
string Booking::getCustomerName() const { return customerName; }
string Booking::getCustomerPhone() const { return customerPhone; }
const vector<int>& Booking::getSeatNumbers() const { return seatNumbers; }
double Booking::getTotalAmount() const { return totalAmount; }
BookingStatus Booking::getStatus() const { return status; }
string Booking::getTimestamp() const { return timestamp; }

void Booking::calculateTotalAmount() {
    totalAmount = show->getTicketPrice() * seatNumbers.size();
}

void Booking::setStatus(BookingStatus status) {
    this->status = status;
}

void Booking::displayInfo() const {
    cout << "\nBooking Details:" << endl;
    cout << "Booking ID: " << bookingId << endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Customer Phone: " << customerPhone << endl;
    show->displayInfo();
    cout << "Seats: ";
    for (int seat : seatNumbers) {
        cout << seat << " ";
    }
    cout << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) 
              << totalAmount << endl;
    cout << "Status: ";
    switch (status) {
        case BookingStatus::PENDING: cout << "Pending"; break;
        case BookingStatus::CONFIRMED: cout << "Confirmed"; break;
        case BookingStatus::CANCELLED: cout << "Cancelled"; break;
    }
    cout << endl;
    cout << "Booking Time: " << timestamp << endl;
} 

// ===== BookingSystem.cpp =====
BookingSystem::BookingSystem() : bookingIdCounter(1) {}

BookingSystem::~BookingSystem() {
    for (auto movie : movies) delete movie;
    for (auto theater : theaters) delete theater;
    for (auto booking : bookings) delete booking;
}

void BookingSystem::addMovie(Movie* movie) {
    movies.push_back(movie);
}

void BookingSystem::addTheater(Theater* theater) {
    theaters.push_back(theater);
}

Booking* BookingSystem::createBooking(string showId, string customerName,
                                    string customerPhone, const vector<int>& seats) {
    Show* show = findShow(showId);
    if (!show || show->getStatus() != ShowStatus::SCHEDULED) {
        return nullptr;
    }
    
    // Check if all seats are available
    for (int seatNumber : seats) {
        if (!show->isSeatAvailable(seatNumber)) {
            return nullptr;
        }
    }
    
    // Book all seats
    for (int seatNumber : seats) {
        show->bookSeat(seatNumber);
    }
    
    // Create booking
    Booking* booking = new Booking(generateBookingId(), show, customerName,
                                 customerPhone, seats);
    booking->setStatus(BookingStatus::CONFIRMED);
    bookings.push_back(booking);
    return booking;
}

bool BookingSystem::cancelBooking(string bookingId) {
    Booking* booking = findBooking(bookingId);
    if (!booking || booking->getStatus() == BookingStatus::CANCELLED) {
        return false;
    }
    
    // Cancel seat bookings
    Show* show = booking->getShow();
    for (int seatNumber : booking->getSeatNumbers()) {
        show->cancelSeatBooking(seatNumber);
    }
    
    booking->setStatus(BookingStatus::CANCELLED);
    return true;
}

void BookingSystem::displayMovies() const {
    cout << "\nAvailable Movies:" << endl;
    for (const auto& movie : movies) {
        if (movie->isActive()) {
            movie->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void BookingSystem::displayTheaters() const {
    cout << "\nTheaters:" << endl;
    for (const auto& theater : theaters) {
        if (theater->isActive()) {
            theater->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void BookingSystem::displayShows(string movieId) const {
    cout << "\nShows for Movie ID " << movieId << ":" << endl;
    for (const auto& theater : theaters) {
        for (const auto& show : theater->getShows()) {
            if (show->getMovie()->getMovieId() == movieId) {
                show->displayInfo();
                cout << "------------------------" << endl;
            }
        }
    }
}

void BookingSystem::displayBooking(string bookingId) const {
    Booking* booking = findBooking(bookingId);
    if (booking) {
        booking->displayInfo();
    }
}

Show* BookingSystem::findShow(const string& showId) const {
    for (const auto& theater : theaters) {
        for (const auto& show : theater->getShows()) {
            if (show->getShowId() == showId) {
                return show;
            }
        }
    }
    return nullptr;
}

Booking* BookingSystem::findBooking(const string& bookingId) const {
    for (auto booking : bookings) {
        if (booking->getBookingId() == bookingId) {
            return booking;
        }
    }
    return nullptr;
}

string BookingSystem::generateBookingId() {
    return "B" + to_string(bookingIdCounter++);
} 

// ===== Movie.cpp =====
Movie::Movie(string movieId, string title, string description,
             MovieGenre genre, int durationMinutes, string language)
    : movieId(movieId), title(title), description(description),
      genre(genre), durationMinutes(durationMinutes), language(language),
      active(true) {}

string Movie::getMovieId() const { return movieId; }
string Movie::getTitle() const { return title; }
string Movie::getDescription() const { return description; }
MovieGenre Movie::getGenre() const { return genre; }
int Movie::getDurationMinutes() const { return durationMinutes; }
string Movie::getLanguage() const { return language; }
bool Movie::isActive() const { return active; }
const vector<string>& Movie::getCast() const { return cast; }

void Movie::addCastMember(const string& actor) {
    cast.push_back(actor);
}

void Movie::setActive(bool status) {
    active = status;
}

void Movie::displayInfo() const {
    cout << "Movie: " << title << " (ID: " << movieId << ")" << endl;
    cout << "Description: " << description << endl;
    cout << "Genre: ";
    switch (genre) {
        case MovieGenre::ACTION: cout << "Action"; break;
        case MovieGenre::COMEDY: cout << "Comedy"; break;
        case MovieGenre::DRAMA: cout << "Drama"; break;
        case MovieGenre::HORROR: cout << "Horror"; break;
        case MovieGenre::SCIFI: cout << "Sci-Fi"; break;
        case MovieGenre::THRILLER: cout << "Thriller"; break;
    }
    cout << endl;
    cout << "Duration: " << durationMinutes << " minutes" << endl;
    cout << "Language: " << language << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    
    if (!cast.empty()) {
        cout << "Cast:" << endl;
        for (const auto& actor : cast) {
            cout << "- " << actor << endl;
        }
    }
} 

// ===== Show.cpp =====
Show::Show(string showId, Movie* movie, string date,
           string startTime, double ticketPrice, int totalSeats)
    : showId(showId), movie(movie), date(date), startTime(startTime),
      ticketPrice(ticketPrice), seats(totalSeats, false),
      status(ShowStatus::SCHEDULED) {}

string Show::getShowId() const { return showId; }
Movie* Show::getMovie() const { return movie; }
string Show::getDate() const { return date; }
string Show::getStartTime() const { return startTime; }
double Show::getTicketPrice() const { return ticketPrice; }
ShowStatus Show::getStatus() const { return status; }

bool Show::isSeatAvailable(int seatNumber) const {
    if (seatNumber < 1 || seatNumber > seats.size()) return false;
    return !seats[seatNumber - 1];
}

bool Show::bookSeat(int seatNumber) {
    if (!isSeatAvailable(seatNumber)) return false;
    seats[seatNumber - 1] = true;
    return true;
}

void Show::cancelSeatBooking(int seatNumber) {
    if (seatNumber >= 1 && seatNumber <= seats.size()) {
        seats[seatNumber - 1] = false;
    }
}

void Show::setStatus(ShowStatus status) {
    this->status = status;
}

int Show::getAvailableSeats() const {
    int count = 0;
    for (bool seat : seats) {
        if (!seat) count++;
    }
    return count;
}

void Show::displayInfo() const {
    cout << "\nShow Details:" << endl;
    cout << "Show ID: " << showId << endl;
    movie->displayInfo();
    cout << "Date: " << date << endl;
    cout << "Start Time: " << startTime << endl;
    cout << "Ticket Price: $" << fixed << setprecision(2) 
              << ticketPrice << endl;
    cout << "Available Seats: " << getAvailableSeats() 
              << "/" << seats.size() << endl;
    cout << "Status: ";
    switch (status) {
        case ShowStatus::SCHEDULED: cout << "Scheduled"; break;
        case ShowStatus::RUNNING: cout << "Running"; break;
        case ShowStatus::COMPLETED: cout << "Completed"; break;
        case ShowStatus::CANCELLED: cout << "Cancelled"; break;
    }
    cout << endl;
} 

// ===== Theater.cpp =====
Theater::Theater(string theaterId, string name, string location,
                int totalSeats)
    : theaterId(theaterId), name(name), location(location),
      totalSeats(totalSeats), active(true) {}

Theater::~Theater() {
    for (auto show : shows) {
        delete show;
    }
}

string Theater::getTheaterId() const { return theaterId; }
string Theater::getName() const { return name; }
string Theater::getLocation() const { return location; }
int Theater::getTotalSeats() const { return totalSeats; }
bool Theater::isActive() const { return active; }
const vector<Show*>& Theater::getShows() const { return shows; }

void Theater::addShow(Show* show) {
    shows.push_back(show);
}

void Theater::removeShow(Show* show) {
    auto it = find(shows.begin(), shows.end(), show);
    if (it != shows.end()) {
        shows.erase(it);
    }
}

void Theater::setActive(bool status) {
    active = status;
}

void Theater::displayInfo() const {
    cout << "Theater: " << name << " (ID: " << theaterId << ")" << endl;
    cout << "Location: " << location << endl;
    cout << "Total Seats: " << totalSeats << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Number of Shows: " << shows.size() << endl;
} 

// ===== BookingDemo.cpp =====
int main() {
    BookingSystem system;
    
    // Create movies
    Movie* movie1 = new Movie("M001", "The Matrix", "A sci-fi action movie",
                             MovieGenre::SCIFI, 136, "English");
    movie1->addCastMember("Keanu Reeves");
    movie1->addCastMember("Laurence Fishburne");
    
    Movie* movie2 = new Movie("M002", "Inception", "A mind-bending thriller",
                             MovieGenre::THRILLER, 148, "English");
    movie2->addCastMember("Leonardo DiCaprio");
    movie2->addCastMember("Ellen Page");
    
    system.addMovie(movie1);
    system.addMovie(movie2);
    
    // Create theaters
    Theater* theater1 = new Theater("T001", "Cineplex", "Downtown", 100);
    Theater* theater2 = new Theater("T002", "MovieMax", "Uptown", 150);
    
    system.addTheater(theater1);
    system.addTheater(theater2);
    
    // Create shows
    Show* show1 = new Show("S001", movie1, "2024-01-01", "18:00", 12.99, 100);
    Show* show2 = new Show("S002", movie2, "2024-01-01", "20:00", 14.99, 150);
    
    theater1->addShow(show1);
    theater2->addShow(show2);
    
    // Display available movies and shows
    system.displayMovies();
    system.displayShows("M001");
    
    // Create a booking
    vector<int> seats = {1, 2, 3};
    Booking* booking = system.createBooking("S001", "John Doe", "+1-555-0123", seats);
    
    if (booking) {
        cout << "\nBooking created successfully!" << endl;
        system.displayBooking(booking->getBookingId());
        
        // Try to book same seats again
        cout << "\nTrying to book same seats again..." << endl;
        Booking* failedBooking = system.createBooking("S001", "Jane Smith", 
                                                     "+1-555-0124", seats);
        if (!failedBooking) {
            cout << "Booking failed: Seats already taken" << endl;
        }
        
        // Cancel booking
        cout << "\nCancelling booking..." << endl;
        if (system.cancelBooking(booking->getBookingId())) {
            cout << "Booking cancelled successfully!" << endl;
            system.displayBooking(booking->getBookingId());
        }
    }
    
    return 0;
} 

