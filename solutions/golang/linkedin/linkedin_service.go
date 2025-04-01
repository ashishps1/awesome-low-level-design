package linkedin

import (
	"fmt"
	"strings"
	"sync"
	"time"
)

type LinkedInService struct {
	users         map[string]*User
	jobPostings   map[string]*JobPosting
	notifications map[string][]*Notification
	mu            sync.RWMutex
}

var (
	instance *LinkedInService
	once     sync.Once
)

func GetLinkedInService() *LinkedInService {
	once.Do(func() {
		instance = &LinkedInService{
			users:         make(map[string]*User),
			jobPostings:   make(map[string]*JobPosting),
			notifications: make(map[string][]*Notification),
		}
	})
	return instance
}

func (s *LinkedInService) RegisterUser(user *User) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.users[user.ID] = user
}

func (s *LinkedInService) LoginUser(email, password string) (*User, error) {
	s.mu.RLock()
	defer s.mu.RUnlock()

	for _, user := range s.users {
		if user.Email == email && user.Password == password {
			return user, nil
		}
	}
	return nil, fmt.Errorf("invalid email or password")
}

func (s *LinkedInService) UpdateUserProfile(user *User) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.users[user.ID] = user
}

func (s *LinkedInService) SendConnectionRequest(sender, receiver *User) {
	connection := NewConnection(sender)
	receiver.AddConnection(connection)

	notification := NewNotification(
		fmt.Sprintf("NOTIF-%d", time.Now().UnixNano()),
		receiver,
		NotificationTypeConnectionRequest,
		fmt.Sprintf("New connection request from %s", sender.Name),
	)
	s.addNotification(receiver.ID, notification)
}

func (s *LinkedInService) AcceptConnectionRequest(user, connectionUser *User) {
	user.AddConnection(NewConnection(connectionUser))
}

func (s *LinkedInService) SearchUsers(keyword string) []*User {
	s.mu.RLock()
	defer s.mu.RUnlock()

	var results []*User
	keyword = strings.ToLower(keyword)

	for _, user := range s.users {
		if strings.Contains(strings.ToLower(user.Name), keyword) {
			results = append(results, user)
		}
	}
	return results
}

func (s *LinkedInService) PostJobListing(jobPosting *JobPosting) {
	s.mu.Lock()
	s.jobPostings[jobPosting.ID] = jobPosting
	s.mu.Unlock()

	// Notify all users about new job posting
	for _, user := range s.users {
		notification := NewNotification(
			fmt.Sprintf("NOTIF-%d", time.Now().UnixNano()),
			user,
			NotificationTypeJobPosting,
			fmt.Sprintf("New job posting: %s", jobPosting.Title),
		)
		s.addNotification(user.ID, notification)
	}
}

func (s *LinkedInService) SearchJobPostings(keyword string) []*JobPosting {
	s.mu.RLock()
	defer s.mu.RUnlock()

	var results []*JobPosting
	keyword = strings.ToLower(keyword)

	for _, posting := range s.jobPostings {
		if strings.Contains(strings.ToLower(posting.Title), keyword) ||
			strings.Contains(strings.ToLower(posting.Description), keyword) {
			results = append(results, posting)
		}
	}
	return results
}

func (s *LinkedInService) SendMessage(sender, receiver *User, content string) {
	message := NewMessage(
		fmt.Sprintf("MSG-%d", time.Now().UnixNano()),
		sender,
		receiver,
		content,
	)

	receiver.AddMessage(message, false)
	sender.AddMessage(message, true)

	notification := NewNotification(
		fmt.Sprintf("NOTIF-%d", time.Now().UnixNano()),
		receiver,
		NotificationTypeMessage,
		fmt.Sprintf("New message from %s", sender.Name),
	)
	s.addNotification(receiver.ID, notification)
}

func (s *LinkedInService) addNotification(userID string, notification *Notification) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.notifications[userID] = append(s.notifications[userID], notification)
}

func (s *LinkedInService) GetNotifications(userID string) []*Notification {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return s.notifications[userID]
}
