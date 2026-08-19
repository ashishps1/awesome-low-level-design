package splitwise

import "fmt"

type User struct {
	ID    string
	Name  string
	Email string
}

func NewUser(id, name, email string) *User {
	return &User{ID: id, Name: name, Email: email}
}

func (u *User) String() string {
	return fmt.Sprintf("%s(%s)", u.Name, u.ID)
}
