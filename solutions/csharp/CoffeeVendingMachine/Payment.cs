namespace CoffeeVendingMachine;

public class Payment
{
    private readonly double _amount;

    public Payment(double amount)
    {
        _amount = amount;
    }
    
    public double GetAmount() => _amount;
}