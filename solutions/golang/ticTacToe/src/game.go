package src

import "fmt"

type Game struct {
	board         *Board
	player1       Player
	player2       Player
	currentPlayer Player
}

func NewGame(p1, p2 Player) *Game {
	if p1.Symbol == p2.Symbol {
		fmt.Println("Both players cant have same symbol")
		return nil
	}
	return &Game{
		board:         NewBoard(),
		player1:       p1,
		player2:       p2,
		currentPlayer: p1,
	}
}

func (g *Game) Play() {
	fmt.Printf("%s: %s\n%s: %s\n", g.player1.Name, g.player1.Symbol, g.player2.Name, g.player2.Symbol)
	g.board.Print()

	for _, isFinished := g.board.ValidateState(); !isFinished; _, isFinished = g.board.ValidateState() {
		var row, col int
		fmt.Printf("%s's turn\n", g.currentPlayer.Name)
		fmt.Print("Enter row: ")
		fmt.Scanln(&row)
		fmt.Print("Enter col: ")
		fmt.Scanln(&col)

		g.board.MakeMove(row, col, g.currentPlayer.Symbol)
		g.board.Print()
		g.switchPlayer()
	}

	result, _ := g.board.ValidateState()
	fmt.Println(result)
}

func (g *Game) switchPlayer() {
	if g.currentPlayer == g.player1 {
		g.currentPlayer = g.player2
	} else {
		g.currentPlayer = g.player1
	}
}
