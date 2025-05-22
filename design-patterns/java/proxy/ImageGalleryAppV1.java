public class ImageGalleryAppV1 {
    public static void main(String[] args) {
        System.out.println("Application Started. Initializing images for gallery...");

        // Imagine we need to create image objects for a list of thumbnails
        // Even if the user never clicks them, they get loaded!
        Image image1 = new HighResolutionImage("photo1.jpg");
        Image image2 = new HighResolutionImage("photo2.png");
        Image image3 = new HighResolutionImage("photo3.gif");

        System.out.println("\nGallery initialized. User might view an image now.");

        // User clicks on image1
        System.out.println("User requests to display " + image1.getFileName());
        image1.display();

        // User clicks on image3
        System.out.println("\nUser requests to display " + image3.getFileName());
        image3.display();

        // image2 was loaded but never displayed by the user in this session. Waste of resources!
        System.out.println("\nApplication finished.");
    }    
}
