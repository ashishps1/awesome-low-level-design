interface ISearchStrategy
{
    List<LibraryItem> Search(string query, List<LibraryItem> items);
}