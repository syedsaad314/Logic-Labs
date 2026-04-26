/*
 * Problem (The Commons): When a user checkout fails, it might have touched 5 different 
 * services. Finding out *where* it broke across 10,000 lines of disparate server logs is impossible.
 * Logic: Correlation IDs. The API Gateway assigns a unique UUID to every incoming request. 
 * This ID is passed inside the headers to every downstream service. If a crash happens, 
 * you simply search the master log for that one ID to see the exact chain of execution.
 */

import java.util.UUID;
import java.util.Scanner;

public class RequestTracer {

    public static String generateCorrelationId() {
        return "REQ-" + UUID.randomUUID().toString().substring(0, 8).toUpperCase();
    }

    public static void simulateMicroserviceChain(String endpoint) {
        String correlationId = generateCorrelationId();
        System.out.println("\n  \033[36m[Gateway]\033[0m Request received. Generated ID: [" + correlationId + "]");

        // Service 1: Auth
        System.out.println("  \033[90m[Auth Service]\033[0m Processing [" + correlationId + "] -> Token Validated.");

        // Service 2: Target
        if (endpoint.equalsIgnoreCase("/checkout")) {
            System.out.println("  \033[90m[Order Service]\033[0m Processing [" + correlationId + "] -> Building Order...");
            System.out.println("  \033[31m[Payment Service]\033[0m FATAL ERROR on [" + correlationId + "] -> Card Declined.");
        } else {
            System.out.println("  \033[90m[Profile Service]\033[0m Processing [" + correlationId + "] -> Data Fetched.");
            System.out.println("  \033[32m[Gateway]\033[0m Response sent for [" + correlationId + "]");
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("\033[1m\n--- TraceLink Injector (Distributed Logging) ---\033[0m");
        System.out.println("\033[90mEnter an endpoint to simulate a distributed request chain.\033[0m");

        while (true) {
            System.out.print("\033[1mHit Endpoint (e.g., /checkout, /profile) > \033[0m");
            String input = sc.nextLine().trim();
            if (input.equalsIgnoreCase("exit")) break;
            
            if (!input.isEmpty()) simulateMicroserviceChain(input);
        }
        sc.close();
    }
}