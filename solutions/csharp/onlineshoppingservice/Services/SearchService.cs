class SearchService
{
    private readonly ICollection<Product> productCatalog;

    public SearchService(ICollection<Product> productCatalog)
    {
        this.productCatalog = productCatalog;
    }

    public List<Product> SearchByName(string name)
    {
        return productCatalog
            .Where(p => p.GetName().ToLower().Contains(name.ToLower()))
            .ToList();
    }

    public List<Product> SearchByCategory(ProductCategory category)
    {
        return productCatalog
            .Where(p => p.GetCategory() == category)
            .ToList();
    }
}