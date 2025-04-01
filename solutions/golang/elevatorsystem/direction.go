package elevatorsystem

type Direction int

const (
	DirectionUp Direction = iota
	DirectionDown
)

func (d Direction) String() string {
	return [...]string{"UP", "DOWN"}[d]
}
