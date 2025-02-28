namespace VendingMachineApp
{
    public enum Coin
    {
        Penny = 1,
        Nickel = 5,
        Dime = 10,
        Quarter = 25
    }

    public static class CoinExtensions
    {
        public static double GetValue(this Coin coin)
        {
            return (int)coin / 100.0;
        }
    }
}