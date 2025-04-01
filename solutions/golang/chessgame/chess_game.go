package chessgame

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

type ChessGame struct {
	board         *Board
	players       []*Player
	currentPlayer int
}

func NewChessGame() *ChessGame {
	return &ChessGame{
		board:         NewBoard(),
		players:       []*Player{NewPlayer(White), NewPlayer(Black)},
		currentPlayer: 0,
	}
}

func (g *ChessGame) Start() {
	reader := bufio.NewReader(os.Stdin)

	for !g.isGameOver() {
		player := g.players[g.currentPlayer]
		fmt.Printf("%s's turn.\n", player.color)

		move, err := g.getPlayerMove(player, reader)
		if err != nil {
			fmt.Printf("Error: %v\nTry again!\n", err)
			continue
		}

		err = player.MakeMove(g.board, move)
		if err != nil {
			fmt.Printf("Error: %v\nTry again!\n", err)
			continue
		}

		g.currentPlayer = (g.currentPlayer + 1) % 2
	}

	g.displayResult()
}

func (g *ChessGame) isGameOver() bool {
	return g.board.IsCheckmate(White) || g.board.IsCheckmate(Black) ||
		g.board.IsStalemate(White) || g.board.IsStalemate(Black)
}

func (g *ChessGame) getPlayerMove(player *Player, reader *bufio.Reader) (*Move, error) {
	fmt.Print("Enter source row: ")
	sourceRow, _ := strconv.Atoi(readLine(reader))
	fmt.Print("Enter source column: ")
	sourceCol, _ := strconv.Atoi(readLine(reader))
	fmt.Print("Enter destination row: ")
	destRow, _ := strconv.Atoi(readLine(reader))
	fmt.Print("Enter destination column: ")
	destCol, _ := strconv.Atoi(readLine(reader))

	piece := g.board.GetPiece(sourceRow, sourceCol)
	if piece == nil || piece.GetColor() != player.color {
		return nil, fmt.Errorf("invalid piece selection")
	}

	return NewMove(piece, destRow, destCol), nil
}

func (g *ChessGame) displayResult() {
	if g.board.IsCheckmate(White) {
		fmt.Println("Black wins by checkmate!")
	} else if g.board.IsCheckmate(Black) {
		fmt.Println("White wins by checkmate!")
	} else if g.board.IsStalemate(White) || g.board.IsStalemate(Black) {
		fmt.Println("The game ends in a stalemate!")
	}
}

func readLine(reader *bufio.Reader) string {
	text, _ := reader.ReadString('\n')
	return text[:len(text)-1]
}
