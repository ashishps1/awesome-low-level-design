public class ImageGalleryAppV2 {
    public static void main(String[] args) {
        System.out.println("Application Started. Initializing image proxies for gallery...");

        // Create lightweight proxies instead of full image objects
        Image image1 = new ImageProxy("photo1.jpg");
        Image image2 = new ImageProxy("photo2.png"); // Never displayed
        Image image3 = new ImageProxy("photo3.gif");

        System.out.println("\nGallery initialized. No images actually loaded yet.");
        System.out.println("Image 1 Filename: " + image1.getFileName()); // Does not trigger image load

        // User clicks on image1
        System.out.println("\nUser requests to display " + image1.getFileName());
        image1.display(); // Lazy loading happens here

        // User clicks on image1 again
        System.out.println("\nUser requests to display " + image1.getFileName() + " again.");
        image1.display(); // Already loaded; no loading delay

        // User clicks on image3
        System.out.println("\nUser requests to display " + image3.getFileName());
        image3.display(); // Triggers loading for image3

        System.out.println("\nApplication finished. Note: photo2.png was never loaded.");
    }
}