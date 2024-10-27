package onlinestockbrokeragesystem

type User struct {
	userId string
	name   string
	email  string
}

func NewUser(userId, name, email string) *User {
	return &User{userId: userId, name: name, email: email}
}
