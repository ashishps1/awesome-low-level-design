class BookCopy
{
    private readonly string id;
    private readonly LibraryItem item;
    private IItemState currentState;

    public BookCopy(string id, LibraryItem item)
    {
        this.id = id;
        this.item = item;
        this.currentState = new AvailableState();
        item.AddCopy(this);
    }

    public void Checkout(Member member) { currentState.Checkout(this, member); }
    public void ReturnItem() { currentState.ReturnItem(this); }
    public void PlaceHold(Member member) { currentState.PlaceHold(this, member); }

    public void SetState(IItemState state) { this.currentState = state; }
    public string GetId() { return id; }
    public LibraryItem GetItem() { return item; }
    public bool IsAvailable() { return currentState is AvailableState; }
}