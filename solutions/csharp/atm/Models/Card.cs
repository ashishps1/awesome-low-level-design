class Card
{
    private readonly string cardNumber;
    private readonly string pin;

    public Card(string cardNumber, string pin)
    {
        this.cardNumber = cardNumber;
        this.pin = pin;
    }

    public string GetCardNumber() => cardNumber;
    public string GetPin() => pin;
}