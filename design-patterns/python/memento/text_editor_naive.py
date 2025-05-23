from .text_editor import TextEditor

def main():
    # Create editor
    editor = TextEditor()

    # Type some text
    editor.type("Hello")
    editor.type(" World")
    editor.type("!")

    # Show content
    print(f"\nContent: {editor.get_content()}")

    # No undo functionality available
    print("\nNo undo functionality available in this version")

if __name__ == "__main__":
    main() 