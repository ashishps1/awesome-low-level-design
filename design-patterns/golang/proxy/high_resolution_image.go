package proxy

import (
	"fmt"
	"time"
)

// HighResolutionImage represents a high-resolution image
type HighResolutionImage struct {
	fileName  string
	imageData []byte // Simulate large data
}

// NewHighResolutionImage creates a new HighResolutionImage
func NewHighResolutionImage(fileName string) *HighResolutionImage {
	image := &HighResolutionImage{fileName: fileName}
	image.loadImageFromDisk() // Expensive operation!
	return image
}

func (i *HighResolutionImage) loadImageFromDisk() {
	fmt.Printf("Loading image: %s from disk (Expensive Operation)...\n", i.fileName)
	// Simulate disk read and memory allocation
	time.Sleep(2 * time.Second)              // Simulate delay
	i.imageData = make([]byte, 10*1024*1024) // 10MB
	fmt.Printf("Image %s loaded successfully.\n", i.fileName)
}

func (i *HighResolutionImage) Display() {
	fmt.Printf("Displaying image: %s\n", i.fileName)
	// Actual rendering logic would go here
}

func (i *HighResolutionImage) GetFileName() string {
	return i.fileName
}
