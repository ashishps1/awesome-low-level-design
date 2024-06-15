class LazySingleton {
    // The single instance, initially null
    private static LazySingleton instance;
    
    // Private constructor to prevent instantiation
    private LazySingleton() {}
    
    // Public method to get the instance
    public static LazySingleton getInstance() {
        // Check if instance is null
        if (instance == null) {
            // If null, create a new instance
            instance = new LazySingleton();
        }
        // Return the instance (either newly created or existing)
        return instance;
    }
}