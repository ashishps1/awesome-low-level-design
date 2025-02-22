package snakeandladdergame

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
)

type SnakeAndLadderGame struct {
	ID               int64
	Board            *Board
	Players          []*Player
	Dice             *Dice
	CurrentPlayerIdx int
}

func NewSnakeAndLadderGame(playerNames []string) *SnakeAndLadderGame {
	game := &SnakeAndLadderGame{
		ID:               generateID(),
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

func (g *SnakeAndLadderGame) Play(wg *sync.WaitGroup) {
	for !g.isGameOver() {
		player := g.Players[g.CurrentPlayerIdx]
		roll := g.Dice.Roll()
		newPosition := player.Position + roll

		if newPosition <= g.Board.Size {
			player.Position = g.Board.GetNewPosition(newPosition)
			fmt.Printf("Game: %d :- %s rolled a %d and moved to position %d\n", g.ID, player.Name, roll, player.Position)
		}

		if player.Position == g.Board.Size {
			fmt.Printf("For Game %d :- %s wins!\n", g.ID, player.Name)
			break
		}

		g.CurrentPlayerIdx = (g.CurrentPlayerIdx + 1) % len(g.Players)
		time.Sleep(10 * time.Millisecond) //To simulate the demo
	}
	wg.Done()
}

func (g *SnakeAndLadderGame) isGameOver() bool {
	for _, player := range g.Players {
		if player.Position == g.Board.Size {
			return true
		}
	}
	return false
}

var idCounter int64

func generateID() int64 {
	return atomic.AddInt64(&idCounter, 1)
}
