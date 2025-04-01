package linkedin

import "time"

type Connection struct {
	User           *User
	ConnectionDate time.Time
}

func NewConnection(user *User) *Connection {
	return &Connection{
		User:           user,
		ConnectionDate: time.Now(),
	}
}
