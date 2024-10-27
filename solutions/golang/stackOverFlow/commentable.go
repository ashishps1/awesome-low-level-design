package stackoverflow

type Commentable interface {
	AddComment(comment *Comment)
	GetComments() []*Comment
}
