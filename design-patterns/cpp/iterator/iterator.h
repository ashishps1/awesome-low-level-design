#pragma once
#include <string>

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual std::string next() = 0;
}; 