package tictactoe

type Player struct {
	Name   string
	Symbol rune
}

func NewPlayer(name string, symbol rune) *Player {
	return &Player{Name: name, Symbol: symbol}
}
