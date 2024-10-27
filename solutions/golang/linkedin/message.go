package linkedin

import "time"

type Message struct {
	ID        string
	Sender    *User
	Receiver  *User
	Content   string
	Timestamp time.Time
}

func NewMessage(id string, sender, receiver *User, content string) *Message {
	return &Message{
		ID:        id,
		Sender:    sender,
		Receiver:  receiver,
		Content:   content,
		Timestamp: time.Now(),
	}
}
