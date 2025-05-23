package iterator

// Iterator defines the interface for traversing a collection
type Iterator interface {
	HasNext() bool
	Next() interface{}
}
