class Booking
{
    private readonly string id;
    private readonly User user;
    private readonly Show show;
    private readonly List<Seat> seats;
    private readonly double totalAmount;
    private readonly Payment payment;

    public Booking(string id, User user, Show show, List<Seat> seats, double totalAmount, Payment payment)
    {
        this.id = id;
        this.user = user;
        this.show = show;
        this.seats = seats;
        this.totalAmount = totalAmount;
        this.payment = payment;
    }

    public void ConfirmBooking()
    {
        foreach (var seat in seats)
        {
            seat.SetStatus(SeatStatus.BOOKED);
        }
    }

    public string GetId() { return id; }
    public User GetUser() { return user; }
    public Show GetShow() { return show; }
    public List<Seat> GetSeats() { return seats; }
    public double GetTotalAmount() { return totalAmount; }
    public Payment GetPayment() { return payment; }
}

class BookingBuilder
{
    private string id;
    private User user;
    private Show show;
    private List<Seat> seats;
    private double totalAmount;
    private Payment payment;

    public BookingBuilder SetId(string id)
    {
        this.id = id;
        return this;
    }

    public BookingBuilder SetUser(User user)
    {
        this.user = user;
        return this;
    }

    public BookingBuilder SetShow(Show show)
    {
        this.show = show;
        return this;
    }

    public BookingBuilder SetSeats(List<Seat> seats)
    {
        this.seats = seats;
        return this;
    }

    public BookingBuilder SetTotalAmount(double totalAmount)
    {
        this.totalAmount = totalAmount;
        return this;
    }

    public BookingBuilder SetPayment(Payment payment)
    {
        this.payment = payment;
        return this;
    }

    public Booking Build()
    {
        // Validations can be added here
        return new Booking(id ?? Guid.NewGuid().ToString(), user, show, seats, totalAmount, payment);
    }
}