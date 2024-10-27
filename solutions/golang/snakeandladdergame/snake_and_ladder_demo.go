package snakeandladdergame

import "fmt"

func Run() {
	gameManager := GetGameManager()

	// Start game 1
	players1 := []string{"Player 1", "Player 2", "Player 3"}
	gameManager.StartNewGame(players1)

	// Start game 2
	players2 := []string{"Player 4", "Player 5"}
	gameManager.StartNewGame(players2)

	fmt.Println("Games started. Check game output above.")
}
