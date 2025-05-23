#pragma once
#include <string>

class FileSystemItem {
public:
    virtual ~FileSystemItem() = default;
    virtual int getSize() const = 0;
    virtual void printStructure(const std::string& indent) const = 0;
    virtual void delete() = 0;
}; 