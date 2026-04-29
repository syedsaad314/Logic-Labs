/*
 * Problem: When a background worker fails to process a message (e.g., bad payload, database offline), 
 * it puts it back in the queue. The worker then retries it endlessly, clogging the pipeline 
 * and blocking all healthy messages from being processed.
 * Logic: The Dead Letter Queue. If a message fails 'N' consecutive times, we permanently remove 
 * it from the active processing pipeline and route it to a segregated "Dead" queue. This keeps 
 * operations running while allowing engineers to manually inspect the corrupted payloads later.
 */

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class DeadLetterQueue {
    private final Queue<String> activeQueue = new LinkedList<>();
    private final Queue<String> deadLetterQueue = new LinkedList<>();
    private final int MAX_RETRIES = 3;
    
    // Tracks retries for simplicity in this demo
    private int currentRetries = 0;

    public void publish(String payload) {
        activeQueue.add(payload);
        System.out.println("  \033[32m[+ Published]\033[0m Message added to active queue: " + payload);
    }

    public void processNext(boolean simulateSuccess) {
        if (activeQueue.isEmpty()) {
            System.out.println("  \033[90mQueue is empty.\033[0m");
            return;
        }

        String message = activeQueue.peek();

        if (simulateSuccess) {
            activeQueue.poll();
            currentRetries = 0;
            System.out.println("  \033[32m[✓ Success]\033[0m Processed and acknowledged: " + message);
        } else {
            currentRetries++;
            System.out.println("  \033[33m[✗ Failed]\033[0m Processing error. Retry " + currentRetries + "/" + MAX_RETRIES);
            
            if (currentRetries >= MAX_RETRIES) {
                System.out.println("  \033[31m[☠ Poison Pill]\033[0m Max retries hit. Moving to Dead Letter Queue.");
                deadLetterQueue.add(activeQueue.poll());
                currentRetries = 0;
            }
        }
    }

    public void viewDLQ() {
        System.out.println("\n  \033[1m--- Dead Letter Queue Inspection ---\033[0m");
        if (deadLetterQueue.isEmpty()) System.out.println("  \033[90mClean. No failed messages.\033[0m\n");
        for (String msg : deadLetterQueue) System.out.println("  -> " + msg);
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        DeadLetterQueue dlq = new DeadLetterQueue();

        System.out.println("\033[1m\n--- DLQ Message Processor ---\033[0m");
        dlq.publish("Order_7781_Process");
        
        while (true) {
            System.out.print("\033[1mWorker (s=success, f=fail, dlq=view, exit) > \033[0m");
            String cmd = sc.nextLine().trim();
            if (cmd.equals("exit")) break;

            if (cmd.equals("s")) dlq.processNext(true);
            else if (cmd.equals("f")) dlq.processNext(false);
            else if (cmd.equals("dlq")) dlq.viewDLQ();
        }
        sc.close();
    }
}