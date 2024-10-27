package socialnetworkingservice

import (
	"fmt"
	"sync"
	"time"
)

type SocialNetworkingService struct {
	users         map[string]*User
	posts         map[string]*Post
	notifications map[string][]Notification
	mu            sync.Mutex
}

var instance *SocialNetworkingService
var once sync.Once

func GetSocialNetworkingService() *SocialNetworkingService {
	once.Do(func() {
		instance = &SocialNetworkingService{
			users:         make(map[string]*User),
			posts:         make(map[string]*Post),
			notifications: make(map[string][]Notification),
		}
	})
	return instance
}

func (s *SocialNetworkingService) RegisterUser(user *User) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.users[user.ID] = user
}

func (s *SocialNetworkingService) LoginUser(email, password string) *User {
	s.mu.Lock()
	defer s.mu.Unlock()
	for _, user := range s.users {
		if user.Email == email && user.Password == password {
			return user
		}
	}
	return nil
}

func (s *SocialNetworkingService) SendFriendRequest(senderId, receiverId string) {
	s.mu.Lock()
	defer s.mu.Unlock()
	receiver := s.users[receiverId]
	if receiver != nil {
		notification := Notification{
			ID:        generateUUID(),
			UserID:    receiverId,
			Type:      FriendRequest,
			Content:   fmt.Sprintf("Friend request from %s", senderId),
			Timestamp: time.Now(),
		}
		s.addNotification(receiverId, notification)
	}
}

func (s *SocialNetworkingService) AcceptFriendRequest(userId, friendId string) {
	s.mu.Lock()
	defer s.mu.Unlock()
	user := s.users[userId]
	friend := s.users[friendId]
	if user != nil && friend != nil {
		user.Friends = append(user.Friends, friendId)
		friend.Friends = append(friend.Friends, userId)
		notification := Notification{
			ID:        generateUUID(),
			UserID:    friendId,
			Type:      FriendRequestAccepted,
			Content:   fmt.Sprintf("Friend request accepted by %s", userId),
			Timestamp: time.Now(),
		}
		s.addNotification(friendId, notification)
	}
}

func (s *SocialNetworkingService) CreatePost(post *Post) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.posts[post.ID] = post
	user := s.users[post.UserID]
	if user != nil {
		user.Posts = append(user.Posts, post)
	}
}

func (s *SocialNetworkingService) GetNewsfeed(userId string) []*Post {
	s.mu.Lock()
	defer s.mu.Unlock()
	var newsfeed []*Post
	user := s.users[userId]
	if user != nil {
		for _, friendId := range user.Friends {
			friend := s.users[friendId]
			if friend != nil {
				newsfeed = append(newsfeed, friend.Posts...)
			}
		}
		newsfeed = append(newsfeed, user.Posts...)
	}
	return newsfeed
}

func (s *SocialNetworkingService) LikePost(userId, postId string) {
	s.mu.Lock()
	defer s.mu.Unlock()
	post := s.posts[postId]
	if post != nil {
		post.Likes = append(post.Likes, userId)
		notification := Notification{
			ID:        generateUUID(),
			UserID:    post.UserID,
			Type:      Like,
			Content:   fmt.Sprintf("Your post was liked by %s", userId),
			Timestamp: time.Now(),
		}
		s.addNotification(post.UserID, notification)
	}
}

func (s *SocialNetworkingService) CommentOnPost(comment *Comment) {
	s.mu.Lock()
	defer s.mu.Unlock()
	post := s.posts[comment.PostID]
	if post != nil {
		post.Comments = append(post.Comments, *comment)
		notification := Notification{
			ID:        generateUUID(),
			UserID:    post.UserID,
			Type:      Comment,
			Content:   fmt.Sprintf("Your post received a comment from %s", comment.UserID),
			Timestamp: time.Now(),
		}
		s.addNotification(post.UserID, notification)
	}
}

func (s *SocialNetworkingService) GetNotifications(userId string) []Notification {
	s.mu.Lock()
	defer s.mu.Unlock()
	return s.notifications[userId]
}

func (s *SocialNetworkingService) addNotification(userId string, notification Notification) {
	s.notifications[userId] = append(s.notifications[userId], notification)
}

func generateUUID() string {
	return fmt.Sprintf("%d", time.Now().UnixNano()) // Placeholder for a UUID generator
}
