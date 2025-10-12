class Dice
{
    private readonly int minValue;
    private readonly int maxValue;
    private readonly Random random = new Random();

    public Dice(int minValue, int maxValue)
    {
        this.minValue = minValue;
        this.maxValue = maxValue;
    }

    public int Roll()
    {
        return (int)(random.NextDouble() * (maxValue - minValue + 1) + minValue);
    }
}