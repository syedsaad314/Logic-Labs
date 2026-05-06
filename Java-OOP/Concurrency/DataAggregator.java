/*
 * Problem: A dashboard needs user data, financial data, and server stats. If we fetch 
 * these one by one (synchronously), a 1-second delay on each means a 3-second load time.
 * Logic: CompletableFuture. We fire all three requests simultaneously on different 
 * background threads. The total wait time drops to the speed of the slowest single request.
 */

import java.util.concurrent.CompletableFuture;

public class DataAggregator {

    private static CompletableFuture<String> fetchService(String serviceName, long delayMs) {
        return CompletableFuture.supplyAsync(() -> {
            try { Thread.sleep(delayMs); } catch (InterruptedException e) {}
            System.out.println("  \033[32m[OK]\033[0m " + serviceName + " payload received.");
            return serviceName + "_DATA";
        });
    }

    public static void main(String[] args) {
        System.out.println("\033[1m\n--- Async Data Aggregator ---\033[0m");
        System.out.println("  \033[90m[System]\033[0m Firing concurrent requests...\n");

        long startTime = System.currentTimeMillis();

        CompletableFuture<String> userFetch = fetchService("Auth_Service", 800);
        CompletableFuture<String> financeFetch = fetchService("Ledger_Service", 1200);
        CompletableFuture<String> serverFetch = fetchService("Telemetry_Service", 500);

        // Wait for ALL of them to complete
        CompletableFuture.allOf(userFetch, financeFetch, serverFetch).join();

        long endTime = System.currentTimeMillis();
        System.out.println("\n  \033[36m[Aggregator]\033[0m All data compiled in " + (endTime - startTime) + "ms.");
    }
}