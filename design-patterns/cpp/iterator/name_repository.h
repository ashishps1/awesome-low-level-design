#pragma once
#include "container.h"
#include <vector>
#include <string>

class NameRepository : public Container {
public:
    NameRepository();
    Iterator* getIterator() override;

private:
    std::vector<std::string> names;
}; 