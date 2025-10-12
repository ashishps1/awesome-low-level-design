using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

public class MovieBookingDemo
{
    public static void Main(string[] args)
    {
        // Setup
        var service = MovieBookingService.GetInstance();

        var nyc = service.AddCity("city1", "New York");
        var la = service.AddCity("city2", "Los Angeles");

        // 2. Add movies
        var matrix = new Movie("M1", "The Matrix", 120);
        var avengers = new Movie("M2", "Avengers: Endgame", 170);
        service.AddMovie(matrix);
        service.AddMovie(avengers);

        // Add Seats for a Screen
        var screen1 = new Screen("S1");

        for (int i = 1; i <= 10; i++)
        {
            var seatType = i <= 5 ? SeatType.REGULAR : SeatType.PREMIUM;
            screen1.AddSeat(new Seat($"A{i}", 1, i, seatType));
            screen1.AddSeat(new Seat($"B{i}", 2, i, seatType));
        }

        // Add Cinemas
        var amcNYC = service.AddCinema("cinema1", "AMC Times Square", nyc.GetId(), new List<Screen> { screen1 });

        // Add Shows
        var matrixShow = service.AddShow("show1", matrix, screen1, DateTime.Now.AddHours(2), new WeekdayPricingStrategy());
        var avengersShow = service.AddShow("show2", avengers, screen1, DateTime.Now.AddHours(5), new WeekdayPricingStrategy());

        // --- User and Observer Setup ---
        var alice = service.CreateUser("Alice", "alice@example.com");
        var aliceObserver = new UserObserver(alice);
        avengers.AddObserver(aliceObserver);

        // Simulate movie release
        Console.WriteLine("\n--- Notifying Observers about Movie Release ---");
        avengers.NotifyObservers();

        // --- User Story: Alice books tickets ---
        Console.WriteLine("\n--- Alice's Booking Flow ---");
        string cityName = "New York";
        string movieTitle = "Avengers: Endgame";

        // 1. Search for shows
        var availableShows = service.FindShows(movieTitle, cityName);
        if (!availableShows.Any())
        {
            Console.WriteLine($"No shows found for {movieTitle} in {cityName}");
            return;
        }
        var selectedShow = availableShows[0]; // Alice selects the first show

        // 2. View available seats
        var availableSeats = selectedShow.GetScreen().GetSeats()
            .Where(seat => seat.GetStatus() == SeatStatus.AVAILABLE)
            .ToList();
        
        Console.WriteLine($"Available seats for '{selectedShow.GetMovie().GetTitle()}' at {selectedShow.GetStartTime()}: {string.Join(", ", availableSeats.Select(s => s.GetId()))}");

        // 3. Select seats
        var desiredSeats = new List<Seat> { availableSeats[2], availableSeats[3] };
        Console.WriteLine($"Alice selects seats: {string.Join(", ", desiredSeats.Select(s => s.GetId()))}");

        // 4. Book Tickets
        var booking = service.BookTickets(
            alice.GetId(),
            selectedShow.GetId(),
            desiredSeats,
            new CreditCardPaymentStrategy("1234-5678-9876-5432", "123")
        );

        if (booking != null)
        {
            Console.WriteLine("\n--- Booking Successful! ---");
            Console.WriteLine($"Booking ID: {booking.GetId()}");
            Console.WriteLine($"User: {booking.GetUser().GetName()}");
            Console.WriteLine($"Movie: {booking.GetShow().GetMovie().GetTitle()}");
            Console.WriteLine($"Seats: {string.Join(", ", booking.GetSeats().Select(s => s.GetId()))}");
            Console.WriteLine($"Total Amount: ${booking.GetTotalAmount()}");
            Console.WriteLine($"Payment Status: {booking.GetPayment().GetStatus()}");
        }
        else
        {
            Console.WriteLine("Booking failed.");
        }

        // 5. Verify seat status after booking
        Console.WriteLine("\nSeat status after Alice's booking:");
        foreach (var seat in desiredSeats)
        {
            Console.WriteLine($"Seat {seat.GetId()} status: {seat.GetStatus()}");
        }

        // 6. Shut down the system to release resources like the scheduler.
        service.Shutdown();
    }
}