package snakeandladdergame

type Ladder struct {
	Start int
	End   int
}

func NewLadder(start, end int) *Ladder {
	return &Ladder{Start: start, End: end}
}
