package onlinestockbrokeragesystem

type User struct {
	UserID string
	Name   string
	Email  string
}

func NewUser(userID, name, email string) *User {
	return &User{
		UserID: userID,
		Name:   name,
		Email:  email,
	}
}
