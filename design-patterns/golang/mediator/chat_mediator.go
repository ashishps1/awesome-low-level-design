package mediator

// ChatMediator is a concrete mediator that manages users
type ChatMediator struct {
	users []Colleague
}

// NewChatMediator creates a new ChatMediator
func NewChatMediator() *ChatMediator {
	return &ChatMediator{users: make([]Colleague, 0)}
}

// AddUser adds a user to the chat
func (m *ChatMediator) AddUser(user Colleague) {
	m.users = append(m.users, user)
	user.SetMediator(m)
}

// SendMessage sends a message from one user to all others
func (m *ChatMediator) SendMessage(message string, sender Colleague) {
	for _, user := range m.users {
		if user != sender {
			user.ReceiveMessage(sender.GetName() + ": " + message)
		}
	}
}
