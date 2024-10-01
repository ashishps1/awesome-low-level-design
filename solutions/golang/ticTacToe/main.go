package main

import "github.com/ashishps1/awesome-low-level-design/ticTacToe/src"

func main() {
	p1 := src.NewPlayer("alice", src.X)
	p2 := src.NewPlayer("bob", src.O)
	game := src.NewGame(p1, p2)
	game.Play()
}
