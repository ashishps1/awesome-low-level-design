package onlineauctionsystem

type User struct {
	ID       string
	Username string
	Email    string
}

func NewUser(id, username, email string) *User {
	return &User{
		ID:       id,
		Username: username,
		Email:    email,
	}
}
