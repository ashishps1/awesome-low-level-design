namespace ATM
{
    public class Card
    {
        public string CardNumber { get; }
        public string Pin { get; }

        public Card(string cardNumber, string pin)
        {
            CardNumber = cardNumber;
            Pin = pin;
        }
    }
}