package stackoverflow

type Votable interface {
	Vote(user *User, value int)
	GetVoteCount() int
}
