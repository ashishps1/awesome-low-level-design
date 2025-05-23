package flyweight

import "fmt"

// CharacterFlyweightFactory manages the flyweight objects
type CharacterFlyweightFactory struct {
	flyweightCache map[string]CharacterFlyweight
}

// NewCharacterFlyweightFactory creates a new CharacterFlyweightFactory instance
func NewCharacterFlyweightFactory() *CharacterFlyweightFactory {
	return &CharacterFlyweightFactory{
		flyweightCache: make(map[string]CharacterFlyweight),
	}
}

// GetFlyweight returns a flyweight object for the given character properties
func (f *CharacterFlyweightFactory) GetFlyweight(symbol rune, fontFamily string, fontSize int, color string) CharacterFlyweight {
	key := fmt.Sprintf("%c-%d-%s", symbol, fontSize, color)
	if _, exists := f.flyweightCache[key]; !exists {
		f.flyweightCache[key] = NewCharacterGlyph(symbol, fontFamily, fontSize, color)
	}
	return f.flyweightCache[key]
}

// GetFlyweightCount returns the number of unique flyweight objects
func (f *CharacterFlyweightFactory) GetFlyweightCount() int {
	return len(f.flyweightCache)
}
