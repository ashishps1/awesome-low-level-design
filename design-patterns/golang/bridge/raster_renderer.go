package bridge

import "fmt"

// RasterRenderer renders shapes as raster graphics
type RasterRenderer struct{}

// NewRasterRenderer creates a new RasterRenderer
func NewRasterRenderer() *RasterRenderer {
	return &RasterRenderer{}
}

// RenderCircle implements the Renderer interface
func (r *RasterRenderer) RenderCircle(radius float64) {
	fmt.Printf("Drawing a circle of radius %.2f using raster graphics\n", radius)
}

// RenderRectangle implements the Renderer interface
func (r *RasterRenderer) RenderRectangle(width, height float64) {
	fmt.Printf("Drawing a rectangle of width %.2f and height %.2f using raster graphics\n", width, height)
}
