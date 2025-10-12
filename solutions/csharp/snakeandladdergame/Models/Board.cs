class Board
{
    private readonly int size;
    private readonly Dictionary<int, int> snakesAndLadders;

    public Board(int size, List<BoardEntity> entities)
    {
        this.size = size;
        this.snakesAndLadders = new Dictionary<int, int>();

        foreach (BoardEntity entity in entities)
        {
            snakesAndLadders[entity.GetStart()] = entity.GetEnd();
        }
    }

    public int GetSize()
    {
        return size;
    }

    public int GetFinalPosition(int position)
    {
        if (snakesAndLadders.ContainsKey(position))
        {
            return snakesAndLadders[position];
        }
        return position;
    }
}