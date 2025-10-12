class SearchByTitleStrategy : ISearchStrategy
{
    public List<LibraryItem> Search(string query, List<LibraryItem> items)
    {
        return items.Where(item => item.GetTitle().ToLower().Contains(query.ToLower())).ToList();
    }
}