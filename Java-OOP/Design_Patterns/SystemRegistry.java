/*
 * Problem: If every part of your app creates its own "Configuration" object, 
 * you'll have 5 different settings for the same app.
 * Logic: Thread-Safe Singleton. We ensure only ONE instance of the Registry exists 
 * globally. We use "Double-Checked Locking" to make it high-performance and thread-safe.
 */

public class SystemRegistry {
    private static volatile SystemRegistry instance;
    private String systemMode = "STANDBY";

    private SystemRegistry() {} // Private constructor prevents new keyword

    public static SystemRegistry getInstance() {
        if (instance == null) {
            synchronized (SystemRegistry.class) {
                if (instance == null) instance = new SystemRegistry();
            }
        }
        return instance;
    }

    public void setMode(String mode) { this.systemMode = mode; }
    public String getMode() { return this.systemMode; }

    public static void main(String[] args) {
        System.out.println("\033[1m\n--- Singleton System Registry ---\033[0m");
        SystemRegistry.getInstance().setMode("PRODUCTION_ACTIVE");
        System.out.println("  \033[36m[State]\033[0m Global Mode: " + SystemRegistry.getInstance().getMode());
    }
}