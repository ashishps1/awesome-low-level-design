#include "plain_text_view.h"
#include <iostream>

PlainTextView::PlainTextView(const std::string& text) : text(text) {}

void PlainTextView::render() {
    std::cout << text;
} 