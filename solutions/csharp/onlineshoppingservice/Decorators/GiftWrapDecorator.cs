class GiftWrapDecorator : ProductDecorator
{
    private const double GIFT_WRAP_COST = 5.00;

    public GiftWrapDecorator(Product product) : base(product) { }

    public override double GetPrice()
    {
        return base.GetPrice() + GIFT_WRAP_COST;
    }

    public override string GetDescription()
    {
        return base.GetDescription() + " (Gift Wrapped)";
    }
}