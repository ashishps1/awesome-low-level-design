package iterator

// Collection defines the interface for creating an iterator
type Collection interface {
	CreateIterator() Iterator
}
