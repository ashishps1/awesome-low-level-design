package snakeandladdergame

type Board struct {
	Size    int
	Snakes  []*Snake
	Ladders []*Ladder
}

func NewBoard() *Board {
	board := &Board{
		Size:    100,
		Snakes:  []*Snake{},
		Ladders: []*Ladder{},
	}
	board.initializeSnakesAndLadders()
	return board
}

func (b *Board) initializeSnakesAndLadders() {
	b.Snakes = append(b.Snakes, NewSnake(16, 6), NewSnake(48, 26), NewSnake(64, 60), NewSnake(93, 73))
	b.Ladders = append(b.Ladders, NewLadder(1, 38), NewLadder(4, 14), NewLadder(9, 31), NewLadder(21, 42),
		NewLadder(28, 84), NewLadder(51, 67), NewLadder(80, 99))
}

func (b *Board) GetNewPosition(position int) int {
	for _, snake := range b.Snakes {
		if snake.Start == position {
			return snake.End
		}
	}
	for _, ladder := range b.Ladders {
		if ladder.Start == position {
			return ladder.End
		}
	}
	return position
}
