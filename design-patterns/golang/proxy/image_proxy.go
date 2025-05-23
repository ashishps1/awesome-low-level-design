package proxy

import "fmt"

// ImageProxy represents a proxy for high-resolution images
type ImageProxy struct {
	fileName  string
	realImage *HighResolutionImage // RealSubject
}

// NewImageProxy creates a new ImageProxy
func NewImageProxy(fileName string) *ImageProxy {
	fmt.Printf("ImageProxy: Created for %s. Real image not loaded yet.\n", fileName)
	return &ImageProxy{fileName: fileName}
}

func (p *ImageProxy) GetFileName() string {
	// Can safely return without loading the image
	return p.fileName
}

func (p *ImageProxy) Display() {
	// Lazy initialization: Load only when Display() is called
	if p.realImage == nil {
		fmt.Printf("ImageProxy: Display() requested for %s. Loading high-resolution image...\n", p.fileName)
		p.realImage = NewHighResolutionImage(p.fileName)
	} else {
		fmt.Printf("ImageProxy: Using cached high-resolution image for %s\n", p.fileName)
	}

	// Delegate the display call to the real image
	p.realImage.Display()
}
