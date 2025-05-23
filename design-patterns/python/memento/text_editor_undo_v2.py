from .text_editor import TextEditor
from .text_editor_undo_manager import TextEditorUndoManager

def main():
    # Create editor and undo manager
    editor = TextEditor()
    undo_manager = TextEditorUndoManager()

    # Type a sentence
    editor.type("The quick brown fox")
    undo_manager.save(editor)

    # Type more text
    editor.type(" jumps over the lazy dog")
    undo_manager.save(editor)

    # Show current content
    print(f"\nCurrent content: {editor.get_content()}")

    # Undo to remove " jumps over the lazy dog"
    print("\nUndoing...")
    undo_manager.undo(editor)
    print(f"Content after undo: {editor.get_content()}")

    # Type different text
    editor.type(" is quick")
    undo_manager.save(editor)

    # Show final content
    print(f"\nFinal content: {editor.get_content()}")

    # Try to undo multiple times
    print("\nUndoing multiple times...")
    for _ in range(3):
        undo_manager.undo(editor)
        print(f"Content: {editor.get_content()}")

if __name__ == "__main__":
    main() 