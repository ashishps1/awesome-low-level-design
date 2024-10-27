package linkedin

import (
	"fmt"
)

func Run() {
	service := GetLinkedInService()

	// Create users
	user1 := NewUser("1", "John Doe", "john@example.com", "password")
	user2 := NewUser("2", "Jane Smith", "jane@example.com", "password")

	service.RegisterUser(user1)
	service.RegisterUser(user2)

	// Login
	loggedInUser, err := service.LoginUser("john@example.com", "password")
	if err != nil {
		fmt.Printf("Login failed: %v\n", err)
		return
	}
	fmt.Printf("User logged in: %s\n", loggedInUser.Name)

	// Update profile
	loggedInUser.Profile.SetHeadline("Software Engineer")
	loggedInUser.Profile.SetSummary("Passionate about coding and problem-solving.")
	service.UpdateUserProfile(loggedInUser)

	// Send connection request
	service.SendConnectionRequest(user1, user2)

	// Accept connection request
	service.AcceptConnectionRequest(user2, user1)

	// Post job listing
	jobPosting := NewJobPosting(
		"1",
		"Software Developer",
		"We are hiring!",
		[]string{"Java", "Python"},
		"San Francisco",
	)
	service.PostJobListing(jobPosting)

	// Search users
	searchResults := service.SearchUsers("John")
	fmt.Println("\nSearch Results:")
	for _, user := range searchResults {
		fmt.Printf("Name: %s\n", user.Name)
		fmt.Printf("Headline: %s\n\n", user.Profile.Headline)
	}

	// Search job postings
	jobResults := service.SearchJobPostings("Software")
	fmt.Println("Job Posting Results:")
	for _, posting := range jobResults {
		fmt.Printf("Title: %s\n", posting.Title)
		fmt.Printf("Description: %s\n\n", posting.Description)
	}

	// Send message
	service.SendMessage(user1, user2, "Hi Jane, hope you're doing well!")

	// Get notifications
	notifications := service.GetNotifications(user2.ID)
	fmt.Println("Notifications:")
	for _, notification := range notifications {
		fmt.Printf("Type: %v\n", notification.Type)
		fmt.Printf("Content: %s\n\n", notification.Content)
	}
}
