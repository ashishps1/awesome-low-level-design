#pragma once
#include "iterator.h"
#include <vector>
#include <string>

class NameIterator : public Iterator {
public:
    explicit NameIterator(const std::vector<std::string>& names);
    bool hasNext() override;
    std::string next() override;

private:
    std::vector<std::string> names;
    size_t index;
}; 