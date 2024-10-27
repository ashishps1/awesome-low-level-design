package stackoverflow

import "time"

type Answer struct {
	ID           int
	Content      string
	Author       *User
	Question     *Question
	IsAccepted   bool
	CreationDate time.Time
	Comments     []*Comment
	Votes        []*Vote
}

func NewAnswer(author *User, question *Question, content string) *Answer {
	return &Answer{
		ID:           generateID(),
		Author:       author,
		Question:     question,
		Content:      content,
		CreationDate: time.Now(),
	}
}

func (a *Answer) AddComment(comment *Comment) {
	a.Comments = append(a.Comments, comment)
}

func (a *Answer) GetComments() []*Comment {
	return a.Comments
}

func (a *Answer) Vote(user *User, value int) {
	a.Votes = append(a.Votes, NewVote(user, value))
	a.Author.UpdateReputation(value * 10)
}

func (a *Answer) GetVoteCount() int {
	voteCount := 0
	for _, vote := range a.Votes {
		voteCount += vote.Value
	}
	return voteCount
}

func (a *Answer) MarkAsAccepted() {
	if a.IsAccepted {
		panic("Answer is already accepted")
	}
	a.IsAccepted = true
	a.Author.UpdateReputation(15)
}
