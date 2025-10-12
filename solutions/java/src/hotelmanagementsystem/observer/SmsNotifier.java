package hotelmanagementsystem.observer;

import hotelmanagementsystem.model.Booking;

public class SmsNotifier implements BookingObserver {
    @Override
    public void update(Booking booking) {
        System.out.println("--- SMS Notification ---");
        System.out.println("To: [Guest's Phone Number]"); // Assuming guest has a phone number
        System.out.println("Message: Booking " + booking.getBookingId() + " for Room " + booking.getRoom().getRoomNumber() + " confirmed!");
        System.out.println("------------------------");
    }
}
