#include "text_editor_memento.h"

TextEditorMemento::TextEditorMemento(const std::string& state) : state(state) {}

std::string TextEditorMemento::getState() const {
    return state;
} 