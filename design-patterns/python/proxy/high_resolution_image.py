import time
from .image import Image

class HighResolutionImage(Image):
    def __init__(self, file_name: str):
        self.file_name = file_name
        self.image_data = None  # Simulate large data
        self.load_image_from_disk()  # Expensive operation!

    def load_image_from_disk(self) -> None:
        print(f"Loading image: {self.file_name} from disk (Expensive Operation)...")
        # Simulate disk read and memory allocation
        time.sleep(2)  # Simulate delay
        self.image_data = bytearray(10 * 1024 * 1024)  # 10MB
        print(f"Image {self.file_name} loaded successfully.")

    def display(self) -> None:
        print(f"Displaying image: {self.file_name}")
        # Actual rendering logic would go here

    def get_file_name(self) -> str:
        return self.file_name 