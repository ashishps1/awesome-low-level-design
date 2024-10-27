package pubsubsystem

import "fmt"

type Publisher struct {
	Topics map[*Topic]struct{}
}

func NewPublisher() *Publisher {
	return &Publisher{Topics: make(map[*Topic]struct{})}
}

func (p *Publisher) RegisterTopic(topic *Topic) {
	p.Topics[topic] = struct{}{}
}

func (p *Publisher) Publish(topic *Topic, message *Message) {
	if _, exists := p.Topics[topic]; !exists {
		fmt.Printf("This publisher can't publish to topic: %s\n", topic.Name)
		return
	}
	topic.Publish(message)
}
