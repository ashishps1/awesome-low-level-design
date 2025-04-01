package movieticketbookingsystem

type Theater struct {
	ID       string
	Name     string
	Location string
	Shows    []*Show
}

func NewTheater(id, name, location string) *Theater {
	return &Theater{
		ID:       id,
		Name:     name,
		Location: location,
		Shows:    make([]*Show, 0),
	}
}
