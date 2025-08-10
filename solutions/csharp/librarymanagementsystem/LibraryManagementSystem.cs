class LibraryManagementSystem
{
    private static readonly LibraryManagementSystem instance = new LibraryManagementSystem();
    private readonly Dictionary<string, LibraryItem> catalog = new Dictionary<string, LibraryItem>();
    private readonly Dictionary<string, Member> members = new Dictionary<string, Member>();
    private readonly Dictionary<string, BookCopy> copies = new Dictionary<string, BookCopy>();

    private LibraryManagementSystem() { }
    public static LibraryManagementSystem GetInstance() { return instance; }

    public List<BookCopy> AddItem(ItemType type, string id, string title, string author, int numCopies)
    {
        var bookCopies = new List<BookCopy>();
        var item = ItemFactory.CreateItem(type, id, title, author);
        catalog[id] = item;
        
        for (int i = 0; i < numCopies; i++)
        {
            string copyId = $"{id}-c{i + 1}";
            var copy = new BookCopy(copyId, item);
            copies[copyId] = copy;
            bookCopies.Add(copy);
        }
        
        Console.WriteLine($"Added {numCopies} copies of '{title}'");
        return bookCopies;
    }

    public Member AddMember(string id, string name)
    {
        var member = new Member(id, name);
        members[id] = member;
        return member;
    }

    public void Checkout(string memberId, string copyId)
    {
        if (members.TryGetValue(memberId, out var member) && copies.TryGetValue(copyId, out var copy))
        {
            copy.Checkout(member);
        }
        else
        {
            Console.WriteLine("Error: Invalid member or copy ID.");
        }
    }

    public void ReturnItem(string copyId)
    {
        if (copies.TryGetValue(copyId, out var copy))
        {
            copy.ReturnItem();
        }
        else
        {
            Console.WriteLine("Error: Invalid copy ID.");
        }
    }

    public void PlaceHold(string memberId, string itemId)
    {
        if (members.TryGetValue(memberId, out var member) && catalog.TryGetValue(itemId, out var item))
        {
            var checkedOutCopy = item.GetCopies().FirstOrDefault(c => !c.IsAvailable());
            checkedOutCopy?.PlaceHold(member);
        }
    }

    public List<LibraryItem> Search(string query, ISearchStrategy strategy)
    {
        return strategy.Search(query, catalog.Values.ToList());
    }

    public void PrintCatalog()
    {
        Console.WriteLine("\n--- Library Catalog ---");
        foreach (var item in catalog.Values)
        {
            Console.WriteLine($"ID: {item.GetId()}, Title: {item.GetTitle()}, " +
                            $"Author/Publisher: {item.GetAuthorOrPublisher()}, " +
                            $"Available: {item.GetAvailableCopyCount()}");
        }
        Console.WriteLine("-----------------------\n");
    }
}