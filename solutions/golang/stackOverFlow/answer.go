package main

type Answer struct {
	Title    string
	Body     string
	Votes    []Vote
	Comments []Comment
	Author   *User
}

func NewAnswer(title, body string, user *User) *Answer {
	return &Answer{
		Title:  title,
		Body:   body,
		Author: user,
	}
}

func (a *Answer) addCommentToList(comment Comment) {
	a.Comments = append(a.Comments, comment)
}

func (a *Answer) addVoteToList(vote Vote) {
	a.Votes = append(a.Votes, vote)
}

func (a *Answer) PostComment(user *User, body string) {
	comment := NewComment(body)
	a.addCommentToList(*comment)
	user.AddCommentToList(*comment)
}

func (a *Answer) AddVote(user *User, value int) {
	vote := NewVote(value)
	user.AddVoteToList(vote)
	a.addVoteToList(vote)
	a.Author.ManageRating(vote)
}
