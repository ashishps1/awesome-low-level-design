from datetime import datetime, timedelta
from typing import List
from concert_ticket_booking_system import ConcertTicketBookingSystem
from concert import Concert
from seat import Seat, SeatType, SeatStatus
from user import User

class ConcertTicketBookingSystemDemo:
    @staticmethod
    def run():
        # Create concert ticket booking system instance
        booking_system = ConcertTicketBookingSystem()

        # Create concerts
        concert1_seats = ConcertTicketBookingSystemDemo._generate_seats(100)
        concert1 = Concert("C001", "Artist 1", "Venue 1", datetime.now().replace(day=10, hour=20, minute=0, second=0, microsecond=0), concert1_seats)
        booking_system.add_concert(concert1)

        concert2_seats = ConcertTicketBookingSystemDemo._generate_seats(50)
        concert2 = Concert("C002", "Artist 2", "Venue 2", datetime.now().replace(day=15, hour=19, minute=30, second=0, microsecond=0), concert2_seats)
        booking_system.add_concert(concert2)

        # Create users
        user1 = User("U001", "John Doe", "john@example.com")
        user2 = User("U002", "Jane Smith", "jane@example.com")

        # Search concerts
        search_results = booking_system.search_concerts("Artist 1", "Venue 1", concert1.date_time)
        print("Search Results:")
        for concert in search_results:
            print(f"Concert: {concert.artist} at {concert.venue}")

        # Book tickets
        selected_seats1 = ConcertTicketBookingSystemDemo._select_seats(concert1, 3)
        booking1 = booking_system.book_tickets(user1, concert1, selected_seats1)

        selected_seats2 = ConcertTicketBookingSystemDemo._select_seats(concert2, 2)
        booking2 = booking_system.book_tickets(user2, concert2, selected_seats2)

        # Cancel booking
        booking_system.cancel_booking(booking1.id)

        # Book tickets again
        selected_seats3 = ConcertTicketBookingSystemDemo._select_seats(concert1, 2)
        booking3 = booking_system.book_tickets(user2, concert1, selected_seats3)

    @staticmethod
    def _generate_seats(number_of_seats: int) -> List[Seat]:
        seats = []
        for i in range(1, number_of_seats + 1):
            seat_number = f"S{i}"
            seat_type = SeatType.VIP if i <= 10 else SeatType.PREMIUM if i <= 30 else SeatType.REGULAR
            price = 100.0 if seat_type == SeatType.VIP else 75.0 if seat_type == SeatType.PREMIUM else 50.0
            seats.append(Seat(seat_number, seat_number, seat_type, price))
        return seats

    @staticmethod
    def _select_seats(concert: Concert, number_of_seats: int) -> List[Seat]:
        available_seats = [seat for seat in concert.seats if seat.status == SeatStatus.AVAILABLE]
        return available_seats[:number_of_seats]

if __name__ == "__main__":
    ConcertTicketBookingSystemDemo.run()