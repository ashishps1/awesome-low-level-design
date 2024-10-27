package stackoverflow

type StackOverflow struct {
	Users     map[int]*User
	Questions map[int]*Question
	Answers   map[int]*Answer
	Tags      map[string]*Tag
}

func NewStackOverflow() *StackOverflow {
	return &StackOverflow{
		Users:     make(map[int]*User),
		Questions: make(map[int]*Question),
		Answers:   make(map[int]*Answer),
		Tags:      make(map[string]*Tag),
	}
}

func (s *StackOverflow) CreateUser(username, email string) *User {
	id := len(s.Users) + 1
	user := NewUser(id, username, email)
	s.Users[id] = user
	return user
}

func (s *StackOverflow) AskQuestion(user *User, title, content string, tags []string) *Question {
	question := NewQuestion(user, title, content, tags)
	s.Questions[question.ID] = question
	return question
}

func (s *StackOverflow) AnswerQuestion(user *User, question *Question, content string) *Answer {
	answer := NewAnswer(user, question, content)
	s.Answers[answer.ID] = answer
	question.AddAnswer(answer)
	return answer
}

func (s *StackOverflow) AddComment(user *User, commentable Commentable, content string) *Comment {
	comment := NewComment(user, content)
	commentable.AddComment(comment)
	return comment
}

func (s *StackOverflow) VoteQuestion(user *User, question *Question, value int) {
	question.Vote(user, value)
}

func (s *StackOverflow) VoteAnswer(user *User, answer *Answer, value int) {
	answer.Vote(user, value)
}

func (s *StackOverflow) AcceptAnswer(answer *Answer) {
	answer.MarkAsAccepted()
}

func (s *StackOverflow) SearchQuestions(query string) []*Question {
	var results []*Question
	for _, question := range s.Questions {
		if contains(question.Title, query) || contains(question.Content, query) {
			results = append(results, question)
		}
	}
	return results
}

func (s *StackOverflow) GetQuestionsByUser(user *User) []*Question {
	var userQuestions []*Question
	for _, question := range s.Questions {
		if question.Author == user {
			userQuestions = append(userQuestions, question)
		}
	}
	return userQuestions
}

func contains(s, substr string) bool {
	return len(s) >= len(substr) && s[:len(substr)] == substr
}
