from .image_proxy import ImageProxy

def main():
    # Create image proxies
    print("Creating image proxies...")
    image1 = ImageProxy("nature.jpg")
    image2 = ImageProxy("city.jpg")
    image3 = ImageProxy("people.jpg")

    # Note: Images are not loaded yet
    print("\nNote: Images are not loaded yet, only proxies are created")

    # Display images (this will trigger loading)
    print("\nDisplaying images...")
    image1.display()  # This will load the image
    image2.display()  # This will load the image
    image3.display()  # This will load the image

    # Display again (should use cached images)
    print("\nDisplaying images again...")
    image1.display()  # Should use cached image
    image2.display()  # Should use cached image
    image3.display()  # Should use cached image

if __name__ == "__main__":
    main() 