#include "high_resolution_image.h"
#include <iostream>

int main() {
    // Create high-resolution images directly
    std::cout << "Creating high-resolution images..." << std::endl;
    HighResolutionImage image1("nature.jpg");
    HighResolutionImage image2("city.jpg");
    HighResolutionImage image3("people.jpg");

    // Display images
    std::cout << "\nDisplaying images..." << std::endl;
    image1.display();
    image2.display();
    image3.display();

    // Note: All images are loaded at creation time, even if not displayed
    std::cout << "\nNote: All images were loaded at creation time, even if not displayed" << std::endl;

    return 0;
} 