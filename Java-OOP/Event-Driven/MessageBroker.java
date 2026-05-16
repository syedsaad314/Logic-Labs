/* * [PROBLEM STATEMENT]
 * In microservices, having Service A directly call Service B creates tight 
 * coupling. If Service B crashes, Service A crashes. We need a "Middleman" 
 * to handle communications asynchronously.
 *
 * [LOGIC & INSIGHT]
 * I engineered a topic-based Message Broker using the Observer Pattern. 
 * Microservices "Subscribe" to topics (like 'ORDERS' or 'SECURITY'). 
 * When an event occurs, the Publisher just throws the message to the Broker, 
 * and the Broker distributes it. This guarantees that publishers and 
 * subscribers never need to know about each other, ensuring high decoupling.
 */

import java.util.*;

interface Subscriber {
    void receive(String message);
}

class Microservice implements Subscriber {
    private String name;
    public Microservice(String name) { this.name = name; }
    
    public void receive(String message) {
        System.out.println("  \033[36m[" + name + "]\033[0m Processed Event -> " + message);
    }
}

class EventBroker {
    private Map<String, List<Subscriber>> topics = new HashMap<>();

    public void subscribe(String topic, Subscriber sub) {
        topics.computeIfAbsent(topic, k -> new ArrayList<>()).add(sub);
        System.out.println("\033[90m[BROKER]\033[0m New subscriber attached to: " + topic);
    }

    public void publish(String topic, String message) {
        System.out.println("\n\033[35m[PUBLISH]\033[0m Topic: " + topic + " | Payload: " + message);
        List<Subscriber> subs = topics.getOrDefault(topic, Collections.emptyList());
        for (Subscriber sub : subs) {
            sub.receive(message);
        }
    }
}

public class MessageBroker {
    public static void main(String[] args) {
        EventBroker kafkaLite = new EventBroker();
        
        Subscriber paymentService = new Microservice("Payment_API");
        Subscriber inventoryService = new Microservice("Inventory_DB");
        Subscriber securityService = new Microservice("Auth_Gateway");

        kafkaLite.subscribe("CHECKOUT", paymentService);
        kafkaLite.subscribe("CHECKOUT", inventoryService);
        kafkaLite.subscribe("SECURITY_ALERT", securityService);

        kafkaLite.publish("CHECKOUT", "Order #5512 - 2x Zinger Burgers");
        kafkaLite.publish("SECURITY_ALERT", "Multiple failed logins from IP 10.0.0.5");
    }
}