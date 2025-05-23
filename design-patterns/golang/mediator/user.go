package mediator

import "fmt"

// User represents a concrete colleague
type User struct {
	name     string
	mediator Mediator
}

// NewUser creates a new User
func NewUser(name string) *User {
	return &User{name: name}
}

func (u *User) SetMediator(mediator Mediator) {
	u.mediator = mediator
}

func (u *User) GetName() string {
	return u.name
}

func (u *User) ReceiveMessage(message string) {
	fmt.Printf("%s received: %s\n", u.name, message)
}

// SendMessage allows the user to send a message via the mediator
func (u *User) SendMessage(message string) {
	if u.mediator != nil {
		u.mediator.SendMessage(message, u)
	}
}
