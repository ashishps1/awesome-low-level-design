package tictactoe

import "fmt"

type Board struct {
	Grid       [3][3]rune
	MovesCount int
}

func NewBoard() *Board {
	board := &Board{}
	board.InitializeBoard()
	return board
}

func (b *Board) InitializeBoard() {
	for row := 0; row < 3; row++ {
		for col := 0; col < 3; col++ {
			b.Grid[row][col] = '-'
		}
	}
	b.MovesCount = 0
}

func (b *Board) MakeMove(row, col int, symbol rune) error {
	if row < 0 || row >= 3 || col < 0 || col >= 3 || b.Grid[row][col] != '-' {
		return fmt.Errorf("invalid move!")
	}
	b.Grid[row][col] = symbol
	b.MovesCount++
	return nil
}

func (b *Board) IsFull() bool {
	return b.MovesCount == 9
}

func (b *Board) HasWinner() bool {
	// Check rows
	for row := 0; row < 3; row++ {
		if b.Grid[row][0] != '-' && b.Grid[row][0] == b.Grid[row][1] && b.Grid[row][1] == b.Grid[row][2] {
			return true
		}
	}

	// Check columns
	for col := 0; col < 3; col++ {
		if b.Grid[0][col] != '-' && b.Grid[0][col] == b.Grid[1][col] && b.Grid[1][col] == b.Grid[2][col] {
			return true
		}
	}

	// Check diagonals
	if b.Grid[0][0] != '-' && b.Grid[0][0] == b.Grid[1][1] && b.Grid[1][1] == b.Grid[2][2] {
		return true
	}
	return b.Grid[0][2] != '-' && b.Grid[0][2] == b.Grid[1][1] && b.Grid[1][1] == b.Grid[2][0]
}

func (b *Board) PrintBoard() {
	for row := 0; row < 3; row++ {
		for col := 0; col < 3; col++ {
			fmt.Print(string(b.Grid[row][col]) + " ")
		}
		fmt.Println()
	}
	fmt.Println()
}
