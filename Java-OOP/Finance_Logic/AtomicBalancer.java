/*
 * Problem: In a multi-threaded banking app, if two threads try to update the same account 
 * balance simultaneously, you get a "Race Condition" where money literally disappears or duplicates.
 * Logic: Compare-And-Swap (CAS). Instead of slow heavy locks (synchronized), we use 
 * AtomicLong. It uses hardware-level instructions to ensure that the balance is only 
 * updated if it hasn't changed since we last checked it, ensuring 100% thread-safety.
 */

import java.util.concurrent.atomic.AtomicLong;

public class AtomicBalancer {
    private final AtomicLong balance = new AtomicLong(1000); // Initial 1000 PKR

    public void processTransaction(long amount) {
        long current = balance.get();
        if (balance.compareAndSet(current, current + amount)) {
            System.out.println("  \033[32m[Transaction Success]\033[0m New Balance: " + balance.get());
        } else {
            System.out.println("  \033[31m[Collision Detected]\033[0m Retrying transaction...");
            processTransaction(amount); // Recursive retry on collision
        }
    }

    public static void main(String[] args) {
        System.out.println("\033[1m\n--- Atomic Transaction Balancer ---\033[0m");
        AtomicBalancer account = new AtomicBalancer();
        account.processTransaction(500);
        account.processTransaction(-200);
    }
}