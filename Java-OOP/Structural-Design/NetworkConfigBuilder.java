/* * [PROBLEM STATEMENT]
 * In complex systems, objects like 'NetworkConfiguration' can have 20+ 
 * different parameters. A constructor with 20 arguments is unreadable 
 * and prone to errors. We need a way to construct these objects in a 
 * "readable, step-by-step" manner.
 *
 * [LOGIC & INSIGHT]
 * I implemented the 'Builder Design Pattern' using a fluent interface. 
 * Instead of one giant constructor, you 'chain' methods together like 
 * '.setIP().setPort().setEncryption()'. It reads like a sentence. 
 * I also added a 'Validation' step at the very end—the '.build()' 
 * method won't create the object if the critical fields (like IP) 
 * are missing. This is clean, safe, and professional code.
 */

class NetworkConfig {
    private final String ipAddress;
    private final int port;
    private final String protocol;
    private final boolean isEncrypted;

    private NetworkConfig(Builder builder) {
        this.ipAddress = builder.ipAddress;
        this.port = builder.port;
        this.protocol = builder.protocol;
        this.isEncrypted = builder.isEncrypted;
    }

    public void display() {
        System.out.println("\033[1m[CONFIG_LOADED]\033[0m");
        System.out.println("  IP: " + ipAddress + " | Protocol: " + protocol);
        System.out.println("  Security: " + (isEncrypted ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m"));
    }

    public static class Builder {
        private String ipAddress;
        private int port = 8080; // Default
        private String protocol = "TCP";
        private boolean isEncrypted = false;

        public Builder setIp(String ip) { this.ipAddress = ip; return this; }
        public Builder setPort(int port) { this.port = port; return this; }
        public Builder useSSL() { this.isEncrypted = true; return this; }

        public NetworkConfig build() {
            if (ipAddress == null) throw new IllegalStateException("IP Address is mandatory!");
            return new NetworkConfig(this);
        }
    }
}

public class NetworkConfigBuilder {
    public static void main(String[] args) {
        NetworkConfig config = new NetworkConfig.Builder()
                .setIp("192.168.1.1")
                .setPort(443)
                .useSSL()
                .build();

        config.display();
    }
}