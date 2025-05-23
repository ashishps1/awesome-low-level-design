package flyweight

import "fmt"

func main() {
	// Create a text editor client
	editor := NewTextEditorClient()

	// Render some text with the same properties
	fmt.Println("Rendering text with same properties:")
	editor.RenderText("Hello", 0, 0, "Arial", 12, "black")
	fmt.Printf("Number of unique characters: %d\n\n", editor.GetUniqueCharacterCount())

	// Render the same text with different properties
	fmt.Println("Rendering text with different properties:")
	editor.RenderText("Hello", 0, 20, "Times New Roman", 14, "blue")
	fmt.Printf("Number of unique characters: %d\n\n", editor.GetUniqueCharacterCount())

	// Render text with mixed properties
	fmt.Println("Rendering text with mixed properties:")
	editor.RenderText("World", 0, 40, "Arial", 12, "red")
	fmt.Printf("Number of unique characters: %d\n", editor.GetUniqueCharacterCount())
}
