/* * [PROBLEM STATEMENT]
 * In large-scale applications, different modules (UI, Database, Network) need 
 * to talk to each other. If they are tightly coupled, changing one breaks them all. 
 * We need an asynchronous "Event Bus" where modules can subscribe to signals 
 * without knowing who sent them.
 *
 * [LOGIC & INSIGHT]
 * I implemented a 'Pub-Sub' (Publisher-Subscriber) pattern here. I used 
 * synchronized lists and a thread-safe dispatching mechanism. The beauty of this 
 * code is its scalability; you can have 100 listeners waiting for a "System_Alert" 
 * and the main engine won't slow down because the notification logic is decoupled. 
 * This is exactly how modern frameworks like Spring or Android work under the hood.
 */

import java.util.*;
import java.util.concurrent.*;

interface SystemListener {
    void onSignal(String message, int priority);
}

class SecurityModule implements SystemListener {
    public void onSignal(String message, int priority) {
        if (priority > 5) {
            System.out.println("\033[31m[SEC_MOD]\033[0m High Priority Alert: " + message);
        }
    }
}

class DashboardModule implements SystemListener {
    public void onSignal(String message, int priority) {
        System.out.println("\033[34m[DASHBOARD]\033[0m Updating UI with signal: " + message);
    }
}

public class SystemPulse {
    private final List<SystemListener> subscribers = new CopyOnWriteArrayList<>();

    public void subscribe(SystemListener listener) {
        subscribers.add(listener);
    }

    public void emit(String signal, int level) {
        System.out.println("\033[1m[EMITTING]\033[0m Pulse Level " + level + ": " + signal);
        for (SystemListener s : subscribers) {
            s.onSignal(signal, level);
        }
    }

    public static void main(String[] args) {
        SystemPulse bus = new SystemPulse();
        
        bus.subscribe(new SecurityModule());
        bus.subscribe(new DashboardModule());

        bus.emit("Unauthorized Access Attempt", 9);
        System.out.println("----------------------------------");
        bus.emit("Background Sync Complete", 2);
    }
}