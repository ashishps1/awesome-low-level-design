package splitwise

type Transaction struct {
	ID       string
	Sender   *User
	Receiver *User
	Amount   float64
}

func NewTransaction(id string, sender, receiver *User, amount float64) *Transaction {
	return &Transaction{ID: id, Sender: sender, Receiver: receiver, Amount: amount}
}
