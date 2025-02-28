namespace VendingMachineApp
{
    public class VendingMachineDemo
    {
        public static void Run()
        {
            VendingMachine vendingMachine = VendingMachine.GetInstance();

            // Add products to the inventory
            Product coke = new Product("Coke", 1.5);
            Product pepsi = new Product("Pepsi", 1.5);
            Product water = new Product("Water", 1.0);

            vendingMachine.Inventory.AddProduct(coke, 5);
            vendingMachine.Inventory.AddProduct(pepsi, 3);
            vendingMachine.Inventory.AddProduct(water, 2);

            // Select a product
            vendingMachine.SelectProduct(coke);

            // Insert coins
            vendingMachine.InsertCoin(Coin.Quarter);
            vendingMachine.InsertCoin(Coin.Quarter);
            vendingMachine.InsertCoin(Coin.Quarter);
            vendingMachine.InsertCoin(Coin.Quarter);

            // Insert a note
            vendingMachine.InsertNote(Note.Five);

            // Dispense the product
            vendingMachine.DispenseProduct();

            // Return change
            vendingMachine.ReturnChange();
        }
    }
}