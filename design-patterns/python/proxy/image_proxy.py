from typing import Optional
from .image import Image
from .high_resolution_image import HighResolutionImage

class ImageProxy(Image):
    def __init__(self, file_name: str):
        self.file_name = file_name
        self.real_image: Optional[HighResolutionImage] = None
        print(f"ImageProxy: Created for {file_name}. Real image not loaded yet.")

    def get_file_name(self) -> str:
        # Can safely return without loading the image
        return self.file_name

    def display(self) -> None:
        # Lazy initialization: Load only when display() is called
        if self.real_image is None:
            print(f"ImageProxy: display() requested for {self.file_name}. Loading high-resolution image...")
            self.real_image = HighResolutionImage(self.file_name)
        else:
            print(f"ImageProxy: Using cached high-resolution image for {self.file_name}")

        # Delegate the display call to the real image
        self.real_image.display() 