package atm

type DepositTransaction struct {
	BaseTransaction
}

func NewDepositTransaction(transactionID string, account *Account, amount float64) *DepositTransaction {
	return &DepositTransaction{
		BaseTransaction: BaseTransaction{
			TransactionID: transactionID,
			Account:       account,
			Amount:        amount,
		},
	}
}

func (t *DepositTransaction) Execute() error {
	return t.Account.Credit(t.Amount)
}
