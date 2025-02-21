#include "BookingSystem.hpp"
#include <iostream>

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
    std::vector<int> seats = {1, 2, 3};
    Booking* booking = system.createBooking("S001", "John Doe", "+1-555-0123", seats);
    
    if (booking) {
        std::cout << "\nBooking created successfully!" << std::endl;
        system.displayBooking(booking->getBookingId());
        
        // Try to book same seats again
        std::cout << "\nTrying to book same seats again..." << std::endl;
        Booking* failedBooking = system.createBooking("S001", "Jane Smith", 
                                                     "+1-555-0124", seats);
        if (!failedBooking) {
            std::cout << "Booking failed: Seats already taken" << std::endl;
        }
        
        // Cancel booking
        std::cout << "\nCancelling booking..." << std::endl;
        if (system.cancelBooking(booking->getBookingId())) {
            std::cout << "Booking cancelled successfully!" << std::endl;
            system.displayBooking(booking->getBookingId());
        }
    }
    
    return 0;
} 