package pubsubsystem

func Run() {
	// Create topics
	topic1 := NewTopic("Topic1")
	topic2 := NewTopic("Topic2")

	// Create publishers
	publisher1 := NewPublisher()
	publisher2 := NewPublisher()

	// Create subscribers
	subscriber1 := NewPrintSubscriber("Subscriber1")
	subscriber2 := NewPrintSubscriber("Subscriber2")
	subscriber3 := NewPrintSubscriber("Subscriber3")

	publisher1.RegisterTopic(topic1)
	publisher2.RegisterTopic(topic2)

	// Subscribe to topics
	topic1.AddSubscriber(subscriber1)
	topic1.AddSubscriber(subscriber2)
	topic2.AddSubscriber(subscriber2)
	topic2.AddSubscriber(subscriber3)

	// Publish messages
	publisher1.Publish(topic1, NewMessage("Message1 for Topic1"))
	publisher1.Publish(topic1, NewMessage("Message2 for Topic1"))
	publisher2.Publish(topic2, NewMessage("Message1 for Topic2"))

	// Unsubscribe from a topic
	topic1.RemoveSubscriber(subscriber2)

	// Publish more messages
	publisher1.Publish(topic1, NewMessage("Message3 for Topic1"))
	publisher2.Publish(topic2, NewMessage("Message2 for Topic2"))
}
