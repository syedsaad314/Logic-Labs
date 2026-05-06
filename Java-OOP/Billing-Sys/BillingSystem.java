/*
 * Logic: OOP Polymorphism & Logic 
 * Problem: Create a system that handles different customer types (Regular/Premium) 
 * with different discount logic without using messy if-else blocks everywhere.
 * Approach: We use an abstract class and override the 'calculateTotal' method. 
 * This makes the system extensible for future "VIP" or "Student" types.
 */

import java.util.Scanner;

abstract class Customer {
    String name;
    public Customer(String name) { this.name = name; }
    abstract double applyDiscount(double amount);
}

class RegularCustomer extends Customer {
    public RegularCustomer(String name) { super(name); }
    @Override
    double applyDiscount(double amount) { return amount; } // No discount
}

class PremiumCustomer extends Customer {
    public PremiumCustomer(String name) { super(name); }
    @Override
    double applyDiscount(double amount) { return amount * 0.85; } // 15% off
}

public class BillingSystem { 
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            System.out.println("\033[1m--- Logic Labs: Billing System ---\033[0m");
            
            System.out.print("Customer Name: ");
            String name = sc.nextLine();
            System.out.print("Are they Premium? (yes/no): ");
            String type = sc.nextLine();
            System.out.print("Enter total bill amount: ");
            double bill = sc.nextDouble();

            Customer customer = type.equalsIgnoreCase("yes") ? 
                                new PremiumCustomer(name) : new RegularCustomer(name);

            System.out.println("\033[90m----------------------------------\033[0m");
            System.out.println("Final Bill for " + customer.name + ": $" + customer.applyDiscount(bill));
        }
    }
}