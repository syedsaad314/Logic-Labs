/*
 * Problem: Not everyone should be able to reboot the server or view financial logs.
 * Logic: Role-Based Access Control (RBAC). We map users to roles (ADMIN, GUEST), 
 * and roles to permissions. We intercept actions and block unauthorized access.
 */

import java.util.*;

public class RoleManager {
    private Map<String, List<String>> rolePermissions = new HashMap<>();

    public RoleManager() {
        // Define the security matrix
        rolePermissions.put("ADMIN", Arrays.asList("READ_LOGS", "REBOOT_SERVER", "EDIT_USERS"));
        rolePermissions.put("GUEST", Arrays.asList("READ_LOGS"));
    }

    public boolean checkAccess(String role, String action) {
        System.out.print("  \033[36m[Auth Check]\033[0m " + role + " attempting " + action + "... ");
        
        if (rolePermissions.containsKey(role) && rolePermissions.get(role).contains(action)) {
            System.out.println("\033[32mGRANTED\033[0m");
            return true;
        } else {
            System.out.println("\033[31mDENIED\033[0m");
            return false;
        }
    }

    public static void main(String[] args) {
        System.out.println("\033[1m\n--- RBAC Security Engine ---\033[0m");
        RoleManager security = new RoleManager();
        
        security.checkAccess("GUEST", "READ_LOGS");
        security.checkAccess("GUEST", "REBOOT_SERVER");
        security.checkAccess("ADMIN", "REBOOT_SERVER");
    }
}