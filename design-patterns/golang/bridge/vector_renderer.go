package bridge

import "fmt"

// VectorRenderer renders shapes as vector graphics
type VectorRenderer struct{}

// NewVectorRenderer creates a new VectorRenderer
func NewVectorRenderer() *VectorRenderer {
	return &VectorRenderer{}
}

// RenderCircle implements the Renderer interface
func (v *VectorRenderer) RenderCircle(radius float64) {
	fmt.Printf("Drawing a circle of radius %.2f using vector graphics\n", radius)
}

// RenderRectangle implements the Renderer interface
func (v *VectorRenderer) RenderRectangle(width, height float64) {
	fmt.Printf("Drawing a rectangle of width %.2f and height %.2f using vector graphics\n", width, height)
}
