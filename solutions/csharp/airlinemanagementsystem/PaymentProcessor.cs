namespace AirlineManagementSystem
{
    public class PaymentProcessor
    {
        private static PaymentProcessor instance;

        private PaymentProcessor() { }

        public static PaymentProcessor Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new PaymentProcessor();
                }
                return instance;
            }
        }

        public void ProcessPayment(Payment payment)
        {
            payment.ProcessPayment();
        }
    }
}