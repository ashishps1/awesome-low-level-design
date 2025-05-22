public class HighResolutionImage implements Image {
    private String fileName;
    private byte[] imageData; // Simulate large data

    public HighResolutionImage(String fileName) {
        this.fileName = fileName;
        loadImageFromDisk(); // Expensive operation!
    }

    private void loadImageFromDisk() {
        System.out.println("Loading image: " + fileName + " from disk (Expensive Operation)...");
        // Simulate disk read and memory allocation
        try {
            Thread.sleep(2000); // Simulate delay
            this.imageData = new byte[10 * 1024 * 1024]; // 10MB
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        System.out.println("Image " + fileName + " loaded successfully.");
    }

    @Override
    public void display() {
        System.out.println("Displaying image: " + fileName);
        // Actual rendering logic would go here
    }

    @Override
    public String getFileName() {
        return fileName;
    }
}
