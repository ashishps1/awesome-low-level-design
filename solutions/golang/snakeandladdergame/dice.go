package snakeandladdergame

import "math/rand"

type Dice struct{}

func NewDice() *Dice {
	return &Dice{}
}

func (d *Dice) Roll() int {
	return rand.Intn(6) + 1
}
