package bridge

// Shape defines the interface for shapes
type Shape interface {
	Draw()
}

// BaseShape provides common functionality for shapes
type BaseShape struct {
	renderer Renderer
}

// NewBaseShape creates a new BaseShape
func NewBaseShape(renderer Renderer) *BaseShape {
	return &BaseShape{
		renderer: renderer,
	}
}
