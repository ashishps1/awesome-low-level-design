#pragma once
#include "text_view.h"
#include <string>

class PlainTextView : public TextView {
public:
    explicit PlainTextView(const std::string& text);
    void render() override;
private:
    std::string text;
}; 