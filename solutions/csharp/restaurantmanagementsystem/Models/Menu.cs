class Menu
{
    private readonly Dictionary<string, MenuItem> items = new Dictionary<string, MenuItem>();

    public void AddItem(MenuItem item)
    {
        items[item.GetId()] = item;
    }

    public MenuItem GetItem(string id)
    {
        if (!items.TryGetValue(id, out MenuItem item))
        {
            throw new ArgumentException($"Menu item with ID {id} not found.");
        }
        return item;
    }
}