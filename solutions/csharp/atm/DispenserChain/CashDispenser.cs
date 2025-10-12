class CashDispenser
{
    private readonly IDispenseChain chain;
    private readonly object dispenserLock = new object();

    public CashDispenser(IDispenseChain chain)
    {
        this.chain = chain;
    }

    public void DispenseCash(int amount)
    {
        lock (dispenserLock)
        {
            chain.Dispense(amount);
        }
    }

    public bool CanDispenseCash(int amount)
    {
        lock (dispenserLock)
        {
            if (amount % 10 != 0)
            {
                return false;
            }
            return chain.CanDispense(amount);
        }
    }
}