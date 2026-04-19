/*
 * Problem: If a user uploads a video, the app shouldn't freeze while processing it. 
 * Heavy logic must be handled in the background without blocking the main interface.
 * Logic: Producer-Consumer pattern using a Thread-safe BlockingQueue. The main thread 
 * accepts user commands instantly, while a separate background worker thread polls the queue 
 * and processes jobs sequentially.
 */

import java.util.Scanner;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

class WorkerThread implements Runnable {
    private BlockingQueue<String> queue;

    public WorkerThread(BlockingQueue<String> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            while (true) {
                String task = queue.take(); // Blocks until a task is available
                if (task.equals("KILL_WORKER")) break;

                System.out.println("\n  \033[90m[Worker] Started processing: " + task + "\033[0m");
                Thread.sleep(3000); // Simulate heavy processing time (3 seconds)
                System.out.println("  \033[32m[Worker] ✓ Completed: " + task + "\033[0m");
                System.out.print("\033[1mMain > \033[0m"); // Re-prompt UI seamlessly
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class TaskQueue {
    public static void main(String[] args) {
        BlockingQueue<String> queue = new LinkedBlockingQueue<>();
        Thread worker = new Thread(new WorkerThread(queue));
        worker.start();

        Scanner sc = new Scanner(System.in);
        System.out.println("\033[1m\n--- Async Job Processing Engine ---\033[0m");
        System.out.println("\033[90mThe main thread remains unblocked while the background worker handles jobs.\033[0m");
        System.out.println("\033[90mType a job name to add it to the queue (e.g., 'Upload_File', 'Send_Email'). Type 'exit' to quit.\033[0m\n");

        while (true) {
            System.out.print("\033[1mMain > \033[0m");
            String input = sc.nextLine().trim();

            if (input.equalsIgnoreCase("exit")) {
                queue.offer("KILL_WORKER"); // Safe shutdown
                break;
            }

            if (!input.isEmpty()) {
                queue.offer(input);
                System.out.println("  \033[36m[+] Job added to queue. (Queue size: " + queue.size() + ")\033[0m");
            }
        }
        
        System.out.println("\033[90mWaiting for background worker to finish remaining jobs...\033[0m");
        try {
            worker.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        sc.close();
    }
}