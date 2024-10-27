package linkedin

import "sync"

type User struct {
	ID           string
	Name         string
	Email        string
	Password     string
	Profile      *Profile
	connections  []*Connection
	inbox        []*Message
	sentMessages []*Message
	mu           sync.RWMutex
}

func NewUser(id, name, email, password string) *User {
	return &User{
		ID:           id,
		Name:         name,
		Email:        email,
		Password:     password,
		Profile:      NewProfile(),
		connections:  make([]*Connection, 0),
		inbox:        make([]*Message, 0),
		sentMessages: make([]*Message, 0),
	}
}

func (u *User) AddConnection(connection *Connection) {
	u.mu.Lock()
	defer u.mu.Unlock()
	u.connections = append(u.connections, connection)
}

func (u *User) AddMessage(message *Message, isSent bool) {
	u.mu.Lock()
	defer u.mu.Unlock()
	if isSent {
		u.sentMessages = append(u.sentMessages, message)
	} else {
		u.inbox = append(u.inbox, message)
	}
}
