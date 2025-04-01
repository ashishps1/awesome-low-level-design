using System;
using System.Collections.Generic;

namespace AirlineManagementSystem
{
    public class Flight
    {
        public string FlightNumber { get; }
        public string Source { get; }
        public string Destination { get; }
        public DateTime DepartureTime { get; }
        public DateTime ArrivalTime { get; }
        public List<Seat> AvailableSeats { get; }

        public Flight(string flightNumber, string source, string destination, DateTime departureTime, DateTime arrivalTime)
        {
            FlightNumber = flightNumber;
            Source = source;
            Destination = destination;
            DepartureTime = departureTime;
            ArrivalTime = arrivalTime;
            AvailableSeats = new List<Seat>();
        }
    }
}