package prototype

// EnemyRegistry manages enemy prototypes
type EnemyRegistry struct {
	prototypes map[string]*Enemy
}

// NewEnemyRegistry creates a new EnemyRegistry
func NewEnemyRegistry() *EnemyRegistry {
	return &EnemyRegistry{
		prototypes: make(map[string]*Enemy),
	}
}

// Register adds a prototype to the registry
func (r *EnemyRegistry) Register(key string, prototype *Enemy) {
	r.prototypes[key] = prototype
}

// Get retrieves and clones a prototype from the registry
func (r *EnemyRegistry) Get(key string) *Enemy {
	if prototype, exists := r.prototypes[key]; exists {
		return prototype.Clone().(*Enemy)
	}
	panic("No prototype registered for: " + key)
}
