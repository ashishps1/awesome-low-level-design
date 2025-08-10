class Bill
{
    private readonly IBillComponent component;

    public Bill(IBillComponent component)
    {
        this.component = component;
    }

    public void PrintBill()
    {
        Console.WriteLine("\n--- BILL ---");
        Console.WriteLine($"Description: {component.GetDescription()}");
        Console.WriteLine($"Total: ${component.CalculateTotal():F2}");
        Console.WriteLine("------------");
    }
}