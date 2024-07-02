from datetime import datetime, timedelta
from typing import List
from concert_ticket_booking_system import ConcertTicketBookingSystem
from concert import Concert
from seat import Seat, SeatType, SeatStatus
from user import User

def run():
    # Create concert ticket booking system instance
    booking_system = ConcertTicketBookingSystem()

    # Create concerts
    concert1_seats = _generate_seats(100)
    concert1 = Concert("C001", "Artist 1", "Venue 1", datetime.now() + timedelta(days=30), concert1_seats)
    booking_system.add_concert(concert1)

    concert2_seats = _generate_seats(50)
    concert2 = Concert("C002", "Artist 2", "Venue 2", datetime.now() + timedelta(days=60), concert2_seats)
    booking_system.add_concert(concert2)

    # Create users
    user1 = User("U001", "John Doe", "john@example.com")
    user2 = User("U002", "Jane Smith", "jane@example.com")

    # Search concerts
    search_results = booking_system.search_concerts("Artist 1", "Venue 1", datetime.now() + timedelta(days=30))
    print("Search Results:")
    for concert in search_results:
        print(f"Concert: {concert.artist} at {concert.venue}")

    # Book tickets
    selected_seats1 = _select_seats(concert1, 3)
    booking1 = booking_system.book_tickets(user1, concert1, selected_seats1)
    print(f"Booking 1: {booking1.id} - {len(booking1.seats)} seats booked")

    selected_seats2 = _select_seats(concert2, 2)
    booking2 = booking_system.book_tickets(user2, concert2, selected_seats2)
    print(f"Booking 2: {booking2.id} - {len(booking2.seats)} seats booked")

    # Cancel booking
    booking_system.cancel_booking(booking1.id)
    print("Booking 1 cancelled")

    # Book tickets again
    selected_seats3 = _select_seats(concert1, 2)
    booking3 = booking_system.book_tickets(user2, concert1, selected_seats3)
    print(f"Booking 3: {booking3.id} - {len(booking3.seats)} seats booked")

def _generate_seats(number_of_seats: int) -> List[Seat]:
    seats = []
    for i in range(1, number_of_seats + 1):
        seat_number = f"S{i}"
        seat_type = SeatType.VIP if i <= 10 else SeatType.PREMIUM if i <= 30 else SeatType.REGULAR
        price = 100.0 if seat_type == SeatType.VIP else 75.0 if seat_type == SeatType.PREMIUM else 50.0
        seats.append(Seat(seat_number, seat_number, seat_type, price))
    return seats

def _select_seats(concert: Concert, number_of_seats: int) -> List[Seat]:
    available_seats = [seat for seat in concert.seats if seat.status == SeatStatus.AVAILABLE][:number_of_seats]
    return available_seats

if __name__ == "__main__":
    run()