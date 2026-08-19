package splitwise

import "fmt"

type Transaction struct {
	ID     string
	From   *User
	To     *User
	Amount float64
}

func NewTransaction(id string, from, to *User, amount float64) *Transaction {
	return &Transaction{ID: id, From: from, To: to, Amount: amount}
}

func (t *Transaction) String() string {
	return fmt.Sprintf("%s pays %s: $%.2f", t.From.Name, t.To.Name, t.Amount)
}
