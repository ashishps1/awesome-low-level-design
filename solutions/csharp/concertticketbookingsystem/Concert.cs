using System;
using System.Collections.Generic;

namespace ConcertBookingSystem
{
    public class Concert
    {
        public string Id { get; }
        public string Artist { get; }
        public string Venue { get; }
        public DateTime DateTime { get; }
        public List<Seat> Seats { get; }

        public Concert(string id, string artist, string venue, DateTime dateTime, List<Seat> seats)
        {
            Id = id;
            Artist = artist;
            Venue = venue;
            DateTime = dateTime;
            Seats = seats;
        }
    }
}