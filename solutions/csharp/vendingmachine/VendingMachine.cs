class VendingMachine
{
    private static readonly VendingMachine INSTANCE = new VendingMachine();
    private readonly Inventory inventory = new Inventory();
    private VendingMachineState currentState;
    private int balance = 0;
    private string selectedItemCode;

    public VendingMachine()
    {
        currentState = new IdleState(this);
    }

    public static VendingMachine GetInstance()
    {
        return INSTANCE;
    }

    public void InsertCoin(Coin coin)
    {
        currentState.InsertCoin(coin);
    }

    public Item AddItem(string code, string name, int price, int quantity)
    {
        Item item = new Item(code, name, price);
        inventory.AddItem(code, item, quantity);
        return item;
    }

    public void SelectItem(string code)
    {
        currentState.SelectItem(code);
    }

    public void Dispense()
    {
        currentState.Dispense();
    }

    public void DispenseItem()
    {
        Item item = inventory.GetItem(selectedItemCode);
        if (balance >= item.GetPrice())
        {
            inventory.ReduceStock(selectedItemCode);
            balance -= item.GetPrice();
            Console.WriteLine("Dispensed: " + item.GetName());
            if (balance > 0)
            {
                Console.WriteLine("Returning change: " + balance);
            }
        }
        Reset();
        SetState(new IdleState(this));
    }

    public void RefundBalance()
    {
        Console.WriteLine("Refunding: " + balance);
        balance = 0;
    }

    public void Reset()
    {
        selectedItemCode = null;
        balance = 0;
    }

    public void AddBalance(int value)
    {
        balance += value;
    }

    public Item GetSelectedItem()
    {
        return inventory.GetItem(selectedItemCode);
    }

    public void SetSelectedItemCode(string code)
    {
        this.selectedItemCode = code;
    }

    public void SetState(VendingMachineState state)
    {
        this.currentState = state;
    }

    public Inventory GetInventory() { return inventory; }
    public int GetBalance() { return balance; }
}