using System;
using System.Collections.Concurrent;
using System.Collections.Generic;

namespace RideSharingService
{
    public class RideService
    {
        private static RideService _instance;
        private readonly ConcurrentDictionary<int, Passenger> _passengers;
        private readonly ConcurrentDictionary<int, Driver> _drivers;
        private readonly ConcurrentDictionary<int, Ride> _rides;
        private readonly ConcurrentQueue<Ride> _requestedRides;

        private RideService()
        {
            _passengers = new ConcurrentDictionary<int, Passenger>();
            _drivers = new ConcurrentDictionary<int, Driver>();
            _rides = new ConcurrentDictionary<int, Ride>();
            _requestedRides = new ConcurrentQueue<Ride>();
        }

        public static RideService GetInstance()
        {
            if (_instance == null)
            {
                _instance = new RideService();
            }
            return _instance;
        }

        public void AddPassenger(Passenger passenger)
        {
            _passengers[passenger.Id] = passenger;
        }

        public void AddDriver(Driver driver)
        {
            _drivers[driver.Id] = driver;
        }

        public void RequestRide(Passenger passenger, Location source, Location destination)
        {
            var ride = new Ride(GenerateRideId(), passenger, null, source, destination, RideStatus.REQUESTED, 0.0);
            _requestedRides.Enqueue(ride);
            NotifyDrivers(ride);
        }

        public void AcceptRide(Driver driver, Ride ride)
        {
            if (ride.Status == RideStatus.REQUESTED)
            {
                ride.SetDriver(driver);
                ride.SetStatus(RideStatus.ACCEPTED);
                driver.Status = DriverStatus.BUSY;
                NotifyPassenger(ride);
            }
        }

        public void StartRide(Ride ride)
        {
            if (ride.Status == RideStatus.ACCEPTED)
            {
                ride.SetStatus(RideStatus.IN_PROGRESS);
                NotifyPassenger(ride);
            }
        }

        public void CompleteRide(Ride ride)
        {
            if (ride.Status == RideStatus.IN_PROGRESS)
            {
                ride.SetStatus(RideStatus.COMPLETED);
                ride.Driver.Status = DriverStatus.AVAILABLE;
                double fare = CalculateFare(ride);
                ride.SetFare(fare);
                ProcessPayment(ride, fare);
                NotifyPassenger(ride);
                NotifyDriver(ride);
            }
        }

        public void CancelRide(Ride ride)
        {
            if (ride.Status == RideStatus.REQUESTED || ride.Status == RideStatus.ACCEPTED)
            {
                ride.SetStatus(RideStatus.CANCELLED);
                if (ride.Driver != null)
                {
                    ride.Driver.Status = DriverStatus.AVAILABLE;
                }
                NotifyPassenger(ride);
                NotifyDriver(ride);
            }
        }

        private void NotifyDrivers(Ride ride)
        {
            foreach (var driver in _drivers.Values)
            {
                if (driver.Status == DriverStatus.AVAILABLE)
                {
                    double distance = CalculateDistance(driver.Location, ride.Source);
                    if (distance <= 5.0) // Notify drivers within 5 km radius
                    {
                        Console.WriteLine($"Notifying driver: {driver.Name} about ride request: {ride.Id}");
                    }
                }
            }
        }

        private void NotifyPassenger(Ride ride)
        {
            var passenger = ride.Passenger;
            string message = ride.Status switch
            {
                RideStatus.ACCEPTED => $"Your ride has been accepted by driver: {ride.Driver.Name}",
                RideStatus.IN_PROGRESS => "Your ride is in progress",
                RideStatus.COMPLETED => $"Your ride has been completed. Fare: ${ride.Fare}",
                RideStatus.CANCELLED => "Your ride has been cancelled",
                _ => ""
            };
            Console.WriteLine($"Notifying passenger: {passenger.Name} - {message}");
        }

        private void NotifyDriver(Ride ride)
        {
            if (ride.Driver != null)
            {
                string message = ride.Status switch
                {
                    RideStatus.COMPLETED => $"Ride completed. Fare: ${ride.Fare}",
                    RideStatus.CANCELLED => "Ride cancelled by passenger",
                    _ => ""
                };
                Console.WriteLine($"Notifying driver: {ride.Driver.Name} - {message}");
            }
        }

        private double CalculateFare(Ride ride)
        {
            const double baseFare = 2.0;
            const double perKmFare = 1.5;
            const double perMinuteFare = 0.25;

            double distance = CalculateDistance(ride.Source, ride.Destination);
            double duration = CalculateDuration(ride.Source, ride.Destination);

            double fare = baseFare + (distance * perKmFare) + (duration * perMinuteFare);
            return Math.Round(fare, 2); // Round to 2 decimal places
        }

        private double CalculateDistance(Location source, Location destination)
        {
            return new Random().NextDouble() * 20 + 1; // Random distance between 1 and 20 km
        }

        private double CalculateDuration(Location source, Location destination)
        {
            double distance = CalculateDistance(source, destination);
            return (distance / 30) * 60; // Assume average speed of 30 km/h, convert hours to minutes
        }

        private void ProcessPayment(Ride ride, double amount)
        {
            // Simulate payment processing
        }

        private int GenerateRideId()
        {
            return (int)(DateTimeOffset.UtcNow.ToUnixTimeSeconds());
        }

        public ConcurrentQueue<Ride> GetRequestedRides()
        {
            return _requestedRides;
        }
    }
}