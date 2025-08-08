package hotelmanagementsystem;

import hotelmanagementsystem.decorator.Bookable;
import hotelmanagementsystem.decorator.BreakfastDecorator;
import hotelmanagementsystem.decorator.RoomBooking;
import hotelmanagementsystem.decorator.SpaDecorator;
import hotelmanagementsystem.enums.RoomStyle;
import hotelmanagementsystem.enums.RoomType;
import hotelmanagementsystem.model.Booking;
import hotelmanagementsystem.model.Guest;
import hotelmanagementsystem.model.Room;
import hotelmanagementsystem.specification.RoomAvailableSpecification;
import hotelmanagementsystem.specification.RoomStyleSpecification;
import hotelmanagementsystem.specification.RoomTypeSpecification;
import hotelmanagementsystem.specification.Specification;

import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

public class HotelManagerFacade {
    private final RoomService roomService;
    private final BookingService bookingService;
    private final PaymentService paymentService;

    public HotelManagerFacade(RoomService roomService, BookingService bookingService, PaymentService paymentService) {
        this.roomService = roomService;
        this.bookingService = bookingService;
        this.paymentService = paymentService;
    }

    public Booking bookRoom(Guest guest, RoomType type, RoomStyle style, LocalDate start, LocalDate end, List<String> amenities) {
        // 1. Find an available room using the Specification pattern
        Specification<Room> searchSpec = new RoomAvailableSpecification()
                .and(new RoomTypeSpecification(type))
                .and(new RoomStyleSpecification(style));

        Optional<Room> availableRoom = roomService.findRooms(searchSpec).stream().findFirst();

        if (availableRoom.isPresent()) {
            Room room = availableRoom.get();

            // 2. Create a booking
            Booking booking = bookingService.createBooking(guest, room, start, end);

            // 3. Use Decorator pattern to calculate total cost with amenities
            Bookable bookable = new RoomBooking(room);
            for (String amenity : amenities) {
                if ("breakfast".equalsIgnoreCase(amenity)) {
                    bookable = new BreakfastDecorator(bookable);
                } else if ("spa".equalsIgnoreCase(amenity)) {
                    bookable = new SpaDecorator(bookable);
                }
            }

            System.out.println("Total Cost: " + bookable.getDescription() + " = $" + String.format("%.2f", bookable.getCost()));

            // 4. Process payment
            paymentService.processPayment(bookable.getCost());

            return booking;
        } else {
            System.out.println("Sorry, no rooms available matching your criteria.");
            return null;
        }
    }

    public void checkIn(String bookingId) {
        // In a real system, you'd fetch the booking by ID
        // For this demo, we'll find a room and check it in
        System.out.println("Check-in process for booking ID (not implemented for demo): " + bookingId);
    }

    public void checkOut(String roomNumber) {
        Room room = roomService.findRoomByNumber(roomNumber);
        if(room != null) {
            room.checkOut();
        } else {
            System.out.println("Room " + roomNumber + " not found.");
        }
    }
}
