abstract class Product
{
    protected string id;
    protected string name;
    protected string description;
    protected double price;
    protected ProductCategory category;

    public abstract string GetId();
    public abstract string GetName();
    public abstract string GetDescription();
    public abstract double GetPrice();
    public abstract ProductCategory GetCategory();
}

class BaseProduct : Product
{
    public BaseProduct(string id, string name, string description, double price, ProductCategory category)
    {
        this.id = id;
        this.name = name;
        this.description = description;
        this.price = price;
        this.category = category;
    }

    public override string GetId() { return id; }
    public override string GetName() { return name; }
    public override string GetDescription() { return description; }
    public override double GetPrice() { return price; }
    public override ProductCategory GetCategory() { return category; }
}

class ProductBuilder
{
    private readonly string name;
    private readonly double price;
    private string description = "";
    private ProductCategory category;

    public ProductBuilder(string name, double price)
    {
        this.name = name;
        this.price = price;
    }

    public ProductBuilder WithDescription(string description)
    {
        this.description = description;
        return this;
    }

    public ProductBuilder WithCategory(ProductCategory category)
    {
        this.category = category;
        return this;
    }

    public Product Build()
    {
        return new BaseProduct(Guid.NewGuid().ToString(), name, description, price, category);
    }
}