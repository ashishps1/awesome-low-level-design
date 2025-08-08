package movieticketbookingsystem;

import movieticketbookingsystem.enums.PaymentStatus;
import movieticketbookingsystem.entities.*;
import movieticketbookingsystem.strategy.payment.PaymentStrategy;

import java.util.List;
import java.util.Optional;

public class BookingManager {
    private final SeatLockManager seatLockManager;

    public BookingManager(SeatLockManager seatLockManager) {
        this.seatLockManager = seatLockManager;
    }

    public Optional<Booking> createBooking(User user, Show show, List<Seat> seats, PaymentStrategy paymentStrategy) {
        // 1. Lock the seats
        seatLockManager.lockSeats(show, seats, user.getId());

        // 2. Calculate the total price
        double totalAmount = show.getPricingStrategy().calculatePrice(seats);

        // 3. Process Payment
        Payment payment = paymentStrategy.pay(totalAmount);

        // 4. If payment is successful, create the booking
        if (payment.getStatus() == PaymentStatus.SUCCESS) {
            Booking booking = new Booking.BookingBuilder()
                    .setUser(user)
                    .setShow(show)
                    .setSeats(seats)
                    .setTotalAmount(totalAmount)
                    .setPayment(payment)
                    .build();

            // 5. Confirm the booking (mark seats as BOOKED)
            booking.confirmBooking();

            // Clean up the lock map
            seatLockManager.unlockSeats(show, seats, user.getId());

            return Optional.of(booking);
        } else {
            System.out.println("Payment failed. Please try again.");
            return Optional.empty();
        }
    }
}
