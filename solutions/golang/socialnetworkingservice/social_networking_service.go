package socialnetworkingservice

import (
	"fmt"
	"sort"
	"sync"
	"time"
)

type SocialNetwork struct {
	users         map[string]*User
	posts         map[string]*Post
	notifications map[string][]*Notification
	mu            sync.RWMutex
}

var (
	instance *SocialNetwork
	once     sync.Once
)

func GetSocialNetwork() *SocialNetwork {
	once.Do(func() {
		instance = &SocialNetwork{
			users:         make(map[string]*User),
			posts:         make(map[string]*Post),
			notifications: make(map[string][]*Notification),
		}
	})
	return instance
}

func (sn *SocialNetwork) RegisterUser(user *User) error {
	sn.mu.Lock()
	defer sn.mu.Unlock()

	if _, exists := sn.users[user.ID]; exists {
		return fmt.Errorf("user with ID %s already exists", user.ID)
	}
	sn.users[user.ID] = user
	return nil
}

func (sn *SocialNetwork) LoginUser(email, password string) (*User, error) {
	sn.mu.RLock()
	defer sn.mu.RUnlock()

	for _, user := range sn.users {
		if user.Email == email && user.Password == password {
			return user, nil
		}
	}
	return nil, fmt.Errorf("invalid email or password")
}

func (sn *SocialNetwork) UpdateUserProfile(user *User) {
	sn.mu.Lock()
	defer sn.mu.Unlock()
	sn.users[user.ID] = user
}

func (sn *SocialNetwork) SendFriendRequest(senderID, receiverID string) error {
	sn.mu.Lock()
	defer sn.mu.Unlock()

	receiver, exists := sn.users[receiverID]
	if !exists {
		return fmt.Errorf("receiver not found")
	} else {
		fmt.Printf(receiver.ID)
	}

	notification := NewNotification(
		fmt.Sprintf("notif-%d", time.Now().UnixNano()),
		receiverID,
		NotificationTypeFriendRequest,
		fmt.Sprintf("Friend request from %s", senderID),
	)

	sn.addNotification(receiverID, notification)
	return nil
}

func (sn *SocialNetwork) AcceptFriendRequest(userID, friendID string) error {
	sn.mu.Lock()
	defer sn.mu.Unlock()

	user, exists1 := sn.users[userID]
	friend, exists2 := sn.users[friendID]

	if !exists1 || !exists2 {
		return fmt.Errorf("user or friend not found")
	}

	user.AddFriend(friendID)
	friend.AddFriend(userID)

	notification := NewNotification(
		fmt.Sprintf("notif-%d", time.Now().UnixNano()),
		friendID,
		NotificationTypeFriendRequestAccepted,
		fmt.Sprintf("Friend request accepted by %s", userID),
	)

	sn.addNotification(friendID, notification)
	return nil
}

func (sn *SocialNetwork) CreatePost(post *Post) error {
	sn.mu.Lock()
	defer sn.mu.Unlock()

	user, exists := sn.users[post.UserID]
	if !exists {
		return fmt.Errorf("user not found")
	}

	sn.posts[post.ID] = post
	user.AddPost(post)
	return nil
}

func (sn *SocialNetwork) GetNewsfeed(userID string) ([]*Post, error) {
	sn.mu.RLock()
	defer sn.mu.RUnlock()

	user, exists := sn.users[userID]
	if !exists {
		return nil, fmt.Errorf("user not found")
	}

	var newsfeed []*Post

	// Add user's own posts
	newsfeed = append(newsfeed, user.GetPosts()...)

	// Add friends' posts
	for friendID := range user.friends {
		if friend, ok := sn.users[friendID]; ok {
			newsfeed = append(newsfeed, friend.GetPosts()...)
		}
	}

	// Sort by timestamp (newest first)
	sort.Slice(newsfeed, func(i, j int) bool {
		return newsfeed[i].Timestamp.After(newsfeed[j].Timestamp)
	})

	return newsfeed, nil
}

func (sn *SocialNetwork) LikePost(userID, postID string) error {
	sn.mu.Lock()
	defer sn.mu.Unlock()

	post, exists := sn.posts[postID]
	if !exists {
		return fmt.Errorf("post not found")
	}

	if added := post.AddLike(userID); added {
		notification := NewNotification(
			fmt.Sprintf("notif-%d", time.Now().UnixNano()),
			post.UserID,
			NotificationTypeLike,
			fmt.Sprintf("Your post was liked by %s", userID),
		)
		sn.addNotification(post.UserID, notification)
	}
	return nil
}

func (sn *SocialNetwork) CommentOnPost(comment *Comment) error {
	sn.mu.Lock()
	defer sn.mu.Unlock()

	post, exists := sn.posts[comment.PostID]
	if !exists {
		return fmt.Errorf("post not found")
	}

	post.AddComment(comment)

	notification := NewNotification(
		fmt.Sprintf("notif-%d", time.Now().UnixNano()),
		post.UserID,
		NotificationTypeComment,
		fmt.Sprintf("Your post received a comment from %s", comment.UserID),
	)
	sn.addNotification(post.UserID, notification)
	return nil
}

func (sn *SocialNetwork) GetNotifications(userID string) ([]*Notification, error) {
	sn.mu.RLock()
	defer sn.mu.RUnlock()

	if _, exists := sn.users[userID]; !exists {
		return nil, fmt.Errorf("user not found")
	}

	return sn.notifications[userID], nil
}

func (sn *SocialNetwork) addNotification(userID string, notification *Notification) {
	sn.notifications[userID] = append(sn.notifications[userID], notification)
}
