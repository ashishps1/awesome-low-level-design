package bridge

// Rectangle represents a rectangle shape
type Rectangle struct {
	*BaseShape
	width  float64
	height float64
}

// NewRectangle creates a new Rectangle
func NewRectangle(renderer Renderer, width, height float64) *Rectangle {
	return &Rectangle{
		BaseShape: NewBaseShape(renderer),
		width:     width,
		height:    height,
	}
}

// Draw implements the Shape interface
func (r *Rectangle) Draw() {
	r.renderer.RenderRectangle(r.width, r.height)
}
