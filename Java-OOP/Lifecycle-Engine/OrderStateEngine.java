/* * [PROBLEM STATEMENT]
 * In a high-volume food service operation, orders transition through 
 * strict phases: Pending -> Cooking -> Ready. If we use massive "if/else" 
 * blocks to manage what an order can or cannot do, the code becomes 
 * spaghetti and breaks under load.
 *
 * [LOGIC & INSIGHT]
 * I implemented the 'State Design Pattern'. Each state (Pending, Cooking, 
 * Ready) is its own separate class implementing a common interface. 
 * An order delegates its behavior to its current state object. This 
 * guarantees that a staff member cannot accidentally 'serve' an order 
 * that is still 'pending'. It's bulletproof domain modeling suitable 
 * for enterprise-grade transactional systems.
 */

interface OrderState {
    void process(OrderContext context);
    void cancel(OrderContext context);
}

class PendingState implements OrderState {
    public void process(OrderContext context) {
        System.out.println("\033[33m[STATE]\033[0m Transitioning to COOKING.");
        context.setState(new CookingState());
    }
    public void cancel(OrderContext context) {
        System.out.println("\033[31m[ACTION]\033[0m Order cancelled. Refunding payment.");
    }
}

class CookingState implements OrderState {
    public void process(OrderContext context) {
        System.out.println("\033[32m[STATE]\033[0m Transitioning to READY for pickup.");
        context.setState(new ReadyState());
    }
    public void cancel(OrderContext context) {
        System.out.println("\033[31m[ERROR]\033[0m Cannot cancel! Food is already on the grill.");
    }
}

class ReadyState implements OrderState {
    public void process(OrderContext context) {
        System.out.println("\033[36m[ACTION]\033[0m Order fulfilled and handed to customer.");
    }
    public void cancel(OrderContext context) {
        System.out.println("\033[31m[ERROR]\033[0m Cannot cancel! Order is already complete.");
    }
}

class OrderContext {
    private OrderState currentState;
    private String orderId;

    public OrderContext(String id) {
        this.orderId = id;
        this.currentState = new PendingState();
        System.out.println("\n\033[1m[NEW_ORDER]\033[0m ID: " + orderId + " initialized in PENDING state.");
    }

    public void setState(OrderState state) { this.currentState = state; }
    public void nextPhase() { currentState.process(this); }
    public void attemptCancel() { currentState.cancel(this); }
}

public class OrderStateEngine {
    public static void main(String[] args) {
        OrderContext order1 = new OrderContext("BURGER_099");
        
        order1.nextPhase();     // Moves to Cooking
        order1.attemptCancel(); // Should fail
        order1.nextPhase();     // Moves to Ready
    }
}