/*
 * Problem: How do credit card companies instantly flag a fraudulent purchase, or 
 * servers detect a DDoS attack? They can't process massive historical databases in milliseconds.
 * Logic: Sliding Window Variance. The engine maintains a rolling window of recent data 
 * points. It calculates the moving average. If a new input deviates significantly 
 * from this rolling baseline, it is instantly flagged as an anomaly.
 */

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class StreamAnalyzer {
    private Queue<Double> window = new LinkedList<>();
    private int windowSize;
    private double currentSum = 0;
    private double thresholdMultiplier = 1.5;

    public StreamAnalyzer(int size) {
        this.windowSize = size;
    }

    public void processDataPoint(double value) {
        if (window.size() < windowSize) {
            window.add(value);
            currentSum += value;
            System.out.println("  \033[90m[Calibrating]\033[0m Data accepted. Building baseline...");
            return;
        }

        double movingAverage = currentSum / windowSize;
        
        // Remove oldest, add newest
        double oldest = window.poll();
        currentSum = currentSum - oldest + value;
        window.add(value);

        // Anomaly logic: If value is X times larger than average
        if (value > movingAverage * thresholdMultiplier) {
            System.out.println("  \033[31m[!] ANOMALY DETECTED:\033[0m Spike of " + value + " (Average was " + String.format("%.1f", movingAverage) + ")");
        } else {
            System.out.println("  \033[32m[OK]\033[0m Data normal. (Current Avg: " + String.format("%.1f", movingAverage) + ")");
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StreamAnalyzer sentinel = new StreamAnalyzer(4); // Window of 4 items

        System.out.println("\033[1m\n--- FlowGuard Sentinel (Live Stream Analysis) ---\033[0m");
        System.out.println("\033[90mWe are monitoring live requests per second. Enter numbers sequentially.\033[0m");
        System.out.println("\033[90mThe system needs 4 inputs to calibrate its baseline. Type 'exit' to quit.\033[0m\n");

        while (true) {
            System.out.print("\033[1mStream Data > \033[0m");
            String input = sc.nextLine().trim();
            if (input.equalsIgnoreCase("exit")) break;

            try {
                double val = Double.parseDouble(input);
                sentinel.processDataPoint(val);
            } catch (NumberFormatException e) {
                System.out.println("  \033[31mPlease enter a valid numeric value.\033[0m");
            }
        }
        sc.close();
    }
}