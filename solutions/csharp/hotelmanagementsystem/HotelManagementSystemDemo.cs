using System;

namespace HotelManagement
{
    public class HotelManagementSystemDemo
    {
        public static void Run()
        {
            var hotelManagementSystem = HotelManagementSystem.Instance;

            // Create guests
            var guest1 = new Guest("G001", "John Doe", "john@example.com", "1234567890");
            var guest2 = new Guest("G002", "Jane Smith", "jane@example.com", "9876543210");
            hotelManagementSystem.AddGuest(guest1);
            hotelManagementSystem.AddGuest(guest2);

            // Create rooms
            var room1 = new Room("R001", RoomType.SINGLE, 100.0);
            var room2 = new Room("R002", RoomType.DOUBLE, 200.0);
            hotelManagementSystem.AddRoom(room1);
            hotelManagementSystem.AddRoom(room2);

            // Book a room
            var checkInDate = DateTime.Now;
            var checkOutDate = checkInDate.AddDays(3);
            var reservation1 = hotelManagementSystem.BookRoom(guest1, room1, checkInDate, checkOutDate);
            if (reservation1 != null)
            {
                Console.WriteLine("Reservation created: " + reservation1.Id);
            }
            else
            {
                Console.WriteLine("Room not available for booking.");
            }

            // Check-in
            hotelManagementSystem.CheckIn(reservation1.Id);
            Console.WriteLine("Checked in: " + reservation1.Id);

            // Check-out and process payment
            var payment = new CreditCardPayment();
            hotelManagementSystem.CheckOut(reservation1.Id, payment);
            Console.WriteLine("Checked out: " + reservation1.Id);

            // Cancel a reservation
            hotelManagementSystem.CancelReservation(reservation1.Id);
            Console.WriteLine("Reservation cancelled: " + reservation1.Id);
        }
    }
}