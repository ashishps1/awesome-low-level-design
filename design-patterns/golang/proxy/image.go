package proxy

// Image defines the interface for image operations
type Image interface {
	Display()
	GetFileName() string
}
