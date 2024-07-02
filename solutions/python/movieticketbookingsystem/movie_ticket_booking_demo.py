from datetime import datetime, timedelta
from movie_ticket_booking_system import MovieTicketBookingSystem
from movie import Movie
from theater import Theater
from show import Show
from seat import Seat, SeatType, SeatStatus
from user import User

class MovieTicketBookingDemo:
    @staticmethod
    def run():
        booking_system = MovieTicketBookingSystem.get_instance()

        # Add movies
        movie1 = Movie("M1", "Movie 1", "Description 1", 120)
        movie2 = Movie("M2", "Movie 2", "Description 2", 135)
        booking_system.add_movie(movie1)
        booking_system.add_movie(movie2)

        # Add theaters
        theater1 = Theater("T1", "Theater 1", "Location 1", [])
        theater2 = Theater("T2", "Theater 2", "Location 2", [])
        booking_system.add_theater(theater1)
        booking_system.add_theater(theater2)

        # Add shows
        show1 = Show("S1", movie1, theater1, datetime.now(), datetime.now() + timedelta(minutes=movie1.duration_in_minutes), create_seats(10, 10))
        show2 = Show("S2", movie2, theater2, datetime.now(), datetime.now() + timedelta(minutes=movie2.duration_in_minutes), create_seats(8, 8))
        booking_system.add_show(show1)
        booking_system.add_show(show2)

        # Book tickets
        user = User("U1", "John Doe", "john@example.com")
        selected_seats = [show1.seats["1-5"], show1.seats["1-6"]]
        booking = booking_system.book_tickets(user, show1, selected_seats)
        if booking:
            print(f"Booking successful. Booking ID: {booking.id}")
            booking_system.confirm_booking(booking.id)
        else:
            print("Booking failed. Seats not available.")

        # Cancel booking
        # booking_system.cancel_booking(booking.id)

def create_seats(rows, columns):
    seats = {}
    for row in range(1, rows + 1):
        for col in range(1, columns + 1):
            seat_id = f"{row}-{col}"
            seat_type = SeatType.PREMIUM if row <= 2 else SeatType.NORMAL
            price = 150.0 if seat_type == SeatType.PREMIUM else 100.0
            seat = Seat(seat_id, row, col, seat_type, price, SeatStatus.AVAILABLE)
            seats[seat_id] = seat
    return seats

if __name__ == "__main__":
    MovieTicketBookingDemo.run()
