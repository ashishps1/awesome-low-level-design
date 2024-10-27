package stackoverflow

import "time"

type Question struct {
	ID           int
	Title        string
	Content      string
	Author       *User
	CreationDate time.Time
	Answers      []*Answer
	Comments     []*Comment
	Tags         []*Tag
	Votes        []*Vote
}

func NewQuestion(author *User, title, content string, tagNames []string) *Question {
	tags := make([]*Tag, len(tagNames))
	for i, tagName := range tagNames {
		tags[i] = NewTag(tagName)
	}
	return &Question{
		ID:           generateID(),
		Author:       author,
		Title:        title,
		Content:      content,
		CreationDate: time.Now(),
		Tags:         tags,
	}
}

func (q *Question) AddComment(comment *Comment) {
	q.Comments = append(q.Comments, comment)
}

func (q *Question) GetComments() []*Comment {
	return q.Comments
}

func (q *Question) Vote(user *User, value int) {
	q.Votes = append(q.Votes, NewVote(user, value))
	q.Author.UpdateReputation(value * 5)
}

func (q *Question) GetVoteCount() int {
	voteCount := 0
	for _, vote := range q.Votes {
		voteCount += vote.Value
	}
	return voteCount
}

func (q *Question) AddAnswer(answer *Answer) {
	q.Answers = append(q.Answers, answer)
}
