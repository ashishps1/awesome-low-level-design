public class ImageProxy implements Image {
    private String fileName;
    private HighResolutionImage realImage; // RealSubject

    public ImageProxy(String fileName) {
        this.fileName = fileName;
        System.out.println("ImageProxy: Created for " + fileName + ". Real image not loaded yet.");
    }

    @Override
    public String getFileName() {
        // Can safely return without loading the image
        return fileName;
    }

    @Override
    public void display() {
        // Lazy initialization: Load only when display() is called
        if (realImage == null) {
            System.out.println("ImageProxy: display() requested for " + fileName + ". Loading high-resolution image...");
            realImage = new HighResolutionImage(fileName);
        } else {
            System.out.println("ImageProxy: Using cached high-resolution image for " + fileName);
        }

        // Delegate the display call to the real image
        realImage.display();
    }
}