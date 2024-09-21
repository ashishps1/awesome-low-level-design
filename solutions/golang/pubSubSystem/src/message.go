package src

import (
	"fmt"
	"time"
)

type Message struct {
	data     string
	createAt time.Time
}

func NewMessage(data string) Message {
	return Message{data: data, createAt: time.Now()}
}

func (m Message) ToString() string {
	return fmt.Sprintf("%s,%s", m.data, m.createAt.Format(time.RFC3339))
}
