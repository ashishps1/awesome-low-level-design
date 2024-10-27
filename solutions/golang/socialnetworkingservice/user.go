package socialnetworkingservice

type User struct {
	ID             string
	Name           string
	Email          string
	Password       string
	ProfilePicture string
	Bio            string
	Friends        []string
	Posts          []*Post
}

func NewUser(id, name, email, password, profilePicture, bio string) *User {
	return &User{
		ID:             id,
		Name:           name,
		Email:          email,
		Password:       password,
		ProfilePicture: profilePicture,
		Bio:            bio,
		Friends:        []string{},
		Posts:          []*Post{},
	}
}
