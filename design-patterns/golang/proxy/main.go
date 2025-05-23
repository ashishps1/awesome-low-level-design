package proxy

import "fmt"

func main() {
	fmt.Println("Application Started. Initializing image proxies for gallery...")

	// Create lightweight proxies instead of full image objects
	image1 := NewImageProxy("photo1.jpg")
	image2 := NewImageProxy("photo2.png") // Never displayed
	image3 := NewImageProxy("photo3.gif")

	fmt.Println("\nGallery initialized. No images actually loaded yet.")
	fmt.Printf("Image 1 Filename: %s\n", image1.GetFileName()) // Does not trigger image load

	// User clicks on image1
	fmt.Printf("\nUser requests to display %s\n", image1.GetFileName())
	image1.Display() // Lazy loading happens here

	// User clicks on image1 again
	fmt.Printf("\nUser requests to display %s again.\n", image1.GetFileName())
	image1.Display() // Already loaded; no loading delay

	// User clicks on image3
	fmt.Printf("\nUser requests to display %s\n", image3.GetFileName())
	image3.Display() // Triggers loading for image3

	fmt.Println("\nApplication finished. Note: photo2.png was never loaded.")
}
