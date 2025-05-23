package mediator

func main() {
	mediator := NewChatMediator()

	alice := NewUser("Alice")
	bob := NewUser("Bob")
	carol := NewUser("Carol")

	mediator.AddUser(alice)
	mediator.AddUser(bob)
	mediator.AddUser(carol)

	alice.SendMessage("Hello, everyone!")
	bob.SendMessage("Hi Alice!")
	carol.SendMessage("Hey folks!")
}
