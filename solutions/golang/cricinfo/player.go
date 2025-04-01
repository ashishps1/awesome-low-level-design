package cricinfo

type Player struct {
	ID   string
	Name string
	Role string
}

func NewPlayer(id, name, role string) *Player {
	return &Player{
		ID:   id,
		Name: name,
		Role: role,
	}
}
