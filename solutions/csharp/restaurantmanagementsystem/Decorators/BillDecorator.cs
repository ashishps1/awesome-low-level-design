abstract class BillDecorator : IBillComponent
{
    protected IBillComponent wrapped;

    public BillDecorator(IBillComponent component)
    {
        this.wrapped = component;
    }

    public virtual double CalculateTotal()
    {
        return wrapped.CalculateTotal();
    }

    public virtual string GetDescription()
    {
        return wrapped.GetDescription();
    }
}