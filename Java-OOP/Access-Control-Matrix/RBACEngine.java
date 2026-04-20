/*
 * Problem: Hardcoding "if (user == admin)" throughout an application leads to security flaws. 
 * We need a structured way to determine exactly who can access what endpoints.
 * Logic: An Access Control Matrix. We map standard Roles (Admin, Editor, Guest) to specific 
 * Permissions (READ, WRITE, DELETE). When a user attempts an action, the engine checks their 
 * assigned role against the required permission before allowing execution.
 */

import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

enum Permission { READ_DOCS, EDIT_DOCS, DELETE_USERS, VIEW_DASHBOARD }
enum Role { ADMIN, EDITOR, GUEST }

public class RBACEngine {
    private HashMap<Role, HashSet<Permission>> rolePermissions = new HashMap<>();
    private HashMap<String, Role> userDatabase = new HashMap<>();

    public RBACEngine() {
        // Define matrix policy
        rolePermissions.put(Role.ADMIN, new HashSet<>());
        rolePermissions.get(Role.ADMIN).add(Permission.READ_DOCS);
        rolePermissions.get(Role.ADMIN).add(Permission.EDIT_DOCS);
        rolePermissions.get(Role.ADMIN).add(Permission.DELETE_USERS);
        rolePermissions.get(Role.ADMIN).add(Permission.VIEW_DASHBOARD);

        rolePermissions.put(Role.EDITOR, new HashSet<>());
        rolePermissions.get(Role.EDITOR).add(Permission.READ_DOCS);
        rolePermissions.get(Role.EDITOR).add(Permission.EDIT_DOCS);

        rolePermissions.put(Role.GUEST, new HashSet<>());
        rolePermissions.get(Role.GUEST).add(Permission.READ_DOCS);

        // Seed users
        userDatabase.put("saad", Role.ADMIN);
        userDatabase.put("ali", Role.EDITOR);
        userDatabase.put("guest1", Role.GUEST);
    }

    public void checkAccess(String username, Permission requestedAction) {
        Role userRole = userDatabase.get(username.toLowerCase());
        
        if (userRole == null) {
            System.out.println("  \033[31m[401 Unauthorized]\033[0m User '" + username + "' does not exist.");
            return;
        }

        HashSet<Permission> perms = rolePermissions.get(userRole);
        
        if (perms.contains(requestedAction)) {
            System.out.println("  \033[32m[200 OK]\033[0m Action " + requestedAction + " granted to " + username + " (" + userRole + ").");
        } else {
            System.out.println("  \033[31m[403 Forbidden]\033[0m " + username + " (" + userRole + ") lacks permission for " + requestedAction + ".");
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        RBACEngine rbac = new RBACEngine();

        System.out.println("\033[1m\n--- Role-Based Access Control Middleware ---\033[0m");
        System.out.println("\033[90mUsers: saad (Admin), ali (Editor), guest1 (Guest)\033[0m");
        System.out.println("\033[90mActions: READ_DOCS, EDIT_DOCS, DELETE_USERS, VIEW_DASHBOARD\033[0m");
        System.out.println("\033[90mTest an endpoint access. Format: <user> <action>\033[0m\n");

        while (true) {
            System.out.print("\033[1mServer > \033[0m");
            String[] input = sc.nextLine().trim().split(" ");
            
            if (input[0].equalsIgnoreCase("exit")) break;
            
            if (input.length == 2) {
                try {
                    Permission perm = Permission.valueOf(input[1].toUpperCase());
                    rbac.checkAccess(input[0], perm);
                } catch (IllegalArgumentException e) {
                    System.out.println("  \033[31mInvalid action specified.\033[0m");
                }
            } else {
                System.out.println("  \033[31mFormat: username ACTION\033[0m");
            }
        }
        sc.close();
    }
}