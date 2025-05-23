#include "image_proxy.h"
#include "high_resolution_image.h"
#include <iostream>

ImageProxy::ImageProxy(const std::string& fileName)
    : fileName(fileName) {
    std::cout << "ImageProxy: Created for " << fileName << ". Real image not loaded yet." << std::endl;
}

void ImageProxy::display() {
    // Lazy initialization: Load only when display() is called
    if (!realImage) {
        std::cout << "ImageProxy: display() requested for " << fileName << ". Loading high-resolution image..." << std::endl;
        realImage = std::make_unique<HighResolutionImage>(fileName);
    } else {
        std::cout << "ImageProxy: Using cached high-resolution image for " << fileName << std::endl;
    }

    // Delegate the display call to the real image
    realImage->display();
}

std::string ImageProxy::getFileName() const {
    // Can safely return without loading the image
    return fileName;
} 