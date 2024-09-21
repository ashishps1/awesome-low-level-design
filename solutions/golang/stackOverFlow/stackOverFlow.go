package main

type StackOverFlow struct {
	questions map[string][]*Question
	tags      map[string]struct{}
}

func NewStackOverFlow() *StackOverFlow {
	return &StackOverFlow{
		questions: make(map[string][]*Question),
		tags:      make(map[string]struct{}),
	}
}

func (s *StackOverFlow) PostQuestion(user *User, title string, body string, tags []string) *Question {
	ques := NewQuestion(title, body, user)
	tagsToAdd := make(map[string]struct{})

	for _, tag := range tags {
		if _, isPresent := s.tags[tag]; !isPresent {
			tagsToAdd[tag] = struct{}{}
			s.tags[tag] = struct{}{}
		}
	}
	ques.tags = tagsToAdd
	s.questions[user.Email] = append(s.questions[user.Email], ques)
	return ques
}

func (s *StackOverFlow) GetQuestionsByTags(tags []string) []*Question {
	result := []*Question{}

	for _, questions := range s.questions {
		for _, question := range questions {
			for _, tag := range tags {
				if question.IsTagPresent(tag) {
					result = append(result, question)
				}
			}
		}
	}
	return result
}
