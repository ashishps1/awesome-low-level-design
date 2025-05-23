from .text_editor_client import TextEditorClient

def main():
    # Create a text editor client
    editor = TextEditorClient()

    # Add some text with different styles
    # First line: "Hello" in Arial, size 12, black
    editor.add_character("H", "Arial", 12, "black", 0, 0)
    editor.add_character("e", "Arial", 12, "black", 10, 0)
    editor.add_character("l", "Arial", 12, "black", 20, 0)
    editor.add_character("l", "Arial", 12, "black", 30, 0)
    editor.add_character("o", "Arial", 12, "black", 40, 0)

    # Second line: "World" in Times New Roman, size 14, blue
    editor.add_character("W", "Times New Roman", 14, "blue", 0, 20)
    editor.add_character("o", "Times New Roman", 14, "blue", 15, 20)
    editor.add_character("r", "Times New Roman", 14, "blue", 30, 20)
    editor.add_character("l", "Times New Roman", 14, "blue", 45, 20)
    editor.add_character("d", "Times New Roman", 14, "blue", 60, 20)

    # Render the text
    print("Rendering text:")
    editor.render()

    # Show flyweight count
    print(f"\nNumber of unique character flyweights: {editor.get_flyweight_count()}")

if __name__ == "__main__":
    main() 