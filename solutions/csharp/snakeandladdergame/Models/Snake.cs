class Snake : BoardEntity
{
    public Snake(int start, int end) : base(start, end)
    {
        if (start <= end)
        {
            throw new ArgumentException("Snake head must be at a higher position than its tail.");
        }
    }
}