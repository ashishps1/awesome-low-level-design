class ThreadSafeSingleton {
    // The single instance, initially null
    private static ThreadSafeSingleton instance;
    
    // Private constructor to prevent instantiation
    private ThreadSafeSingleton() {}
    
    // Public method to get the instance, with synchronized keyword
    public static synchronized ThreadSafeSingleton getInstance() {
        // Check if instance is null
        if (instance == null) {
            // If null, create a new instance
            instance = new ThreadSafeSingleton();
        }
        // Return the instance (either newly created or existing)
        return instance;
    }
}