package flyweight

import "fmt"

// CharacterGlyph represents a character with its intrinsic properties
type CharacterGlyph struct {
	symbol     rune
	fontFamily string
	fontSize   int
	color      string
}

// NewCharacterGlyph creates a new CharacterGlyph instance
func NewCharacterGlyph(symbol rune, fontFamily string, fontSize int, color string) *CharacterGlyph {
	return &CharacterGlyph{
		symbol:     symbol,
		fontFamily: fontFamily,
		fontSize:   fontSize,
		color:      color,
	}
}

// Draw renders the character at the specified position
func (g *CharacterGlyph) Draw(x, y int) {
	fmt.Printf("Rendering %c at (%d, %d) with font %s, size %d, color %s\n",
		g.symbol, x, y, g.fontFamily, g.fontSize, g.color)
}
