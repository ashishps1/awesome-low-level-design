package composite

import "fmt"

func main() {
	// Create root folder
	root := NewFolder("Root")

	// Create subfolders
	documents := NewFolder("Documents")
	downloads := NewFolder("Downloads")
	pictures := NewFolder("Pictures")

	// Create files
	report := NewFile("report.txt", 1024)
	image := NewFile("image.jpg", 2048)
	video := NewFile("video.mp4", 4096)

	// Build the structure
	root.Add(documents)
	root.Add(downloads)
	root.Add(pictures)

	documents.Add(report)
	downloads.Add(video)
	pictures.Add(image)

	// Print the structure
	fmt.Println("File System Structure:")
	root.Print("")

	// Print total size
	fmt.Printf("\nTotal size: %d bytes\n", root.GetSize())

	// Delete a folder
	fmt.Println("\nDeleting Documents folder:")
	root.Remove(documents)
	documents.Delete()

	// Print the structure again
	fmt.Println("\nUpdated File System Structure:")
	root.Print("")
}
