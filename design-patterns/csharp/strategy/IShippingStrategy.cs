namespace Strategy
{
    public interface IShippingStrategy
    {
        double CalculateCost(Order order);
    }
} 