from movie_booking_service import MovieBookingService
from movie import Movie
from screen import Screen
from seat import Seat, SeatType
from enums import SeatStatus
from payment_strategy import CreditCardPaymentStrategy
from movie_observer import UserObserver
from datetime import datetime, timedelta
from pricing_strategy import WeekdayPricingStrategy

class MovieBookingDemo:
  @staticmethod
  def main():
      # Setup
      service = MovieBookingService.get_instance()

      nyc = service.add_city("city1", "New York")
      la = service.add_city("city2", "Los Angeles")

      # 2. Add movies
      matrix = Movie("M1", "The Matrix", 120)
      avengers = Movie("M2", "Avengers: Endgame", 170)
      service.add_movie(matrix)
      service.add_movie(avengers)

      # Add Seats for a Screen
      screen1 = Screen("S1")

      for i in range(1, 11):
          seat_type = SeatType.REGULAR if i <= 5 else SeatType.PREMIUM
          screen1.add_seat(Seat(f"A{i}", 1, i, seat_type))
          screen1.add_seat(Seat(f"B{i}", 2, i, seat_type))

      # Add Cinemas
      amc_nyc = service.add_cinema("cinema1", "AMC Times Square", nyc.get_id(), [screen1])

      # Add Shows
      matrix_show = service.add_show("show1", matrix, screen1, datetime.now() + timedelta(hours=2), WeekdayPricingStrategy())
      avengers_show = service.add_show("show2", avengers, screen1, datetime.now() + timedelta(hours=5), WeekdayPricingStrategy())

      # User and Observer Setup
      alice = service.create_user("Alice", "alice@example.com")
      alice_observer = UserObserver(alice)
      avengers.add_observer(alice_observer)

      # Simulate movie release
      print("\n--- Notifying Observers about Movie Release ---")
      avengers.notify_observers()

      # User Story: Alice books tickets
      print("\n--- Alice's Booking Flow ---")
      city_name = "New York"
      movie_title = "Avengers: Endgame"

      # 1. Search for shows
      available_shows = service.find_shows(movie_title, city_name)
      if not available_shows:
          print(f"No shows found for {movie_title} in {city_name}")
          return
      
      selected_show = available_shows[0]  # Alice selects the first show

      # 2. View available seats
      available_seats = [seat for seat in selected_show.get_screen().get_seats() if seat.get_status() == SeatStatus.AVAILABLE]
      print(f"Available seats for '{selected_show.get_movie().get_title()}' at {selected_show.get_start_time()}: {[seat.get_id() for seat in available_seats]}")

      # 3. Select seats
      desired_seats = [available_seats[2], available_seats[3]]
      print(f"Alice selects seats: {[seat.get_id() for seat in desired_seats]}")

      # 4. Book Tickets
      booking = service.book_tickets(
          alice.get_id(),
          selected_show.get_id(),
          desired_seats,
          CreditCardPaymentStrategy("1234-5678-9876-5432", "123")
      )

      if booking:
          print("\n--- Booking Successful! ---")
          print(f"Booking ID: {booking.get_id()}")
          print(f"User: {booking.get_user().get_name()}")
          print(f"Movie: {booking.get_show().get_movie().get_title()}")
          print(f"Seats: {[seat.get_id() for seat in booking.get_seats()]}")
          print(f"Total Amount: ${booking.get_total_amount()}")
          print(f"Payment Status: {booking.get_payment().get_status().value}")
      else:
          print("Booking failed.")

      # 5. Verify seat status after booking
      print("\nSeat status after Alice's booking:")
      for seat in desired_seats:
          print(f"Seat {seat.get_id()} status: {seat.get_status().value}")

      # 6. Shut down the system to release resources like the scheduler.
      service.shutdown()


if __name__ == "__main__":
    MovieBookingDemo.main()