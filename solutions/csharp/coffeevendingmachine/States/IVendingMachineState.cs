interface IVendingMachineState
{
    void SelectCoffee(CoffeeVendingMachine machine, Coffee coffee);
    void InsertMoney(CoffeeVendingMachine machine, int amount);
    void DispenseCoffee(CoffeeVendingMachine machine);
    void Cancel(CoffeeVendingMachine machine);
}