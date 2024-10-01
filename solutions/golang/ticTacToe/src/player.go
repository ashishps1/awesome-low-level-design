package src

type Player struct {
	Name   string
	Symbol Symbol
}

func NewPlayer(name string, symbol Symbol) Player {
	return Player{
		Name:   name,
		Symbol: symbol,
	}
}
