package taskmanagementsystem

type User struct {
	Id    string
	Name  string
	Email string
}

func NewUser(id, name, email string) *User {
	return &User{Id: id, Name: name, Email: email}
}

func (u *User) GetId() string {
	return u.Id
}

func (u *User) GetName() string {
	return u.Name
}
