namespace VendingMachineApp
{
    public interface IVendingMachineState
    {
        void SelectProduct(Product product);
        void InsertCoin(Coin coin);
        void InsertNote(Note note);
        void DispenseProduct();
        void ReturnChange();
    }
}