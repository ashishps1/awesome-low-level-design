class BookingManager
{
    private readonly SeatLockManager seatLockManager;

    public BookingManager(SeatLockManager seatLockManager)
    {
        this.seatLockManager = seatLockManager;
    }

    public Booking CreateBooking(User user, Show show, List<Seat> seats, IPaymentStrategy paymentStrategy)
    {
        // 1. Lock the seats
        seatLockManager.LockSeats(show, seats, user.GetId());

        // 2. Calculate the total price
        double totalAmount = show.GetPricingStrategy().CalculatePrice(seats);

        // 3. Process Payment
        Payment payment = paymentStrategy.Pay(totalAmount);

        // 4. If payment is successful, create the booking
        if (payment.GetStatus() == PaymentStatus.SUCCESS)
        {
            Booking booking = new BookingBuilder()
                .SetUser(user)
                .SetShow(show)
                .SetSeats(seats)
                .SetTotalAmount(totalAmount)
                .SetPayment(payment)
                .Build();

            // 5. Confirm the booking (mark seats as BOOKED)
            booking.ConfirmBooking();

            // Clean up the lock map
            seatLockManager.UnlockSeats(show, seats, user.GetId());

            return booking;
        }
        else
        {
            Console.WriteLine("Payment failed. Please try again.");
            return null;
        }
    }
}