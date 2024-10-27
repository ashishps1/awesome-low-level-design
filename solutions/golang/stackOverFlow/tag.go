package stackoverflow

type Tag struct {
	ID   int
	Name string
}

func NewTag(name string) *Tag {
	return &Tag{ID: generateID(), Name: name}
}
