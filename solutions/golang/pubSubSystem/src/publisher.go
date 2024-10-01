package src

type Publisher struct {
	Name   string
	Topics []*Topic
}

func NewPublisher(name string) *Publisher {
	return &Publisher{
		Name: name,
	}
}

func (p *Publisher) AddTopic(topic *Topic) {
	p.Topics = append(p.Topics, topic)
}

func (p *Publisher) PublishToTopic(topic *Topic, msg Message) {
	for _, t := range p.Topics {
		if t.Name == topic.Name {
			t.AddMessage(msg)
		}
	}
}
