/*
 * Problem: Managing thousands of active WebSocket connections for a live dashboard requires 
 * thread-safe collections. Using a standard HashMap will throw a ConcurrentModificationException 
 * when users connect and disconnect while a server broadcast is happening.
 * Logic: Concurrent Collections. Utilizing ConcurrentHashMap ensures that adding, removing, 
 * and iterating over active user sessions is completely thread-safe and non-blocking.
 */

import java.util.concurrent.ConcurrentHashMap;
import java.util.Map;
import java.util.Scanner;

public class WebSocketSessionManager {
    // Simulating a pool of active WebSocket connections
    private final Map<String, String> activeSessions = new ConcurrentHashMap<>();

    public void onConnect(String sessionId, String userId) {
        activeSessions.put(sessionId, userId);
        System.out.println("  \033[32m[+ Connected]\033[0m Session: " + sessionId + " | User: " + userId);
    }

    public void onDisconnect(String sessionId) {
        String userId = activeSessions.remove(sessionId);
        if (userId != null) {
            System.out.println("  \033[31m[- Disconnected]\033[0m Session: " + sessionId + " | User: " + userId);
        }
    }

    public void broadcastUpdate(String jsonPayload) {
        System.out.println("\n  \033[36m[Broadcasting]\033[0m Pushing payload to " + activeSessions.size() + " active clients...");
        for (Map.Entry<String, String> session : activeSessions.entrySet()) {
            // In a real app, this writes to the socket output stream
            System.out.println("    -> Sent to " + session.getValue() + " (Session: " + session.getKey() + ")");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        WebSocketSessionManager pool = new WebSocketSessionManager();

        System.out.println("\033[1m\n--- Concurrent WebSocket Session Pool ---\033[0m");
        System.out.println("\033[90mCommands: 'join <user>', 'drop <session_id>', 'push <data>', 'exit'\033[0m\n");

        int sessionCounter = 100;

        while (true) {
            System.out.print("\033[1mSocket Pool > \033[0m");
            String[] cmd = sc.nextLine().split(" ", 2);
            if (cmd[0].equalsIgnoreCase("exit")) break;

            if (cmd[0].equalsIgnoreCase("join") && cmd.length > 1) {
                pool.onConnect("sess_" + (++sessionCounter), cmd[1]);
            } else if (cmd[0].equalsIgnoreCase("drop") && cmd.length > 1) {
                pool.onDisconnect(cmd[1]);
            } else if (cmd[0].equalsIgnoreCase("push") && cmd.length > 1) {
                pool.broadcastUpdate(cmd[1]);
            }
        }
        sc.close();
    }
}