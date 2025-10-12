interface IDispenseChain
{
    void SetNextChain(IDispenseChain nextChain);
    void Dispense(int amount);
    bool CanDispense(int amount);
}