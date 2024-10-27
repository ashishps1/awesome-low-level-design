package musicstreamingservice

import (
	"sync"
)

type UserManager struct {
	users map[string]*User
	mu    sync.RWMutex
}

var (
	userManagerInstance *UserManager
	userManagerOnce     sync.Once
)

func GetUserManager() *UserManager {
	userManagerOnce.Do(func() {
		userManagerInstance = &UserManager{
			users: make(map[string]*User),
		}
	})
	return userManagerInstance
}

func (um *UserManager) RegisterUser(user *User) {
	um.mu.Lock()
	defer um.mu.Unlock()
	um.users[user.ID] = user
}

func (um *UserManager) LoginUser(username, password string) *User {
	um.mu.RLock()
	defer um.mu.RUnlock()

	for _, user := range um.users {
		if user.Username == username && user.Password == password {
			return user
		}
	}
	return nil
}
