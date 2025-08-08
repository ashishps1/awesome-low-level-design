package hotelmanagementsystem;

import hotelmanagementsystem.enums.RoomStyle;
import hotelmanagementsystem.enums.RoomType;
import hotelmanagementsystem.factory.RoomFactory;
import hotelmanagementsystem.model.Guest;
import hotelmanagementsystem.observer.EmailNotifier;
import hotelmanagementsystem.observer.SmsNotifier;

import java.time.LocalDate;
import java.util.List;

public class HotelManagementDemo {
    public static void main(String[] args) {
        // 1. Setup Services and Facade
        RoomService roomService = new RoomService();
        BookingService bookingService = new BookingService();
        PaymentService paymentService = new PaymentService();

        // Register observers for the booking service
        bookingService.addObserver(new EmailNotifier());
        bookingService.addObserver(new SmsNotifier());

        HotelManagerFacade hotelManager = new HotelManagerFacade(roomService, bookingService, paymentService);

        // 2. Populate hotel with rooms using the Factory
        roomService.addRoom(RoomFactory.createRoom("101", "SINGLE", "STANDARD", 100));
        roomService.addRoom(RoomFactory.createRoom("102", "SINGLE", "DELUXE", 120));
        roomService.addRoom(RoomFactory.createRoom("201", "DOUBLE", "STANDARD", 150));
        roomService.addRoom(RoomFactory.createRoom("202", "DOUBLE", "DELUXE", 180));
        roomService.addRoom(RoomFactory.createRoom("301", "SUITE", "OCEAN_VIEW", 300));

        System.out.println("----------- SCENARIO 1: Successful Booking with Amenities -----------");
        Guest guest1 = new Guest("G123", "John Doe", "john.doe@example.com");
        hotelManager.bookRoom(
                guest1,
                RoomType.DOUBLE,
                RoomStyle.DELUXE,
                LocalDate.now(),
                LocalDate.now().plusDays(3),
                List.of("Breakfast", "Spa")
        );

        System.out.println("\n----------- SCENARIO 2: Attempt to book the same room (State Pattern) -----------");
        Guest guest2 = new Guest("G456", "Jane Smith", "jane.smith@example.com");
        hotelManager.bookRoom(
                guest2,
                RoomType.DOUBLE,
                RoomStyle.DELUXE,
                LocalDate.now(),
                LocalDate.now().plusDays(2),
                List.of()
        );

        System.out.println("\n----------- SCENARIO 3: Check-out and make room available again (State Pattern) -----------");
        // Room 202 was booked by John Doe
        System.out.println("Initial state of Room 202: " + roomService.findRoomByNumber("202"));
        hotelManager.checkOut("202");
        System.out.println("State of Room 202 after checkout: " + roomService.findRoomByNumber("202"));

        System.out.println("\n----------- SCENARIO 4: Book the now available room -----------");
        hotelManager.bookRoom(
                guest2,
                RoomType.DOUBLE,
                RoomStyle.DELUXE,
                LocalDate.now(),
                LocalDate.now().plusDays(2),
                List.of()
        );

        System.out.println("\n----------- SCENARIO 5: Room under maintenance (State Pattern) -----------");
        System.out.println("State of Room 101: " + roomService.findRoomByNumber("101"));
        roomService.findRoomByNumber("101").markForMaintenance();
        System.out.println("State of Room 101 after marking for maintenance: " + roomService.findRoomByNumber("101"));
        Guest guest3 = new Guest("G789", "Peter Jones", "peter.jones@example.com");
        hotelManager.bookRoom(guest3, RoomType.SINGLE, RoomStyle.STANDARD, LocalDate.now(), LocalDate.now().plusDays(1), List.of());
    }
}

