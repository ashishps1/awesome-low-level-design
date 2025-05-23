package prototype

import "fmt"

// Enemy represents a game enemy
type Enemy struct {
	Type    string
	Health  int
	Speed   float64
	Armored bool
	Weapon  string
}

// NewEnemy creates a new Enemy instance
func NewEnemy(type_ string, health int, speed float64, armored bool, weapon string) *Enemy {
	return &Enemy{
		Type:    type_,
		Health:  health,
		Speed:   speed,
		Armored: armored,
		Weapon:  weapon,
	}
}

// Clone creates a copy of the enemy
func (e *Enemy) Clone() EnemyPrototype {
	return NewEnemy(e.Type, e.Health, e.Speed, e.Armored, e.Weapon)
}

// SetHealth updates the enemy's health
func (e *Enemy) SetHealth(health int) {
	e.Health = health
}

// PrintStats displays the enemy's statistics
func (e *Enemy) PrintStats() {
	fmt.Printf("%s [Health: %d, Speed: %.1f, Armored: %v, Weapon: %s]\n",
		e.Type, e.Health, e.Speed, e.Armored, e.Weapon)
} 