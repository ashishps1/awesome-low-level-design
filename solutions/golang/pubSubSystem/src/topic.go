package src

type Topic struct {
	Name        string
	Messages    []Message
	Subscribers []Subscriber // make a map(set) to add remove subscriber functionality
}

func NewTopic(name string) *Topic {
	return &Topic{
		Name: name,
	}
}

func (t *Topic) AddMessage(m Message) {
	t.Messages = append(t.Messages, m)
	for _, sub := range t.Subscribers {
		sub.OnMessage(m)
	}
}

func (t *Topic) Subscribe(s Subscriber) {
	t.Subscribers = append(t.Subscribers, s)
}
