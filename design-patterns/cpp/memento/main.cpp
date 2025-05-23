#include "text_editor.h"
#include "text_editor_undo_manager.h"
#include <iostream>

int main() {
    TextEditor editor;
    TextEditorUndoManager undoManager;

    std::cout << "=== Text Editor with Undo Demo ===\n" << std::endl;

    // Type some text and save state
    std::cout << "Typing and saving initial text:" << std::endl;
    editor.type("Hello, ");
    undoManager.save(editor);

    // Type more text and save state
    std::cout << "\nTyping and saving more text:" << std::endl;
    editor.type("World!");
    undoManager.save(editor);

    // Type additional text
    std::cout << "\nTyping additional text:" << std::endl;
    editor.type(" How are you?");

    // Show current content
    std::cout << "\nCurrent content: " << editor.getContent() << std::endl;

    // Undo last change
    std::cout << "\nUndoing last change:" << std::endl;
    undoManager.undo(editor);

    // Show content after undo
    std::cout << "\nContent after undo: " << editor.getContent() << std::endl;

    // Undo again
    std::cout << "\nUndoing again:" << std::endl;
    undoManager.undo(editor);

    // Show content after second undo
    std::cout << "\nContent after second undo: " << editor.getContent() << std::endl;

    // Try to undo when nothing is left
    std::cout << "\nTrying to undo when nothing is left:" << std::endl;
    undoManager.undo(editor);

    return 0;
} 