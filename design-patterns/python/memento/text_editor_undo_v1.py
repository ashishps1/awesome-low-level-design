from .text_editor import TextEditor
from .text_editor_undo_manager import TextEditorUndoManager

def main():
    # Create editor and undo manager
    editor = TextEditor()
    undo_manager = TextEditorUndoManager()

    # Type some text
    editor.type("Hello")
    undo_manager.save(editor)

    editor.type(" World")
    undo_manager.save(editor)

    editor.type("!")
    undo_manager.save(editor)

    # Show current content
    print(f"\nCurrent content: {editor.get_content()}")

    # Undo operations
    print("\nUndoing...")
    undo_manager.undo(editor)
    print(f"Content after undo: {editor.get_content()}")

    undo_manager.undo(editor)
    print(f"Content after second undo: {editor.get_content()}")

    undo_manager.undo(editor)
    print(f"Content after third undo: {editor.get_content()}")

    # Try to undo when nothing is left
    undo_manager.undo(editor)

if __name__ == "__main__":
    main() 