#include "text_editor_undo_manager.h"
#include <iostream>

void TextEditorUndoManager::save(TextEditor& editor) {
    history.push(editor.save());
}

void TextEditorUndoManager::undo(TextEditor& editor) {
    if (!history.empty()) {
        editor.restore(history.top());
        history.pop();
    } else {
        std::cout << "Nothing to undo." << std::endl;
    }
} 