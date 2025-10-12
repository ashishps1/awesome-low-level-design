class TaxDecorator : BillDecorator
{
    private readonly double taxRate;

    public TaxDecorator(IBillComponent component, double taxRate) : base(component)
    {
        this.taxRate = taxRate;
    }

    public override double CalculateTotal()
    {
        return base.CalculateTotal() * (1 + taxRate);
    }

    public override string GetDescription()
    {
        return base.GetDescription() + $", Tax @{taxRate * 100}%";
    }
}