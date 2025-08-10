class SearchByMenuKeywordStrategy : IRestaurantSearchStrategy
{
    private readonly string keyword;

    public SearchByMenuKeywordStrategy(string keyword)
    {
        this.keyword = keyword.ToLower();
    }

    public List<Restaurant> Filter(List<Restaurant> allRestaurants)
    {
        return allRestaurants
            .Where(r => r.GetMenu().GetItems().Values
                .Any(item => item.GetName().ToLower().Contains(keyword)))
            .ToList();
    }
}