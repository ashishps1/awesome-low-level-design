using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace MovieTicketBookingSystem
{
    public class MovieTicketBookingSystem
    {
        private static MovieTicketBookingSystem _instance;
        private readonly List<Movie> _movies;
        private readonly List<Theater> _theaters;
        private readonly ConcurrentDictionary<string, Show> _shows;
        private readonly ConcurrentDictionary<string, Booking> _bookings;
        private static readonly string BOOKING_ID_PREFIX = "BKG";
        private static long _bookingCounter = 0;

        private MovieTicketBookingSystem()
        {
            _movies = new List<Movie>();
            _theaters = new List<Theater>();
            _shows = new ConcurrentDictionary<string, Show>();
            _bookings = new ConcurrentDictionary<string, Booking>();
        }

        public static MovieTicketBookingSystem GetInstance()
        {
            return _instance ??= new MovieTicketBookingSystem();
        }

        public void AddMovie(Movie movie)
        {
            _movies.Add(movie);
        }

        public void AddTheater(Theater theater)
        {
            _theaters.Add(theater);
        }

        public void AddShow(Show show)
        {
            _shows[show.Id] = show;
        }

        public List<Movie> GetMovies() => _movies;
        public List<Theater> GetTheaters() => _theaters;

        public Show GetShow(string showId)
        {
            _shows.TryGetValue(showId, out var show);
            return show;
        }

        public Booking BookTickets(User user, Show show, List<Seat> selectedSeats)
        {
            lock (this)
            {
                if (AreSeatsAvailable(show, selectedSeats))
                {
                    MarkSeatsAsBooked(show, selectedSeats);
                    var totalPrice = CalculateTotalPrice(selectedSeats);
                    var bookingId = GenerateBookingId();
                    var booking = new Booking(bookingId, user, show, selectedSeats, totalPrice, BookingStatus.PENDING);
                    _bookings[bookingId] = booking;
                    return booking;
                }
            }
            return null;
        }

        private bool AreSeatsAvailable(Show show, List<Seat> selectedSeats)
        {
            return selectedSeats.All(seat => show.Seats.ContainsKey(seat.Id) && show.Seats[seat.Id].Status == SeatStatus.AVAILABLE);
        }

        private void MarkSeatsAsBooked(Show show, List<Seat> selectedSeats)
        {
            foreach (var seat in selectedSeats)
            {
                show.Seats[seat.Id].Status = SeatStatus.BOOKED;
            }
        }

        private double CalculateTotalPrice(List<Seat> selectedSeats)
        {
            return selectedSeats.Sum(seat => seat.Price);
        }

        private string GenerateBookingId()
        {
            var bookingNumber = Interlocked.Increment(ref _bookingCounter);
            var timestamp = DateTime.Now.ToString("yyyyMMddHHmmss");
            return $"{BOOKING_ID_PREFIX}{timestamp}{bookingNumber:D6}";
        }

        public void ConfirmBooking(string bookingId)
        {
            lock (this)
            {
                if (_bookings.TryGetValue(bookingId, out var booking) && booking.Status == BookingStatus.PENDING)
                {
                    booking.Status = BookingStatus.CONFIRMED;
                }
            }
        }

        public void CancelBooking(string bookingId)
        {
            lock (this)
            {
                if (_bookings.TryGetValue(bookingId, out var booking) && booking.Status != BookingStatus.CANCELLED)
                {
                    booking.Status = BookingStatus.CANCELLED;
                    MarkSeatsAsAvailable(booking.Show, booking.Seats);
                }
            }
        }

        private void MarkSeatsAsAvailable(Show show, List<Seat> seats)
        {
            foreach (var seat in seats)
            {
                show.Seats[seat.Id].Status = SeatStatus.AVAILABLE;
            }
        }
    }
}