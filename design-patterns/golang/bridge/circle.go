package bridge

// Circle represents a circle shape
type Circle struct {
	*BaseShape
	radius float64
}

// NewCircle creates a new Circle
func NewCircle(renderer Renderer, radius float64) *Circle {
	return &Circle{
		BaseShape: NewBaseShape(renderer),
		radius:    radius,
	}
}

// Draw implements the Shape interface
func (c *Circle) Draw() {
	c.renderer.RenderCircle(c.radius)
}
