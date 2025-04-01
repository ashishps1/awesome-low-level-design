package concertbookingsystem

type User struct {
	ID    string
	Name  string
	Email string
}

func NewUser(id, name, email string) *User {
	return &User{
		ID:    id,
		Name:  name,
		Email: email,
	}
}
