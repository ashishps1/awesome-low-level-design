package snakeandladdergame

type Player struct {
	Name     string
	Position int
}

func NewPlayer(name string) *Player {
	return &Player{Name: name, Position: 0}
}
