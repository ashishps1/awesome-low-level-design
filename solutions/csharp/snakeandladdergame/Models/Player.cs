class Player
{
    private readonly string name;
    private int position;

    public Player(string name)
    {
        this.name = name;
        this.position = 0;
    }

    public string GetName()
    {
        return name;
    }

    public int GetPosition()
    {
        return position;
    }

    public void SetPosition(int position)
    {
        this.position = position;
    }
}