/*
 * Problem (The Commons): Tightly coupling services via synchronous HTTP requests is slow. 
 * If User Registration has to wait for the Email Service to finish sending a welcome email, 
 * the user experiences lag.
 * Logic: Event-Driven Architecture (Pub/Sub). The Registration service simply publishes a 
 * "USER_CREATED" event to a central Bus and returns instantly. The Email service (and any 
 * others) listens to that Bus and processes the event asynchronously in the background.
 */

const readline = require('readline').createInterface({
    input: process.stdin, output: process.stdout
});

class EventBus {
    constructor() {
        this.subscribers = {};
    }

    subscribe(eventType, callback) {
        if (!this.subscribers[eventType]) {
            this.subscribers[eventType] = [];
        }
        this.subscribers[eventType].push(callback);
        console.log(`  \x1b[90m[System]\x1b[0m Service subscribed to [${eventType}]`);
    }

    publish(eventType, payload) {
        console.log(`\n  \x1b[36m[Event Published]\x1b[0m ${eventType} -> Data:`, payload);
        
        if (!this.subscribers[eventType]) return;

        // Execute subscribers asynchronously
        this.subscribers[eventType].forEach(callback => {
            setTimeout(() => callback(payload), Math.random() * 1000);
        });
    }
}

const nexusBus = new EventBus();

console.log("\x1b[1m\n--- Nexus EventBus (Asynchronous Message Broker) ---\x1b[0m");

// Microservices Booting Up & Subscribing
nexusBus.subscribe("USER_REGISTERED", (data) => {
    console.log(`  \x1b[33m[Email Service]\x1b[0m Sending Welcome Email to ${data.email}...`);
});
nexusBus.subscribe("USER_REGISTERED", (data) => {
    console.log(`  \x1b[32m[Analytics Service]\x1b[0m Updating active user count metrics...`);
});

const prompt = () => {
    readline.question("\n\x1b[1mRegister new user email (or 'exit') > \x1b[0m", (email) => {
        if (email.toLowerCase() === 'exit') return readline.close();
        
        // Registration Service Logic
        const payload = { userId: Math.floor(Math.random() * 10000), email: email };
        console.log(`  \x1b[32m[Auth Service]\x1b[0m User saved to DB. Responding to client instantly.`);
        
        // Fire and forget
        nexusBus.publish("USER_REGISTERED", payload);
        
        setTimeout(prompt, 1500); // Wait briefly so async logs print cleanly
    });
};

prompt();