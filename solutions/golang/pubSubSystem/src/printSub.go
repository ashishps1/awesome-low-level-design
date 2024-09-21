package src

import "fmt"

type PrintSubscriber struct {
	Name string
}

func NewPrintSubscriber(name string) *PrintSubscriber {
	return &PrintSubscriber{
		Name: name,
	}
}
func (p *PrintSubscriber) OnMessage(message Message) {
	fmt.Printf("[%s] %s\n", p.Name, message.ToString())
}
