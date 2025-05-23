#include "image_proxy.h"
#include <iostream>

int main() {
    // Create image proxies
    std::cout << "Creating image proxies..." << std::endl;
    ImageProxy image1("nature.jpg");
    ImageProxy image2("city.jpg");
    ImageProxy image3("people.jpg");

    // Note: Images are not loaded yet
    std::cout << "\nNote: Images are not loaded yet, only proxies are created" << std::endl;

    // Display images (this will trigger loading)
    std::cout << "\nDisplaying images..." << std::endl;
    image1.display();  // This will load the image
    image2.display();  // This will load the image
    image3.display();  // This will load the image

    // Display again (should use cached images)
    std::cout << "\nDisplaying images again..." << std::endl;
    image1.display();  // Should use cached image
    image2.display();  // Should use cached image
    image3.display();  // Should use cached image

    return 0;
} 