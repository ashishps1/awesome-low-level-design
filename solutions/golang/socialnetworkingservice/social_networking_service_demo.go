package socialnetworkingservice

import (
	"fmt"
)

func Run() {
	service := GetSocialNetworkingService()

	// User registration
	user1 := NewUser("1", "John Doe", "john@example.com", "password", "profile1.jpg", "I love coding!")
	user2 := NewUser("2", "Jane Smith", "jane@example.com", "password", "profile2.jpg", "Exploring the world!")
	service.RegisterUser(user1)
	service.RegisterUser(user2)

	// User login
	loggedInUser := service.LoginUser("john@example.com", "password")
	if loggedInUser != nil {
		fmt.Println("User logged in:", loggedInUser.Name)
	} else {
		fmt.Println("Invalid email or password.")
	}

	// Send friend request
	service.SendFriendRequest(user1.ID, user2.ID)

	// Accept friend request
	service.AcceptFriendRequest(user2.ID, user1.ID)

	// Create posts
	post1 := NewPost("post1", user1.ID, "My first post!", []string{}, []string{}, []string{}, []Comment{})
	post2 := NewPost("post2", user2.ID, "Having a great day!", []string{}, []string{}, []string{}, []Comment{})
	service.CreatePost(post1)
	service.CreatePost(post2)

	// Like a post
	service.LikePost(user2.ID, post1.ID)

	// Comment on a post
	comment := NewComment("comment1", user2.ID, post1.ID, "Great post!")
	service.CommentOnPost(comment)

	// Get newsfeed
	newsfeed := service.GetNewsfeed(user1.ID)
	fmt.Println("Newsfeed:")
	for _, post := range newsfeed {
		fmt.Println("Post:", post.Content)
		fmt.Println("Likes:", len(post.Likes))
		fmt.Println("Comments:", len(post.Comments))
		fmt.Println()
	}

	// Get notifications
	notifications := service.GetNotifications(user1.ID)
	fmt.Println("Notifications:")
	for _, notification := range notifications {
		fmt.Println("Type:", notification.Type)
		fmt.Println("Content:", notification.Content)
		fmt.Println()
	}
}
