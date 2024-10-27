package stackoverflow

import (
	"fmt"
	"strings"
)

// Run simulates the Stack Overflow system usage.
func Run() {
	// Initialize the StackOverflow system
	system := NewStackOverflow()

	// Create users
	alice := system.CreateUser("Alice", "alice@example.com")
	bob := system.CreateUser("Bob", "bob@example.com")
	charlie := system.CreateUser("Charlie", "charlie@example.com")

	// Alice asks a question
	javaQuestion := system.AskQuestion(alice, "What is polymorphism in Java?", "Can someone explain polymorphism in Java with an example?", []string{"java", "oop"})

	// Bob answers Alice's question
	bobAnswer := system.AnswerQuestion(bob, javaQuestion, "Polymorphism in Java is the ability of an object to take on many forms...")

	// Charlie comments on the question
	system.AddComment(charlie, javaQuestion, "Great question! I'm also interested in learning about this.")

	// Alice comments on Bob's answer
	system.AddComment(alice, bobAnswer, "Thanks for the explanation! Could you provide a code example?")

	// Charlie votes on the question and answer
	system.VoteQuestion(charlie, javaQuestion, 1) // Upvote
	system.VoteAnswer(charlie, bobAnswer, 1)      // Upvote

	// Alice accepts Bob's answer
	system.AcceptAnswer(bobAnswer)

	// Bob asks another question
	pythonQuestion := system.AskQuestion(bob, "How to use list comprehensions in Python?", "I'm new to Python and I've heard about list comprehensions. Can someone explain how to use them?", []string{"python", "list-comprehension"})

	// Alice answers Bob's question
	aliceAnswer := system.AnswerQuestion(alice, pythonQuestion, "List comprehensions in Python provide a concise way to create lists...")

	// Charlie votes on Bob's question and Alice's answer
	system.VoteQuestion(charlie, pythonQuestion, 1) // Upvote
	system.VoteAnswer(charlie, aliceAnswer, 1)      // Upvote

	// Print out the current state of the first question and its answer
	fmt.Printf("Question: %s\n", javaQuestion.Title)
	fmt.Printf("Asked by: %s\n", javaQuestion.Author.Username)
	fmt.Printf("Tags: %s\n", strings.Join(getTagNames(javaQuestion.Tags), ", "))
	fmt.Printf("Votes: %d\n", javaQuestion.GetVoteCount())
	fmt.Printf("Comments: %d\n", len(javaQuestion.GetComments()))

	fmt.Printf("\nAnswer by %s:\n", bobAnswer.Author.Username)
	fmt.Println(bobAnswer.Content)
	fmt.Printf("Votes: %d\n", bobAnswer.GetVoteCount())
	fmt.Printf("Accepted: %t\n", bobAnswer.IsAccepted)
	fmt.Printf("Comments: %d\n\n", len(bobAnswer.GetComments()))

	// Print user reputations
	fmt.Println("User Reputations:")
	fmt.Printf("Alice: %d\n", alice.Reputation)
	fmt.Printf("Bob: %d\n", bob.Reputation)
	fmt.Printf("Charlie: %d\n\n", charlie.Reputation)

	// Demonstrate search functionality
	fmt.Println("Search Results for 'java':")
	searchResults := system.SearchQuestions("java")
	for _, question := range searchResults {
		fmt.Println(question.Title)
	}

	fmt.Println("\nSearch Results for 'python':")
	searchResults = system.SearchQuestions("python")
	for _, question := range searchResults {
		fmt.Println(question.Title)
	}

	// Demonstrate retrieving questions by user
	fmt.Println("\nBob's Questions:")
	bobQuestions := system.GetQuestionsByUser(bob)
	for _, question := range bobQuestions {
		fmt.Println(question.Title)
	}
}

// Helper function to retrieve tag names as a slice of strings
func getTagNames(tags []*Tag) []string {
	tagNames := make([]string, len(tags))
	for i, tag := range tags {
		tagNames[i] = tag.Name
	}
	return tagNames
}
