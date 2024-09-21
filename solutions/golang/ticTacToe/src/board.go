package src

import "fmt"

type Board struct {
	Grid [][]Symbol
}

func NewBoard() *Board {
	grid := make([][]Symbol, 3)

	for i := 0; i < 3; i++ {
		grid[i] = make([]Symbol, 3)
		for j := 0; j < 3; j++ {
			grid[i][j] = I
		}
	}
	return &Board{Grid: grid}
}

func (b *Board) MakeMove(i, j int, symbol Symbol) {
	b.Grid[i][j] = symbol
}

func (b *Board) ValidateState() (string, bool) {
	//check rows
	for i := 0; i < 3; i++ {
		if b.Grid[i][0] != I && b.Grid[i][0] == b.Grid[i][1] && b.Grid[i][1] == b.Grid[i][2] {
			return fmt.Sprintf("%s has won", b.Grid[i][0].String()), true
		}
	}

	//check cols
	for i := 0; i < 3; i++ {
		if b.Grid[0][i] != I && b.Grid[0][i] == b.Grid[1][i] && b.Grid[1][i] == b.Grid[2][i] {
			return fmt.Sprintf("%s has won", b.Grid[0][i].String()), true
		}
	}

	//check diagonals
	if b.Grid[0][0] != I && b.Grid[0][0] == b.Grid[1][1] && b.Grid[1][1] == b.Grid[2][2] {
		return fmt.Sprintf("%s has won", b.Grid[0][0].String()), true
	}
	if b.Grid[0][2] != I && b.Grid[0][2] == b.Grid[1][1] && b.Grid[1][1] == b.Grid[2][0] {
		return fmt.Sprintf("%s has won", b.Grid[0][2].String()), true
	}

	// check if any moves more possible
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if b.Grid[i][j] == I {
				return fmt.Sprint("Game in progress"), false
			}
		}
	}

	return fmt.Sprint("Game is a draw"), true

}
func (b *Board) Print() {
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			fmt.Printf("%s ", b.Grid[i][j])
		}
		fmt.Println()
	}
}
