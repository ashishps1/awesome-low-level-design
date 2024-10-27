package onlinestockbrokeragesystem

type Account struct {
	accountId string
	user      *User
	balance   float64
	portfolio *Portfolio
}

func NewAccount(accountId string, user *User, initialBalance float64) *Account {
	return &Account{
		accountId: accountId,
		user:      user,
		balance:   initialBalance,
		portfolio: NewPortfolio(),
	}
}

func (a *Account) Deposit(amount float64) {
	a.balance += amount
}

func (a *Account) Withdraw(amount float64) error {
	if a.balance >= amount {
		a.balance -= amount
		return nil
	}
	return &InsufficientFundsException{"Insufficient funds in the account."}
}

func (a *Account) GetBalance() float64 {
	return a.balance
}

func (a *Account) GetPortfolio() *Portfolio {
	return a.portfolio
}
