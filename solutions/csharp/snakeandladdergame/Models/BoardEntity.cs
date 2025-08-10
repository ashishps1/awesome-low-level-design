abstract class BoardEntity
{
    protected readonly int start;
    protected readonly int end;

    public BoardEntity(int start, int end)
    {
        this.start = start;
        this.end = end;
    }

    public int GetStart()
    {
        return start;
    }

    public int GetEnd()
    {
        return end;
    }
}