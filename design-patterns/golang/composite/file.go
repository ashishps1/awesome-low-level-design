package composite

import "fmt"

// File represents a file in the file system
type File struct {
	name string
	size int64
}

// NewFile creates a new File instance
func NewFile(name string, size int64) *File {
	return &File{
		name: name,
		size: size,
	}
}

// GetName returns the name of the file
func (f *File) GetName() string {
	return f.name
}

// GetSize returns the size of the file
func (f *File) GetSize() int64 {
	return f.size
}

// Print prints the file information with the given indentation
func (f *File) Print(indent string) {
	fmt.Printf("%sFile: %s (%d bytes)\n", indent, f.name, f.size)
}

// Delete deletes the file
func (f *File) Delete() {
	fmt.Printf("Deleting file: %s\n", f.name)
}
