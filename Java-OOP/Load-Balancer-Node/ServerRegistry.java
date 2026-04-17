/*
 * Problem: A single server can't handle a million users. We need to distribute traffic 
 * evenly across multiple servers, but also smartly skip servers that have crashed.
 * Logic: A Round-Robin Load Balancer with Health Checks. It maintains a circular queue 
 * of server nodes. When a request comes in, it routes it to the next *healthy* server in line, 
 * bypassing any that are marked as down.
 */

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class ServerNode {
    String ipAddress;
    boolean isHealthy;

    public ServerNode(String ip) {
        this.ipAddress = ip;
        this.isHealthy = true;
    }
}

public class ServerRegistry {
    private List<ServerNode> servers = new ArrayList<>();
    private int currentIndex = 0;

    public ServerRegistry() {
        servers.add(new ServerNode("192.168.1.101"));
        servers.add(new ServerNode("192.168.1.102"));
        servers.add(new ServerNode("192.168.1.103"));
    }

    public void routeRequest(String payload) {
        int attempts = 0;
        while (attempts < servers.size()) {
            ServerNode node = servers.get(currentIndex);
            currentIndex = (currentIndex + 1) % servers.size(); // Move to next for round-robin

            if (node.isHealthy) {
                System.out.println("  \033[32m✓ Routed:\033[0m Payload '" + payload + "' sent to \033[1m" + node.ipAddress + "\033[0m");
                return;
            }
            attempts++;
        }
        System.out.println("  \033[31m[503 Service Unavailable]\033[0m All backend servers are currently dead.");
    }

    public void toggleServerStatus(String ip, boolean status) {
        for (ServerNode node : servers) {
            if (node.ipAddress.equals(ip)) {
                node.isHealthy = status;
                String state = status ? "\033[32mONLINE\033[0m" : "\033[31mOFFLINE\033[0m";
                System.out.println("  \033[90mSystem Event: Node " + ip + " is now " + state + ".\033[0m");
                return;
            }
        }
        System.out.println("  \033[31mServer IP not found in registry.\033[0m");
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ServerRegistry lb = new ServerRegistry();

        System.out.println("\033[1m\n--- Round-Robin Load Balancer ---\033[0m");
        System.out.println("\033[90mCommands:\033[0m");
        System.out.println("\033[90m  req <data>         (e.g., req GetUserFile)\033[0m");
        System.out.println("\033[90m  kill <ip>          (e.g., kill 192.168.1.102)\033[0m");
        System.out.println("\033[90m  revive <ip>\033[0m");
        System.out.println("\033[90m  exit\033[0m\n");

        while (true) {
            System.out.print("\033[1mNetwork > \033[0m");
            String[] input = sc.nextLine().trim().split(" ", 2);
            String cmd = input[0].toLowerCase();

            if (cmd.equals("exit")) break;

            if (cmd.equals("req") && input.length == 2) {
                lb.routeRequest(input[1]);
            } else if (cmd.equals("kill") && input.length == 2) {
                lb.toggleServerStatus(input[1], false);
            } else if (cmd.equals("revive") && input.length == 2) {
                lb.toggleServerStatus(input[1], true);
            } else {
                System.out.println("  \033[31mInvalid command.\033[0m");
            }
        }
        sc.close();
    }
}