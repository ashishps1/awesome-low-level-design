using System;
using System.Collections.Generic;

namespace MovieTicketBookingSystem
{
    public class Show
    {
        public string Id { get; }
        public Movie Movie { get; }
        public Theater Theater { get; }
        public DateTime StartTime { get; }
        public DateTime EndTime { get; }
        public Dictionary<string, Seat> Seats { get; }

        public Show(string id, Movie movie, Theater theater, DateTime startTime, DateTime endTime, Dictionary<string, Seat> seats)
        {
            Id = id;
            Movie = movie;
            Theater = theater;
            StartTime = startTime;
            EndTime = endTime;
            Seats = seats;
        }
    }
}