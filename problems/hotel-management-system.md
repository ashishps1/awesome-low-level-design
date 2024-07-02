# Designing a Hotel Management System

## Requirements
1. The hotel management system should allow guests to book rooms, check-in, and check-out.
2. The system should manage different types of rooms, such as single, double, deluxe, and suite.
3. The system should handle room availability and reservation status.
4. The system should allow the hotel staff to manage guest information, room assignments, and billing.
5. The system should support multiple payment methods, such as cash, credit card, and online payment.
6. The system should handle concurrent bookings and ensure data consistency.
7. The system should provide reporting and analytics features for hotel management.
8. The system should be scalable and handle a large number of rooms and guests.

## Implementations
#### [Java Implementation](../solutions/java/src/hotelmanagement/) 
#### [Python Implementation](../solutions/python/hotelmanagement/)

## Classes, Interfaces and Enumerations
1. The **Guest** class represents a guest of the hotel, with properties such as ID, name, email, and phone number.
2. The **Room** class represents a room in the hotel, with properties like ID, room type, price, and status. It provides methods to book, check-in, and check-out a room.
3. The **RoomType** enum represents the different types of rooms available in the hotel.
4. The **RoomStatus** enum represents the status of a room, which can be available, booked, or occupied.
5. The **Reservation** class represents a reservation made by a guest for a specific room and date range. It contains properties such as ID, guest, room, check-in date, check-out date, and status. It provides a method to cancel a reservation.
6. The **ReservationStatus** enum represents the status of a reservation, which can be confirmed or cancelled.
7. The **Payment** interface defines the contract for processing payments. It is implemented by concrete payment classes like CashPayment and CreditCardPayment.
8. The **HotelManagementSystem** class is the central component of the hotel management system. It follows the Singleton pattern to ensure only one instance of the system exists. It provides methods to add guests and rooms, book rooms, cancel reservations, check-in, check-out, and process payments. It also handles concurrent access to shared resources using synchronization.
9. The **HotelManagementSystemDemo** class demonstrates the usage of the hotel management system by creating guests, rooms, booking a room, checking in, checking out, and cancelling a reservation.