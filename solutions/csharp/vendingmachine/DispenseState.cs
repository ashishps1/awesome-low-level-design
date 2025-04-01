using System;

namespace VendingMachineApp
{
    public class DispenseState : IVendingMachineState
    {
        private readonly VendingMachine _vendingMachine;

        public DispenseState(VendingMachine vendingMachine)
        {
            _vendingMachine = vendingMachine;
        }

        public void SelectProduct(Product product)
        {
            Console.WriteLine("Product already selected. Please collect the dispensed product.");
        }

        public void InsertCoin(Coin coin)
        {
            Console.WriteLine("Payment already made. Please collect the dispensed product.");
        }

        public void InsertNote(Note note)
        {
            Console.WriteLine("Payment already made. Please collect the dispensed product.");
        }

        public void DispenseProduct()
        {
            var product = _vendingMachine.SelectedProduct;
            if (product != null)
            {
                _vendingMachine.Inventory.UpdateQuantity(product, _vendingMachine.Inventory.GetQuantity(product) - 1);
                Console.WriteLine("Product dispensed: " + product.Name);
                _vendingMachine.SetState(_vendingMachine.GetReturnChangeState());
            }
        }

        public void ReturnChange()
        {
            Console.WriteLine("Please collect the dispensed product first.");
        }
    }
}