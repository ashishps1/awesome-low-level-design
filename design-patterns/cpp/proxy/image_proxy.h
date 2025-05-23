#pragma once
#include "image.h"
#include <memory>

class HighResolutionImage;

class ImageProxy : public Image {
public:
    explicit ImageProxy(const std::string& fileName);
    void display() override;
    std::string getFileName() const override;

private:
    std::string fileName;
    std::unique_ptr<HighResolutionImage> realImage;
}; 