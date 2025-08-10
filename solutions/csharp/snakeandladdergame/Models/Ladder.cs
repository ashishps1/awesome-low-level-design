class Ladder : BoardEntity
{
    public Ladder(int start, int end) : base(start, end)
    {
        if (start >= end)
        {
            throw new ArgumentException("Ladder bottom must be at a lower position than its top.");
        }
    }
}