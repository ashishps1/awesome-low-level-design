class CoffeeVendingMachine
{
    private static CoffeeVendingMachine instance;
    private static readonly object lockObject = new object();
    private IVendingMachineState state;
    private Coffee selectedCoffee;
    private int moneyInserted;

    private CoffeeVendingMachine()
    {
        state = new ReadyState();
        moneyInserted = 0;
    }

    public static CoffeeVendingMachine GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new CoffeeVendingMachine();
                }
            }
        }
        return instance;
    }

    public void SelectCoffee(CoffeeType type, List<ToppingType> toppings)
    {
        // 1. Create the base coffee using the factory
        Coffee coffee = CoffeeFactory.CreateCoffee(type);

        // 2. Wrap it with decorators
        foreach (ToppingType topping in toppings)
        {
            switch (topping)
            {
                case ToppingType.EXTRA_SUGAR:
                    coffee = new ExtraSugarDecorator(coffee);
                    break;
                case ToppingType.CARAMEL_SYRUP:
                    coffee = new CaramelSyrupDecorator(coffee);
                    break;
            }
        }
        // Let the state handle the rest
        state.SelectCoffee(this, coffee);
    }

    public void InsertMoney(int amount) { state.InsertMoney(this, amount); }
    public void DispenseCoffee() { state.DispenseCoffee(this); }
    public void Cancel() { state.Cancel(this); }

    // Getters and Setters used by State objects
    public void SetState(IVendingMachineState state) { this.state = state; }
    public IVendingMachineState GetState() { return state; }
    public void SetSelectedCoffee(Coffee selectedCoffee) { this.selectedCoffee = selectedCoffee; }
    public Coffee GetSelectedCoffee() { return selectedCoffee; }
    public void SetMoneyInserted(int moneyInserted) { this.moneyInserted = moneyInserted; }
    public int GetMoneyInserted() { return moneyInserted; }

    public void Reset()
    {
        selectedCoffee = null;
        moneyInserted = 0;
    }
}