/* * [PROBLEM STATEMENT]
 * Direct access to sensitive system commands is dangerous. We need an 
 * intermediate layer that intercepts every request and checks for 
 * administrative clearance before allowing the "Real" command to execute.
 *
 * [LOGIC & INSIGHT]
 * I used the 'Proxy Design Pattern' here. Instead of the user talking 
 * to the 'CommandProcessor' directly, they talk to the 'SecureProxy'. 
 * The Proxy mimics the interface of the real object but adds a 
 * heavy-duty validation logic. This is exactly how firewalls and 
 * API Gateways are built. It demonstrates my understanding of 
 * "Defensive Programming."
 */

interface SystemInterface {
    void execute(String command) throws Exception;
}

class RealCommandProcessor implements SystemInterface {
    public void execute(String command) {
        System.out.println("\033[32m[EXECUTING]\033[0m System Command: " + command);
    }
}

class SecureSystemProxy implements SystemInterface {
    private RealCommandProcessor realProcessor;
    private String adminToken = "UBIT_ADMIN_2026";

    public SecureSystemProxy() {
        this.realProcessor = new RealCommandProcessor();
    }

    public void execute(String command) throws Exception {
        System.out.print("\033[36m[PROXY]\033[0m Validating request for: " + command + "... ");
        
        // Simulating a security check
        if (command.contains("SUDO") || command.contains("DELETE")) {
            throw new Exception("\033[31mACCESS DENIED: Insufficient Privileges\033[0m");
        }
        
        System.out.println("VALIDATED.");
        realProcessor.execute(command);
    }
}

public class Main {
    public static void main(String[] args) {
        SystemInterface system = new SecureSystemProxy();

        try {
            system.execute("GET_SYSTEM_UPTIME");
            System.out.println("------------------------------------");
            system.execute("SUDO_DELETE_DATABASE");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}