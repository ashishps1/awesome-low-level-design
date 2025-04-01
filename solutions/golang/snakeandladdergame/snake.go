package snakeandladdergame

type Snake struct {
	Start int
	End   int
}

func NewSnake(start, end int) *Snake {
	return &Snake{Start: start, End: end}
}
