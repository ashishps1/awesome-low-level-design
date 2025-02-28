using System;

namespace VendingMachineApp
{
    public class ReadyState : IVendingMachineState
    {
        private readonly VendingMachine _vendingMachine;

        public ReadyState(VendingMachine vendingMachine)
        {
            _vendingMachine = vendingMachine;
        }

        public void SelectProduct(Product product)
        {
            Console.WriteLine("Product already selected. Please make payment.");
        }

        public void InsertCoin(Coin coin)
        {
            _vendingMachine.AddCoin(coin);
            Console.WriteLine("Coin inserted: " + coin);
            CheckPaymentStatus();
        }

        public void InsertNote(Note note)
        {
            _vendingMachine.AddNote(note);
            Console.WriteLine("Note inserted: " + note);
            CheckPaymentStatus();
        }

        public void DispenseProduct()
        {
            Console.WriteLine("Please make payment first.");
        }

        public void ReturnChange()
        {
            double change = _vendingMachine.TotalPayment - _vendingMachine.SelectedProduct.Price;
            if (change > 0)
            {
                Console.WriteLine("Change returned: $" + change);
                _vendingMachine.ResetPayment();
            }
            else
            {
                Console.WriteLine("No change to return.");
            }
            _vendingMachine.SetState(_vendingMachine.GetIdleState());
        }

        private void CheckPaymentStatus()
        {
            if (_vendingMachine.TotalPayment >= _vendingMachine.SelectedProduct.Price)
            {
                _vendingMachine.SetState(_vendingMachine.GetDispenseState());
            }
        }
    }
}