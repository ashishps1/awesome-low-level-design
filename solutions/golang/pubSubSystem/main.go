package main

import "github.com/ashishps1/awesome-low-level-design/pubSubSystem/src"

func main() {
	topic1 := src.NewTopic("topic-1")
	topic2 := src.NewTopic("topic-2")

	publisher1 := src.NewPublisher("pub1")
	publisher2 := src.NewPublisher("pub2")

	sub1 := src.NewPrintSubscriber("print-sub-1")
	sub2 := src.NewPrintSubscriber("print-sub-2")
	sub3 := src.NewPrintSubscriber("print-sub-3")

	publisher1.AddTopic(topic1)
	publisher2.AddTopic(topic2)

	topic1.Subscribe(sub1)
	topic1.Subscribe(sub2)
	topic2.Subscribe(sub3)

	publisher1.PublishToTopic(topic1, src.NewMessage("Message for topic 1"))

}
