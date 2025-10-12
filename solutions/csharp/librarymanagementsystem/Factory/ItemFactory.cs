class ItemFactory
{
    public static LibraryItem CreateItem(ItemType type, string id, string title, string author)
    {
        switch (type)
        {
            case ItemType.BOOK:
                return new Book(id, title, author);
            case ItemType.MAGAZINE:
                return new Magazine(id, title, author);
            default:
                throw new ArgumentException("Unknown item type.");
        }
    }
}