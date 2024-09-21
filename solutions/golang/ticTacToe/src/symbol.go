package src

type Symbol int

const (
	X Symbol = iota + 1
	O
	I
)

func (s Symbol) String() string {
	return [...]string{"X", "O", "-"}[s-1]
}
