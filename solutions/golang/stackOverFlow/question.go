package main

import "fmt"

type Question struct {
	title    string
	body     string
	comments []Comment
	answers  []Answer
	votes    []Vote
	tags     map[string]struct{}
	author   *User
}

func NewQuestion(title, body string, author *User) *Question {
	return &Question{
		title:  title,
		body:   body,
		tags:   make(map[string]struct{}),
		author: author,
	}
}

func (q *Question) AddAnswerToList(ans Answer) {
	q.answers = append(q.answers, ans)
}

func (q *Question) PostAnswer(user *User, title, body string) *Answer {
	ans := NewAnswer(title, body, user)

	user.AddAnswerToList(*ans)

	q.AddAnswerToList(*ans)

	return ans
}

func (q *Question) PostComment(user *User, body string) {
	comment := NewComment(body)
	q.comments = append(q.comments, *comment)
	user.AddCommentToList(*comment)
}

func (q *Question) AddVote(user *User, value int) {
	if value != 1 && value != -1 {
		fmt.Printf("%d value not allowed for vote\n", value)
	}

	vote := NewVote(value)
	q.author.ManageRating(vote)

	q.votes = append(q.votes, vote)
	user.AddVoteToList(vote)
}

func (q *Question) IsTagPresent(tag string) bool {
	_, isPresent := q.tags[tag]
	return isPresent
}
