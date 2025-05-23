#include "text_editor.h"
#include <iostream>

void TextEditor::type(const std::string& newText) {
    content += newText;
    std::cout << "Typed: " << newText << std::endl;
}

std::string TextEditor::getContent() const {
    return content;
}

TextEditorMemento TextEditor::save() const {
    std::cout << "Saving state: \"" << content << "\"" << std::endl;
    return TextEditorMemento(content);
}

void TextEditor::restore(const TextEditorMemento& memento) {
    content = memento.getState();
    std::cout << "Restored state to: \"" << content << "\"" << std::endl;
} 