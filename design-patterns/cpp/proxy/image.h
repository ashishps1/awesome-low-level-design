#pragma once
#include <string>

class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
    virtual std::string getFileName() const = 0;
}; 