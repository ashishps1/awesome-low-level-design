package atm

type WithdrawalTransaction struct {
	BaseTransaction
}

func NewWithdrawalTransaction(transactionID string, account *Account, amount float64) *WithdrawalTransaction {
	return &WithdrawalTransaction{
		BaseTransaction: BaseTransaction{
			TransactionID: transactionID,
			Account:       account,
			Amount:        amount,
		},
	}
}

func (t *WithdrawalTransaction) Execute() error {
	return t.Account.Debit(t.Amount)
}
