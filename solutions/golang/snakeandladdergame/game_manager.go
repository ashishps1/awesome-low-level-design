package snakeandladdergame

import "sync"

type GameManager struct {
	Games []*SnakeAndLadderGame
}

var instance *GameManager

func GetGameManager() *GameManager {
	if instance == nil {
		instance = &GameManager{
			Games: []*SnakeAndLadderGame{},
		}
	}
	return instance
}

func (gm *GameManager) StartNewGame(wg *sync.WaitGroup, playerNames []string) {
	game := NewSnakeAndLadderGame(playerNames)
	gm.Games = append(gm.Games, game)
	wg.Add(1)
	go game.Play(wg)
}
