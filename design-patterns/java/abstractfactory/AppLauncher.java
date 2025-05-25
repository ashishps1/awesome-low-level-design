public class AppLauncher {
    public static void main(String[] args) {
        // Simulate platform detection
        String os = System.getProperty("os.name").toLowerCase();
        GUIFactory factory;

        if (os.contains("mac")) {
            factory = new MacOSFactory();
        } else {
            factory = new WindowsFactory();
        }

        Application app = new Application(factory);
        app.renderUI();
    }
}