package stackoverflow

import "fmt"

func Run() {
	system := NewStackOverflow()

	// Create users
	alice := system.CreateUser("Alice", "alice@example.com")
	bob := system.CreateUser("Bob", "bob@example.com")
	charlie := system.CreateUser("Charlie", "charlie@example.com")

	fmt.Println("Users created:", alice.Username, bob.Username, charlie.Username)

	// Alice asks a question about Java
	javaQuestion, err := system.AskQuestion(alice,
		"What is polymorphism in Java?",
		"Can someone explain polymorphism in Java with an example?",
		[]string{"java", "oop"})
	if err != nil {
		fmt.Printf("Error asking Java question: %v\n", err)
		return
	}

	// Bob answers Alice's question
	bobAnswer, err := system.AnswerQuestion(bob, javaQuestion,
		"Polymorphism in Java is the ability of an object to take on many forms...")
	if err != nil {
		fmt.Printf("Error answering question: %v\n", err)
		return
	}

	// Charlie comments on the question
	_, err = system.AddComment(charlie, javaQuestion,
		"Great question! I'm also interested in learning about this.")
	if err != nil {
		fmt.Printf("Error adding comment to question: %v\n", err)
		return
	}

	// Alice comments on Bob's answer
	_, err = system.AddComment(alice, bobAnswer,
		"Thanks for the explanation! Could you provide a code example?")
	if err != nil {
		fmt.Printf("Error adding comment to answer: %v\n", err)
		return
	}

	// Charlie votes on the question and answer
	if err := system.VoteQuestion(charlie, javaQuestion, 1); err != nil {
		fmt.Printf("Error voting on question: %v\n", err)
		return
	}
	if err := system.VoteAnswer(charlie, bobAnswer, 1); err != nil {
		fmt.Printf("Error voting on answer: %v\n", err)
		return
	}

	// Alice accepts Bob's answer
	if err := system.AcceptAnswer(bobAnswer); err != nil {
		fmt.Printf("Error accepting answer: %v\n", err)
		return
	}

	// Bob asks a Python question
	pythonQuestion, err := system.AskQuestion(bob,
		"How to use list comprehensions in Python?",
		"I'm new to Python and I've heard about list comprehensions. Can someone explain how to use them?",
		[]string{"python", "list-comprehension"})
	if err != nil {
		fmt.Printf("Error asking Python question: %v\n", err)
		return
	}

	// Alice answers Bob's question
	aliceAnswer, err := system.AnswerQuestion(alice, pythonQuestion,
		"List comprehensions in Python provide a concise way to create lists...")
	if err != nil {
		fmt.Printf("Error answering Python question: %v\n", err)
		return
	}

	// Charlie votes on Bob's question and Alice's answer
	if err := system.VoteQuestion(charlie, pythonQuestion, 1); err != nil {
		fmt.Printf("Error voting on Python question: %v\n", err)
		return
	}
	if err := system.VoteAnswer(charlie, aliceAnswer, 1); err != nil {
		fmt.Printf("Error voting on Alice's answer: %v\n", err)
		return
	}

	// Print out the current state
	fmt.Println("\n=== Java Question ===")
	fmt.Printf("Title: %s\n", javaQuestion.Title)
	fmt.Printf("Asked by: %s\n", javaQuestion.Author.Username)
	fmt.Printf("Tags: ")
	for _, tag := range javaQuestion.GetTags() {
		fmt.Printf("%s ", tag.Name)
	}
	fmt.Printf("\nVotes: %d\n", javaQuestion.GetVoteCount())
	fmt.Printf("Comments: %d\n", len(javaQuestion.GetComments()))

	fmt.Printf("\nAnswer by %s:\n", bobAnswer.Author.Username)
	fmt.Printf("Content: %s\n", bobAnswer.Content)
	fmt.Printf("Votes: %d\n", bobAnswer.GetVoteCount())
	fmt.Printf("Accepted: %v\n", bobAnswer.IsAccepted())
	fmt.Printf("Comments: %d\n", len(bobAnswer.GetComments()))

	fmt.Println("\n=== User Reputations ===")
	fmt.Printf("Alice: %d\n", alice.GetReputation())
	fmt.Printf("Bob: %d\n", bob.GetReputation())
	fmt.Printf("Charlie: %d\n", charlie.GetReputation())

	fmt.Println("\n=== Search Results ===")
	fmt.Println("Search Results for 'java':")
	javaResults := system.SearchQuestions("java")
	for _, q := range javaResults {
		fmt.Printf("- %s\n", q.Title)
	}

	fmt.Println("\nSearch Results for 'python':")
	pythonResults := system.SearchQuestions("python")
	for _, q := range pythonResults {
		fmt.Printf("- %s\n", q.Title)
	}

	fmt.Println("\n=== Bob's Questions ===")
	bobQuestions := system.GetQuestionsByUser(bob)
	for _, q := range bobQuestions {
		fmt.Printf("- %s\n", q.Title)
	}
}
