#pragma once
#include "file_system_item.h"
#include <string>
#include <vector>
#include <memory>

class Folder : public FileSystemItem {
public:
    explicit Folder(const std::string& name);
    void addItem(std::shared_ptr<FileSystemItem> item);
    int getSize() const override;
    void printStructure(const std::string& indent) const override;
    void delete() override;

private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemItem>> children;
}; 