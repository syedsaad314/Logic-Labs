/*
 * Problem: In a collaborative environment (like multiple staff updating an inventory system 
 * simultaneously), standard database writes cause data loss where the "last write wins".
 * Logic: Conflict-free Replicated Data Types (CRDTs). Instead of overriding state, we track 
 * individual operations with logical timestamps. When offline devices reconnect, operations 
 * merge mathematically without conflicts, ensuring absolute data consistency.
 */

class LWWRegister {
    constructor(id) {
        this.nodeId = id;
        this.state = {}; // { key: { value, timestamp } }
    }

    set(key, value) {
        const timestamp = Date.now();
        this.state[key] = { value, timestamp };
        console.log(`  \x1b[36m[Node ${this.nodeId}]\x1b[0m Set '${key}' to '${value}' at T+${timestamp}`);
    }

    get(key) {
        return this.state[key] ? this.state[key].value : null;
    }

    // Merge incoming state from another node
    merge(incomingState) {
        for (const [key, incomingData] of Object.entries(incomingState)) {
            const localData = this.state[key];

            // Last-Write-Wins (LWW) resolution
            if (!localData || incomingData.timestamp > localData.timestamp) {
                this.state[key] = incomingData;
                console.log(`  \x1b[32m[Sync]\x1b[0m Node ${this.nodeId} updated '${key}' via merge.`);
            }
        }
    }
}

console.log("\x1b[1m\n--- CRDT State Sync Engine (LWW Register) ---\x1b[0m");

const posTerminal1 = new LWWRegister("POS_Front");
const posTerminal2 = new LWWRegister("POS_Back");

// Simulate simultaneous offline writes
setTimeout(() => posTerminal1.set("coffee_beans_kg", 12), 10);
setTimeout(() => posTerminal2.set("coffee_beans_kg", 10), 50); // Back terminal writes slightly later

setTimeout(() => {
    console.log("\n  \x1b[90m--- Network Reconnected. Triggering Sync... ---\x1b[0m");
    // Terminals sync their states with each other
    posTerminal1.merge(posTerminal2.state);
    
    console.log(`\n  \x1b[1mFinal Synchronized State (Front Terminal):\x1b[0m ${posTerminal1.get("coffee_beans_kg")} kg`);
}, 100);