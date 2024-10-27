package snakeandladdergame

import "fmt"

type SnakeAndLadderGame struct {
	Board            *Board
	Players          []*Player
	Dice             *Dice
	CurrentPlayerIdx int
}

func NewSnakeAndLadderGame(playerNames []string) *SnakeAndLadderGame {
	game := &SnakeAndLadderGame{
		Board:            NewBoard(),
		Dice:             NewDice(),
		Players:          []*Player{},
		CurrentPlayerIdx: 0,
	}

	for _, name := range playerNames {
		game.Players = append(game.Players, NewPlayer(name))
	}
	return game
}

func (g *SnakeAndLadderGame) Play() {
	for !g.isGameOver() {
		player := g.Players[g.CurrentPlayerIdx]
		roll := g.Dice.Roll()
		newPosition := player.Position + roll

		if newPosition <= g.Board.Size {
			player.Position = g.Board.GetNewPosition(newPosition)
			fmt.Printf("%s rolled a %d and moved to position %d\n", player.Name, roll, player.Position)
		}

		if player.Position == g.Board.Size {
			fmt.Printf("%s wins!\n", player.Name)
			break
		}

		g.CurrentPlayerIdx = (g.CurrentPlayerIdx + 1) % len(g.Players)
	}
}

func (g *SnakeAndLadderGame) isGameOver() bool {
	for _, player := range g.Players {
		if player.Position == g.Board.Size {
			return true
		}
	}
	return false
}
