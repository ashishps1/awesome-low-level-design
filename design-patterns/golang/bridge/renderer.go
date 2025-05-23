package bridge

// Renderer defines the interface for rendering shapes
type Renderer interface {
	RenderCircle(radius float64)
	RenderRectangle(width, height float64)
}
