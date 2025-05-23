package prototype

// EnemyPrototype defines the interface for cloneable enemies
type EnemyPrototype interface {
	Clone() EnemyPrototype
}
