package main

type Comment struct {
	Body string
}

func NewComment(body string) *Comment {
	return &Comment{
		Body: body,
	}
}
