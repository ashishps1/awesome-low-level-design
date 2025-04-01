package digitalwallet

import "sync"

type User struct {
	ID       string
	Name     string
	Email    string
	Password string
	accounts []*Account
	mu       sync.RWMutex
}

func NewUser(id, name, email, password string) *User {
	return &User{
		ID:       id,
		Name:     name,
		Email:    email,
		Password: password,
		accounts: make([]*Account, 0),
	}
}

func (u *User) AddAccount(account *Account) {
	u.mu.Lock()
	defer u.mu.Unlock()
	u.accounts = append(u.accounts, account)
}

func (u *User) RemoveAccount(account *Account) {
	u.mu.Lock()
	defer u.mu.Unlock()
	for i, acc := range u.accounts {
		if acc == account {
			u.accounts = append(u.accounts[:i], u.accounts[i+1:]...)
			break
		}
	}
}
