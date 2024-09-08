package main

type User struct {
	Name     string
	Email    string
	Rating   int
	Answers  []Answer
	Comments []Comment
	Votes    []Vote
}

func NewUser(name, email string) *User {
	return &User{
		Name:  name,
		Email: email,
	}
}

func (u *User) AddAnswerToList(ans Answer) {
	u.Answers = append(u.Answers, ans)
}

func (u *User) AddCommentToList(comment Comment) {
	u.Comments = append(u.Comments, comment)
}

func (u *User) AddVoteToList(vote Vote) {
	u.Votes = append(u.Votes, vote)
}

func (u *User) ManageRating(vote Vote) {
	if vote.Value == 1 {
		u.Rating += 10
	} else {
		u.Rating -= 10
	}
}
