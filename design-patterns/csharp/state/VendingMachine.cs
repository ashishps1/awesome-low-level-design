namespace State
{
    public class VendingMachine
    {
        private IMachineState currentState;
        private string selectedItem;
        private double insertedAmount;

        public VendingMachine()
        {
            this.currentState = new IdleState(); // Initial state
        }

        public void SetState(IMachineState newState)
        {
            this.currentState = newState;
        }

        public void SetSelectedItem(string itemCode)
        {
            this.selectedItem = itemCode;
        }

        public void SetInsertedAmount(double amount)
        {
            this.insertedAmount = amount;
        }

        public string GetSelectedItem()
        {
            return selectedItem;
        }

        public double GetInsertedAmount()
        {
            return insertedAmount;
        }

        public void SelectItem(string itemCode)
        {
            currentState.SelectItem(this, itemCode);
        }

        public void InsertCoin(double amount)
        {
            currentState.InsertCoin(this, amount);
        }

        public void DispenseItem()
        {
            currentState.DispenseItem(this);
        }

        public void Reset()
        {
            this.selectedItem = "";
            this.insertedAmount = 0.0;
            this.currentState = new IdleState();
        }
    }
} 