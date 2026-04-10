/*
 * Topic: Concurrency & Multithreading
 * Problem: If an application downloads files one by one (synchronously), the user 
 * interface freezes and bandwidth goes underutilized.
 * Approach: We use the ExecutorService framework to spawn multiple background threads. 
 * Each file is treated as a separate 'Runnable' task, allowing the system to process 
 * multiple downloads simultaneously without blocking the main application thread.
 */

import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

class DownloadTask implements Runnable {
    private String filename;

    public DownloadTask(String filename) {
        this.filename = filename;
    }

    @Override
    public void run() {
        try {
            System.out.println("\033[36m  [Starting]\033[0m Fetching " + filename + "...");
            // Simulate variable network delay (1 to 3 seconds)
            Thread.sleep((long) (Math.random() * 2000 + 1000));
            System.out.println("\033[32m  [Complete]\033[0m " + filename + " successfully acquired.");
        } catch (InterruptedException e) {
            System.out.println("Download interrupted for " + filename);
        }
    }
}

public class ThreadedDownloader {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("\033[1m\n--- Asynchronous Downloader Engine ---\033[0m");
        
        System.out.print("How many parallel download threads should we allocate? (e.g., 3): ");
        int threadCount = sc.nextInt();
        sc.nextLine(); // consume newline
        
        System.out.print("Enter filenames to download, separated by commas (e.g., data.json, image.png, script.js): ");
        String[] files = sc.nextLine().split(",");

        // Initialize a thread pool
        ExecutorService executor = Executors.newFixedThreadPool(threadCount);

        System.out.println("\n\033[33mInitializing network requests...\033[0m");
        for (String file : files) {
            executor.submit(new DownloadTask(file.trim()));
        }

        executor.shutdown();
        try {
            executor.awaitTermination(1, TimeUnit.MINUTES);
            System.out.println("\033[1m\nAll concurrent tasks finished gracefully.\033[0m");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        sc.close();
    }
}