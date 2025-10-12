class ServiceChargeDecorator : BillDecorator
{
    private readonly double serviceCharge;

    public ServiceChargeDecorator(IBillComponent component, double charge) : base(component)
    {
        this.serviceCharge = charge;
    }

    public override double CalculateTotal()
    {
        return base.CalculateTotal() + serviceCharge;
    }

    public override string GetDescription()
    {
        return base.GetDescription() + ", Service Charge";
    }
}