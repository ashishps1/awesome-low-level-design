from .high_resolution_image import HighResolutionImage

def main():
    # Create high-resolution images directly
    print("Creating high-resolution images...")
    image1 = HighResolutionImage("nature.jpg")
    image2 = HighResolutionImage("city.jpg")
    image3 = HighResolutionImage("people.jpg")

    # Display images
    print("\nDisplaying images...")
    image1.display()
    image2.display()
    image3.display()

    # Note: All images are loaded at creation time, even if not displayed
    print("\nNote: All images were loaded at creation time, even if not displayed")

if __name__ == "__main__":
    main() 