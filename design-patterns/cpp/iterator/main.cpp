#include "name_repository.h"
#include <iostream>

int main() {
    NameRepository namesRepository;
    
    std::cout << "Names: ";
    for (Iterator* iter = namesRepository.getIterator(); iter->hasNext();) {
        std::string name = iter->next();
        std::cout << name << " ";
    }
    std::cout << std::endl;

    return 0;
} 