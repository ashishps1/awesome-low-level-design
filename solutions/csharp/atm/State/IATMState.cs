interface IATMState
{
    void InsertCard(ATM atm, string cardNumber);
    void EnterPin(ATM atm, string pin);
    void SelectOperation(ATM atm, OperationType op, int amount = 0);
    void EjectCard(ATM atm);
}