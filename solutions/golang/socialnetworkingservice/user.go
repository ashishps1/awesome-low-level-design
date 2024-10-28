package socialnetworkingservice

import "sync"

type User struct {
	ID             string
	Name           string
	Email          string
	Password       string
	ProfilePicture string
	Bio            string
	friends        map[string]bool
	posts          []*Post
	mu             sync.RWMutex
}

func NewUser(id, name, email, password, profilePicture, bio string) *User {
	return &User{
		ID:             id,
		Name:           name,
		Email:          email,
		Password:       password,
		ProfilePicture: profilePicture,
		Bio:            bio,
		friends:        make(map[string]bool),
		posts:          make([]*Post, 0),
	}
}

func (u *User) AddFriend(friendID string) {
	u.mu.Lock()
	defer u.mu.Unlock()
	u.friends[friendID] = true
}

func (u *User) AddPost(post *Post) {
	u.mu.Lock()
	defer u.mu.Unlock()
	u.posts = append(u.posts, post)
}

func (u *User) GetFriends() []string {
	u.mu.RLock()
	defer u.mu.RUnlock()
	friends := make([]string, 0, len(u.friends))
	for friendID := range u.friends {
		friends = append(friends, friendID)
	}
	return friends
}

func (u *User) GetPosts() []*Post {
	u.mu.RLock()
	defer u.mu.RUnlock()
	posts := make([]*Post, len(u.posts))
	copy(posts, u.posts)
	return posts
}
