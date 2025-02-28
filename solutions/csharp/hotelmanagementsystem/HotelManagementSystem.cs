using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace HotelManagement
{
    public class HotelManagementSystem
    {
        private static HotelManagementSystem _instance;
        private readonly ConcurrentDictionary<string, Guest> _guests;
        private readonly ConcurrentDictionary<string, Room> _rooms;
        private readonly ConcurrentDictionary<string, Reservation> _reservations;

        private HotelManagementSystem()
        {
            _guests = new ConcurrentDictionary<string, Guest>();
            _rooms = new ConcurrentDictionary<string, Room>();
            _reservations = new ConcurrentDictionary<string, Reservation>();
        }

        public static HotelManagementSystem Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new HotelManagementSystem();
                }
                return _instance;
            }
        }

        public void AddGuest(Guest guest)
        {
            _guests[guest.Id] = guest;
        }

        public Guest GetGuest(string guestId)
        {
            _guests.TryGetValue(guestId, out var guest);
            return guest;
        }

        public void AddRoom(Room room)
        {
            _rooms[room.Id] = room;
        }

        public Room GetRoom(string roomId)
        {
            _rooms.TryGetValue(roomId, out var room);
            return room;
        }

        public Reservation BookRoom(Guest guest, Room room, DateTime checkInDate, DateTime checkOutDate)
        {
            lock (room)
            {
                if (room.Status == RoomStatus.AVAILABLE)
                {
                    room.Book();
                    var reservationId = GenerateReservationId();
                    var reservation = new Reservation(reservationId, guest, room, checkInDate, checkOutDate);
                    _reservations[reservationId] = reservation;
                    return reservation;
                }
                return null;
            }
        }

        public void CancelReservation(string reservationId)
        {
            lock (this)
            {
                if (_reservations.TryGetValue(reservationId, out var reservation))
                {
                    reservation.Cancel();
                    _reservations.TryRemove(reservationId, out _);
                }
            }
        }

        public void CheckIn(string reservationId)
        {
            lock (this)
            {
                if (_reservations.TryGetValue(reservationId, out var reservation) && reservation.Status == ReservationStatus.CONFIRMED)
                {
                    reservation.Room.CheckIn();
                }
                else
                {
                    throw new InvalidOperationException("Invalid reservation or reservation not confirmed.");
                }
            }
        }

        public void CheckOut(string reservationId, Payment payment)
        {
            lock (this)
            {
                if (_reservations.TryGetValue(reservationId, out var reservation) && reservation.Status == ReservationStatus.CONFIRMED)
                {
                    var room = reservation.Room;
                    var amount = room.Price * (reservation.CheckOutDate - reservation.CheckInDate).TotalDays;
                    if (payment.ProcessPayment(amount))
                    {
                        room.CheckOut();
                        _reservations.TryRemove(reservationId, out _);
                    }
                    else
                    {
                        throw new InvalidOperationException("Payment failed.");
                    }
                }
                else
                {
                    throw new InvalidOperationException("Invalid reservation or reservation not confirmed.");
                }
            }
        }

        private string GenerateReservationId()
        {
            return "RES" + Guid.NewGuid().ToString("N").Substring(0, 8).ToUpper();
        }
    }
}