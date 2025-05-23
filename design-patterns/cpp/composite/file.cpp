#include "file.h"
#include <iostream>

File::File(const std::string& name, int size) : name(name), size(size) {}

int File::getSize() const {
    return size;
}

void File::printStructure(const std::string& indent) const {
    std::cout << indent << "- " << name << " (" << size << " KB)" << std::endl;
}

void File::delete() {
    std::cout << "Deleting file: " << name << std::endl;
} 