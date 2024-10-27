package stackoverflow

type Vote struct {
	User  *User
	Value int
}

func NewVote(user *User, value int) *Vote {
	return &Vote{User: user, Value: value}
}
