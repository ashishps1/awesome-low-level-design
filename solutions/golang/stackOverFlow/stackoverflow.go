package stackoverflow

import (
	"fmt"
	"strings"
	"sync"
)

type StackOverflow struct {
	users     map[string]*User
	questions map[string]*Question
	answers   map[string]*Answer
	tags      map[string]*Tag
	mu        sync.RWMutex
}

func NewStackOverflow() *StackOverflow {
	return &StackOverflow{
		users:     make(map[string]*User),
		questions: make(map[string]*Question),
		answers:   make(map[string]*Answer),
		tags:      make(map[string]*Tag),
	}
}

func (so *StackOverflow) CreateUser(username, email string) *User {
	so.mu.Lock()
	defer so.mu.Unlock()

	id := generateID()
	user := NewUser(id, username, email)
	so.users[id] = user
	return user
}

func (so *StackOverflow) AskQuestion(user *User, title, content string, tags []string) (*Question, error) {
	if user == nil {
		return nil, fmt.Errorf("user cannot be nil")
	}

	question := NewQuestion(user, title, content, tags)

	so.mu.Lock()
	defer so.mu.Unlock()

	so.questions[question.ID] = question
	user.AddQuestion(question)

	// Register tags
	for _, tag := range question.GetTags() {
		so.tags[tag.Name] = tag
	}

	return question, nil
}

func (so *StackOverflow) AnswerQuestion(user *User, question *Question, content string) (*Answer, error) {
	if user == nil || question == nil {
		return nil, fmt.Errorf("user and question cannot be nil")
	}

	answer := NewAnswer(user, question, content)

	so.mu.Lock()
	defer so.mu.Unlock()

	so.answers[answer.ID] = answer
	question.AddAnswer(answer)
	user.AddAnswer(answer)

	return answer, nil
}

func (so *StackOverflow) AddComment(user *User, target Commentable, content string) (*Comment, error) {
	if user == nil || target == nil {
		return nil, fmt.Errorf("user and target cannot be nil")
	}

	comment := NewComment(user, content)
	if err := target.AddComment(comment); err != nil {
		return nil, err
	}

	user.AddComment(comment)
	return comment, nil
}

func (so *StackOverflow) VoteQuestion(user *User, question *Question, value int) error {
	if user == nil || question == nil {
		return fmt.Errorf("user and question cannot be nil")
	}
	return question.Vote(user, value)
}

func (so *StackOverflow) VoteAnswer(user *User, answer *Answer, value int) error {
	if user == nil || answer == nil {
		return fmt.Errorf("user and answer cannot be nil")
	}
	return answer.Vote(user, value)
}

func (so *StackOverflow) AcceptAnswer(answer *Answer) error {
	if answer == nil {
		return fmt.Errorf("answer cannot be nil")
	}
	return answer.MarkAsAccepted()
}

func (so *StackOverflow) SearchQuestions(query string) []*Question {
	so.mu.RLock()
	defer so.mu.RUnlock()

	query = strings.ToLower(query)
	var results []*Question

	for _, q := range so.questions {
		if strings.Contains(strings.ToLower(q.Title), query) ||
			strings.Contains(strings.ToLower(q.Content), query) {
			results = append(results, q)
			continue
		}

		// Search in tags
		for _, tag := range q.GetTags() {
			if strings.EqualFold(tag.Name, query) {
				results = append(results, q)
				break
			}
		}
	}

	return results
}

func (so *StackOverflow) GetQuestionsByUser(user *User) []*Question {
	if user == nil {
		return nil
	}
	return user.GetQuestions()
}
