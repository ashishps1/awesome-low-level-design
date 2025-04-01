package tictactoe

func Run() {
	player1 := NewPlayer("Player 1", 'X')
	player2 := NewPlayer("Player 2", 'O')

	game := NewGame(player1, player2)
	game.Play()
}
