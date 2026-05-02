/*
 * Problem: If a database goes down, 10,000 incoming requests will hang, consuming all 
 * server memory and taking the whole application down with it (Cascading Failure).
 * Logic: The Circuit Breaker. If failures cross a threshold (e.g., 3 fails), the circuit 
 * "Trips" (Opens). It immediately rejects new requests to save the server, waits 5 seconds, 
 * and then tests the connection again (Half-Open).
 */

public class CircuitBreaker {
    private enum State { CLOSED, OPEN, HALF_OPEN }
    
    private State state = State.CLOSED;
    private int failureCount = 0;
    private final int THRESHOLD = 3;
    private long lastFailureTime = 0;
    private final long RESET_TIMEOUT = 5000; // 5 seconds

    public void attemptCall(boolean serviceIsOnline) {
        if (state == State.OPEN) {
            if (System.currentTimeMillis() - lastFailureTime > RESET_TIMEOUT) {
                System.out.println("  \033[33m[Circuit HALF-OPEN]\033[0m Testing service recovery...");
                state = State.HALF_OPEN;
            } else {
                System.out.println("  \033[31m[Circuit OPEN - FAST FAIL]\033[0m Request rejected to prevent cascading failure.");
                return;
            }
        }

        if (serviceIsOnline) {
            System.out.println("  \033[32m[200 OK]\033[0m Service call successful.");
            state = State.CLOSED;
            failureCount = 0;
        } else {
            failureCount++;
            System.out.println("  \033[35m[500 ERROR]\033[0m Service call failed. (Failures: " + failureCount + "/" + THRESHOLD + ")");
            if (failureCount >= THRESHOLD) {
                System.out.println("  \033[31m[CRITICAL]\033[0m Threshold reached. TRIPPING CIRCUIT BREAKER.");
                state = State.OPEN;
                lastFailureTime = System.currentTimeMillis();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        System.out.println("\033[1m\n--- Distributed Circuit Breaker ---\033[0m");
        CircuitBreaker cb = new CircuitBreaker();
        
        cb.attemptCall(false);
        cb.attemptCall(false);
        cb.attemptCall(false); // Trips here
        cb.attemptCall(true);  // Fails fast
        
        System.out.println("  \033[90mWaiting 5 seconds for system cooldown...\033[0m");
        Thread.sleep(5100);
        
        cb.attemptCall(true);  // Recovers
    }
}