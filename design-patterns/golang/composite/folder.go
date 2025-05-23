package composite

import "fmt"

// Folder represents a folder in the file system
type Folder struct {
	name     string
	children []FileSystemItem
}

// NewFolder creates a new Folder instance
func NewFolder(name string) *Folder {
	return &Folder{
		name:     name,
		children: make([]FileSystemItem, 0),
	}
}

// GetName returns the name of the folder
func (f *Folder) GetName() string {
	return f.name
}

// GetSize returns the total size of the folder and its contents
func (f *Folder) GetSize() int64 {
	var totalSize int64
	for _, item := range f.children {
		totalSize += item.GetSize()
	}
	return totalSize
}

// Add adds a new item to the folder
func (f *Folder) Add(item FileSystemItem) {
	f.children = append(f.children, item)
}

// Remove removes an item from the folder
func (f *Folder) Remove(item FileSystemItem) {
	for i, child := range f.children {
		if child.GetName() == item.GetName() {
			f.children = append(f.children[:i], f.children[i+1:]...)
			break
		}
	}
}

// Print prints the folder structure with the given indentation
func (f *Folder) Print(indent string) {
	fmt.Printf("%sFolder: %s\n", indent, f.name)
	for _, item := range f.children {
		item.Print(indent + "  ")
	}
}

// Delete deletes the folder and its contents
func (f *Folder) Delete() {
	fmt.Printf("Deleting folder: %s\n", f.name)
	for _, item := range f.children {
		item.Delete()
	}
}
