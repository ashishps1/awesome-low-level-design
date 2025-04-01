using System;

namespace CarRentalSystem
{
    public class Reservation
    {
        public string ReservationId { get; }
        public Customer Customer { get; }
        public Car Car { get; }
        public DateTime StartDate { get; }
        public DateTime EndDate { get; }
        public double TotalPrice { get; }

        public Reservation(string reservationId, Customer customer, Car car, DateTime startDate, DateTime endDate)
        {
            ReservationId = reservationId;
            Customer = customer;
            Car = car;
            StartDate = startDate;
            EndDate = endDate;
            TotalPrice = CalculateTotalPrice();
        }

        private double CalculateTotalPrice()
        {
            int daysRented = (EndDate - StartDate).Days + 1;
            return Car.RentalPricePerDay * daysRented;
        }
    }
}