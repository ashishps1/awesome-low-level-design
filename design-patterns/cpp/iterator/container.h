#pragma once
#include "iterator.h"

class Container {
public:
    virtual ~Container() = default;
    virtual Iterator* getIterator() = 0;
}; 