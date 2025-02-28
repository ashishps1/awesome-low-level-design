using System;

namespace VendingMachineApp
{
    public class VendingMachine
    {
        private static VendingMachine _instance;
        public Inventory Inventory { get; private set; }
        private IVendingMachineState _idleState;
        private IVendingMachineState _readyState;
        private IVendingMachineState _dispenseState;
        private IVendingMachineState _returnChangeState;
        private IVendingMachineState _currentState;
        public Product SelectedProduct { get; private set; }
        public double TotalPayment { get; private set; }

        private VendingMachine()
        {
            Inventory = new Inventory();
            _idleState = new IdleState(this);
            _readyState = new ReadyState(this);
            _dispenseState = new DispenseState(this);
            _returnChangeState = new ReturnChangeState(this);
            _currentState = _idleState;
            SelectedProduct = null;
            TotalPayment = 0.0;
        }

        public static VendingMachine GetInstance()
        {
            if (_instance == null)
            {
                _instance = new VendingMachine();
            }
            return _instance;
        }

        public void SelectProduct(Product product)
        {
            _currentState.SelectProduct(product);
        }

        public void InsertCoin(Coin coin)
        {
            _currentState.InsertCoin(coin);
        }

        public void InsertNote(Note note)
        {
            _currentState.InsertNote(note);
        }

        public void DispenseProduct()
        {
            _currentState.DispenseProduct();
        }

        public void ReturnChange()
        {
            _currentState.ReturnChange();
        }

        public void SetState(IVendingMachineState state)
        {
            _currentState = state;
        }

        public IVendingMachineState GetIdleState() => _idleState;
        public IVendingMachineState GetReadyState() => _readyState;
        public IVendingMachineState GetDispenseState() => _dispenseState;
        public IVendingMachineState GetReturnChangeState() => _returnChangeState;

        public void SetSelectedProduct(Product product)
        {
            SelectedProduct = product;
        }

        public void ResetSelectedProduct()
        {
            SelectedProduct = null;
        }

        public void AddCoin(Coin coin)
        {
            TotalPayment += coin.GetValue();
        }

        public void AddNote(Note note)
        {
            TotalPayment += note.GetValue();
        }

        public void ResetPayment()
        {
            TotalPayment = 0.0;
        }
    }
}