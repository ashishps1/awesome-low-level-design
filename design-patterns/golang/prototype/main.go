package prototype

func main() {
	registry := NewEnemyRegistry()

	// Register prototype enemies
	registry.Register("flying", NewEnemy("FlyingEnemy", 100, 12.0, false, "Laser"))
	registry.Register("armored", NewEnemy("ArmoredEnemy", 300, 6.0, true, "Cannon"))

	// Clone from registry
	e1 := registry.Get("flying")
	e2 := registry.Get("flying")
	e2.SetHealth(80) // this one is damaged

	e3 := registry.Get("armored")

	// Print enemy stats
	e1.PrintStats()
	e2.PrintStats()
	e3.PrintStats()
}
