#include "high_resolution_image.h"
#include <iostream>

HighResolutionImage::HighResolutionImage(const std::string& fileName)
    : fileName(fileName) {
    loadImageFromDisk();
}

void HighResolutionImage::loadImageFromDisk() {
    std::cout << "Loading image: " << fileName << " from disk (Expensive Operation)..." << std::endl;
    // Simulate disk read and memory allocation
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate delay
    imageData.resize(10 * 1024 * 1024); // 10MB
    std::cout << "Image " << fileName << " loaded successfully." << std::endl;
}

void HighResolutionImage::display() {
    std::cout << "Displaying image: " << fileName << std::endl;
    // Actual rendering logic would go here
}

std::string HighResolutionImage::getFileName() const {
    return fileName;
} 