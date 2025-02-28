using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace CarRentalSystem
{
    public class RentalSystem
    {
        private static RentalSystem instance;
        private readonly Dictionary<string, Car> cars;
        private readonly Dictionary<string, Reservation> reservations;
        private readonly IPaymentProcessor paymentProcessor;

        private RentalSystem()
        {
            cars = new Dictionary<string, Car>();
            reservations = new Dictionary<string, Reservation>();
            paymentProcessor = new CreditCardPaymentProcessor();  // Default to credit card payment processor
        }

        public static RentalSystem Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new RentalSystem();
                }
                return instance;
            }
        }

        public void AddCar(Car car)
        {
            cars[car.LicensePlate] = car;
        }

        public void RemoveCar(string licensePlate)
        {
            cars.Remove(licensePlate);
        }

        public List<Car> SearchCars(string make, string model, DateTime startDate, DateTime endDate)
        {
            return cars.Values
                .Where(car => car.Make.Equals(make, StringComparison.OrdinalIgnoreCase)
                              && car.Model.Equals(model, StringComparison.OrdinalIgnoreCase)
                              && car.Available && IsCarAvailable(car, startDate, endDate))
                .ToList();
        }

        private bool IsCarAvailable(Car car, DateTime startDate, DateTime endDate)
        {
            return reservations.Values
                .Where(reservation => reservation.Car == car)
                .All(reservation => endDate < reservation.StartDate || startDate > reservation.EndDate);
        }

        public Reservation MakeReservation(Customer customer, Car car, DateTime startDate, DateTime endDate)
        {
            if (IsCarAvailable(car, startDate, endDate))
            {
                var reservationId = GenerateReservationId();
                var reservation = new Reservation(reservationId, customer, car, startDate, endDate);
                reservations[reservationId] = reservation;
                car.SetAvailable(false);
                return reservation;
            }
            return null;
        }

        public void CancelReservation(string reservationId)
        {
            if (reservations.TryGetValue(reservationId, out var reservation))
            {
                reservations.Remove(reservationId);
                reservation.Car.SetAvailable(true);
            }
        }

        public bool ProcessPayment(Reservation reservation)
        {
            return paymentProcessor.ProcessPayment(reservation.TotalPrice);
        }

        private string GenerateReservationId()
        {
            return "RES" + Guid.NewGuid().ToString("N").Substring(0, 8).ToUpper();
        }
    }
}