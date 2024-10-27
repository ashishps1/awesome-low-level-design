package stackoverflow

type User struct {
	ID         int
	Username   string
	Email      string
	Reputation int
}

func NewUser(id int, username, email string) *User {
	return &User{ID: id, Username: username, Email: email, Reputation: 0}
}

func (u *User) UpdateReputation(value int) {
	u.Reputation += value
	if u.Reputation < 0 {
		u.Reputation = 0
	}
}
