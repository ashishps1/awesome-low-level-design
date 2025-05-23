#include "name_iterator.h"

NameIterator::NameIterator(const std::vector<std::string>& names) 
    : names(names), index(0) {}

bool NameIterator::hasNext() {
    return index < names.size();
}

std::string NameIterator::next() {
    if (hasNext()) {
        return names[index++];
    }
    return "";
} 