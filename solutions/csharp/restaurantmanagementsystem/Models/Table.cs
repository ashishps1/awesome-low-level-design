class Table
{
    private readonly int id;
    private readonly int capacity;
    private TableStatus status;

    public Table(int id, int capacity)
    {
        this.id = id;
        this.capacity = capacity;
        this.status = TableStatus.AVAILABLE;
    }

    public int GetId() => id;
    public int GetCapacity() => capacity;
    public TableStatus GetStatus() => status;
    public void SetStatus(TableStatus status) => this.status = status;
}