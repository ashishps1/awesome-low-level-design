package socialnetworkingservice

import (
	"fmt"
	"log"
)

func Run() {
	socialNetwork := GetSocialNetwork()

	// Create users
	user1 := NewUser("1", "John Doe", "john@example.com", "password", "profile1.jpg", "I love coding!")
	user2 := NewUser("2", "Jane Smith", "jane@example.com", "password", "profile2.jpg", "Exploring the world!")

	// Register users
	if err := socialNetwork.RegisterUser(user1); err != nil {
		log.Printf("Failed to register user1: %v", err)
		return
	}
	if err := socialNetwork.RegisterUser(user2); err != nil {
		log.Printf("Failed to register user2: %v", err)
		return
	}

	// Login
	loggedInUser, err := socialNetwork.LoginUser("john@example.com", "password")
	if err != nil {
		log.Printf("Login failed: %v", err)
		return
	}
	fmt.Printf("User logged in: %s\n", loggedInUser.Name)

	// Send friend request
	if err := socialNetwork.SendFriendRequest(user1.ID, user2.ID); err != nil {
		log.Printf("Failed to send friend request: %v", err)
		return
	}

	// Accept friend request
	if err := socialNetwork.AcceptFriendRequest(user2.ID, user1.ID); err != nil {
		log.Printf("Failed to accept friend request: %v", err)
		return
	}

	// Create posts
	post1 := NewPost("post1", user1.ID, "My first post!", []string{}, []string{})
	post2 := NewPost("post2", user2.ID, "Having a great day!", []string{}, []string{})

	if err := socialNetwork.CreatePost(post1); err != nil {
		log.Printf("Failed to create post1: %v", err)
		return
	}
	if err := socialNetwork.CreatePost(post2); err != nil {
		log.Printf("Failed to create post2: %v", err)
		return
	}

	// Like and comment
	if err := socialNetwork.LikePost(user2.ID, post1.ID); err != nil {
		log.Printf("Failed to like post: %v", err)
		return
	}

	comment := NewComment("comment1", user2.ID, post1.ID, "Great post!")
	if err := socialNetwork.CommentOnPost(comment); err != nil {
		log.Printf("Failed to comment on post: %v", err)
		return
	}

	// Get newsfeed
	newsfeed, err := socialNetwork.GetNewsfeed(user1.ID)
	if err != nil {
		log.Printf("Failed to get newsfeed: %v", err)
		return
	}

	fmt.Println("\nNewsfeed:")
	for _, post := range newsfeed {
		fmt.Printf("Post: %s\n", post.Content)
		fmt.Printf("Likes: %d\n", len(post.GetLikes()))
		fmt.Printf("Comments: %d\n\n", len(post.GetComments()))
	}

	// Get notifications
	notifications, err := socialNetwork.GetNotifications(user1.ID)
	if err != nil {
		log.Printf("Failed to get notifications: %v", err)
		return
	}

	fmt.Println("Notifications:")
	for _, notification := range notifications {
		fmt.Printf("Type: %s\n", notification.Type)
		fmt.Printf("Content: %s\n\n", notification.Content)
	}
}
