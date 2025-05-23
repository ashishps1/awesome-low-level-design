package composite

// FileSystemItem defines the interface for both files and folders
type FileSystemItem interface {
	GetName() string
	GetSize() int64
	Print(indent string)
	Delete()
}
