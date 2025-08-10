class SearchByAuthorStrategy : ISearchStrategy
{
    public List<LibraryItem> Search(string query, List<LibraryItem> items)
    {
        return items.Where(item => item.GetAuthorOrPublisher().ToLower().Contains(query.ToLower())).ToList();
    }
}