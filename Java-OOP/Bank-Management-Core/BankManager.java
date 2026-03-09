import java.util.Scanner;
import java.util.HashMap;
import java.util.Map;

public class BankManager {
    private static Map<String, BaseAccount> database = new HashMap<>();
    private static Scanner input = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.println("OMNIBANK CORE v1.0 ONLINE");
        
        // Pre-seeding a couple of accounts for testing logic
        database.put("101", new SavingsAccount("101", "Syed Saad", 5000.0));
        database.put("102", new SavingsAccount("102", "Project-User", 1200.0));

        boolean running = true;
        while (running) {
            System.out.println("\n--- MANAGER DASHBOARD ---");
            System.out.println("1. Search Account by ID");
            System.out.println("2. Perform Deposit");
            System.out.println("3. Perform Withdrawal");
            System.out.println("4. Exit System");
            System.out.print("Select Action: ");
            
            int choice = input.nextInt();
            if (choice == 4) break;

            System.out.print("Enter Account ID: ");
            String id = input.next();
            BaseAccount acc = database.get(id);

            if (acc == null) {
                System.out.println("ERROR: Account not found in system.");
                continue;
            }

            switch (choice) {
                case 1 -> acc.showFullReport();
                case 2 -> {
                    System.out.print("Amount to deposit: ");
                    acc.deposit(input.nextDouble());
                }
                case 3 -> {
                    System.out.print("Amount to withdraw: ");
                    acc.withdraw(input.nextDouble());
                }
            }
        }
        System.out.println("System Shutdown Securely.");
    }
}