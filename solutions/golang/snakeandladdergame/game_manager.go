package snakeandladdergame

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

func (gm *GameManager) StartNewGame(playerNames []string) {
	game := NewSnakeAndLadderGame(playerNames)
	gm.Games = append(gm.Games, game)
	go game.Play()
}
