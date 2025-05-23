#pragma once
#include "text_editor.h"
#include <stack>

class TextEditorUndoManager {
public:
    void save(TextEditor& editor);
    void undo(TextEditor& editor);

private:
    std::stack<TextEditorMemento> history;
}; 