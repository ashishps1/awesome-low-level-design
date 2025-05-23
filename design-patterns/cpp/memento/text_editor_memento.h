#pragma once
#include <string>

class TextEditorMemento {
public:
    explicit TextEditorMemento(const std::string& state);
    std::string getState() const;

private:
    const std::string state;
}; 