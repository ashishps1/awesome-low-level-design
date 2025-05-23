#pragma once
#include "text_editor_memento.h"
#include <string>

class TextEditor {
public:
    void type(const std::string& newText);
    std::string getContent() const;
    TextEditorMemento save() const;
    void restore(const TextEditorMemento& memento);

private:
    std::string content;
}; 