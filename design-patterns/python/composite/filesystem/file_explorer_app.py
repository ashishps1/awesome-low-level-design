from .folder import Folder
from .file import File

def main():
    # Create a file system structure
    root = Folder("Root")
    
    documents = Folder("Documents")
    pictures = Folder("Pictures")
    music = Folder("Music")
    
    # Add files to Documents
    doc1 = File("report.txt", 1024)
    doc2 = File("presentation.pptx", 2048)
    documents.add_item(doc1)
    documents.add_item(doc2)
    
    # Add files to Pictures
    pic1 = File("vacation.jpg", 3072)
    pic2 = File("family.png", 4096)
    pictures.add_item(pic1)
    pictures.add_item(pic2)
    
    # Add files to Music
    song1 = File("song1.mp3", 5120)
    song2 = File("song2.mp3", 6144)
    music.add_item(song1)
    music.add_item(song2)
    
    # Add folders to root
    root.add_item(documents)
    root.add_item(pictures)
    root.add_item(music)
    
    # Display file system structure
    print("File System Structure:")
    print(root)
    print(documents)
    print(pictures)
    print(music)
    
    # Display total size
    print(f"\nTotal Size: {root.get_size()} bytes")

if __name__ == "__main__":
    main() 