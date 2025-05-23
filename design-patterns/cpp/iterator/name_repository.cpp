#include "name_repository.h"
#include "name_iterator.h"

NameRepository::NameRepository() {
    names = {"Robert", "John", "Julie", "Lora"};
}

Iterator* NameRepository::getIterator() {
    return new NameIterator(names);
} 