/* * [PROBLEM STATEMENT]
 * In the canteen checkout system, students can pay with Cash, a Student 
 * Wallet ID, or a Credit Card. If we use a giant 'if/else' block for 
 * processing, adding a new payment method (like EasyPaisa) requires 
 * modifying core system logic, risking catastrophic bugs.
 *
 * [LOGIC & INSIGHT]
 * I implemented the 'Strategy Pattern'. We extract each payment method 
 * into its own dedicated class that implements a shared interface. 
 * The main 'CheckoutCart' doesn't know *how* the payment works; it just 
 * knows to call 'pay()'. This adheres strictly to the Open/Closed Principle 
 * (SOLID): Open for extension, closed for modification.
 */

interface PaymentMethod {
    void pay(int amount);
}

class CashStrategy implements PaymentMethod {
    public void pay(int amount) {
        System.out.println("  \033[32m[CASH]\033[0m Processing Rs. " + amount + " at the counter. Open register.");
    }
}

class StudentWalletStrategy implements PaymentMethod {
    private String studentId;
    public StudentWalletStrategy(String id) { this.studentId = id; }
    
    public void pay(int amount) {
        System.out.println("  \033[36m[WALLET]\033[0m Deducting Rs. " + amount + " from Student ID: " + studentId);
    }
}

class CheckoutCart {
    private int totalAmount = 0;

    public void addItemCost(int cost) { totalAmount += cost; }

    public void executePayment(PaymentMethod method) {
        System.out.println("\n\033[1m[CHECKOUT_INITIATED]\033[0m Total Due: Rs. " + totalAmount);
        method.pay(totalAmount);
    }
}

public class PaymentStrategy {
    public static void main(String[] args) {
        CheckoutCart cart1 = new CheckoutCart();
        cart1.addItemCost(450); // Zinger
        cart1.addItemCost(150); // Fries

        // Context dynamically swaps strategies at runtime
        cart1.executePayment(new StudentWalletStrategy("KU-UBIT-9921"));
        
        CheckoutCart cart2 = new CheckoutCart();
        cart2.addItemCost(100); // Chai
        cart2.executePayment(new CashStrategy());
    }
}