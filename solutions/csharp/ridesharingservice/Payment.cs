namespace RideSharingService
{
    public class Payment
    {
        public int Id { get; set; }
        public Ride Ride { get; set; }
        public double Amount { get; set; }
        public PaymentStatus Status { get; set; }
    }
}