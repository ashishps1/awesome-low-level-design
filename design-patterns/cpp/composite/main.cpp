#include "file.h"
#include "folder.h"
#include <iostream>
#include <memory>

int main() {
    auto file1 = std::make_shared<File>("readme.txt", 5);
    auto file2 = std::make_shared<File>("photo.jpg", 1500);
    auto file3 = std::make_shared<File>("data.csv", 300);

    auto documents = std::make_shared<Folder>("Documents");
    documents->addItem(file1);
    documents->addItem(file3);

    auto pictures = std::make_shared<Folder>("Pictures");
    pictures->addItem(file2);

    auto home = std::make_shared<Folder>("Home");
    home->addItem(documents);
    home->addItem(pictures);

    std::cout << "---- File Structure ----" << std::endl;
    home->printStructure("");

    std::cout << "\nTotal Size: " << home->getSize() << " KB" << std::endl;

    std::cout << "\n---- Deleting All ----" << std::endl;
    home->delete();

    return 0;
} 