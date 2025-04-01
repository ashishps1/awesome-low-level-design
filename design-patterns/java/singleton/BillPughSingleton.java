class BillPughSingleton {
    // Private constructor to prevent instantiation
    private BillPughSingleton() {}
    
    // Static inner class that holds the instance
    private static class SingletonHelper {
        private static final BillPughSingleton INSTANCE = new BillPughSingleton();
    }
    
    // Public method to get the instance
    public static BillPughSingleton getInstance() {
        return SingletonHelper.INSTANCE;
    }
}