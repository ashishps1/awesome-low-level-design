package src

type Subscriber interface {
	OnMessage(message Message)
}
