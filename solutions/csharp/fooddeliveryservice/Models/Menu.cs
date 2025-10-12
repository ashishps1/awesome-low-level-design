class Menu
{
    private readonly Dictionary<string, MenuItem> items = new Dictionary<string, MenuItem>();

    public void AddItem(MenuItem item)
    {
        items[item.GetId()] = item;
    }

    public MenuItem GetItem(string id)
    {
        return items.ContainsKey(id) ? items[id] : null;
    }

    public Dictionary<string, MenuItem> GetItems()
    {
        return new Dictionary<string, MenuItem>(items);
    }
}