/*
 * Problem: When a server recovers from a crash, 5,000 clients attempting to reconnect 
 * at the exact same millisecond will immediately crash the server again (The Thundering Herd problem).
 * Logic: Exponential Backoff with Jitter. When a client fails to connect, it waits 1s, then 2s, 
 * then 4s (exponential). Crucially, we add a random delay (jitter) to that wait time. This spreads 
 * out the reconnect attempts, saving the server from traffic spikes.
 */

const readline = require('readline').createInterface({
    input: process.stdin, output: process.stdout
});

class NetworkClient {
    constructor(maxRetries = 4) {
        this.maxRetries = maxRetries;
        this.baseDelay = 1000; // 1 second
    }

    async attemptConnection(attempt = 1) {
        console.log(`  \x1b[36m[Network]\x1b[0m Attempting connection... (Try ${attempt}/${this.maxRetries})`);

        // Simulate server always being down for this demo
        const serverOnline = false;

        if (serverOnline) {
            console.log("  \x1b[32m[200 OK]\x1b[0m Connection established successfully.\n");
            return;
        }

        console.log("  \x1b[31m[503 Unavailable]\x1b[0m Server refused connection.");

        if (attempt >= this.maxRetries) {
            console.log("  \x1b[31m[Fatal]\x1b[0m Max retries exhausted. Alerting user.\n");
            return;
        }

        // Exponential backoff logic: delay * (2 ^ attempt)
        const exponentialDelay = this.baseDelay * Math.pow(2, attempt - 1);
        
        // Jitter: Add a random variance between 0 and 500ms
        const jitter = Math.floor(Math.random() * 500);
        const finalDelay = exponentialDelay + jitter;

        console.log(`  \x1b[90m[Backoff]\x1b[0m Waiting ${(finalDelay/1000).toFixed(2)} seconds before next attempt (included jitter: +${jitter}ms)...\n`);

        setTimeout(() => this.attemptConnection(attempt + 1), finalDelay);
    }
}

console.log("\x1b[1m\n--- Resilient Network Client (Jitter Backoff) ---\x1b[0m");
const client = new NetworkClient();

readline.question("\x1b[1mPress Enter to trigger connection sequence > \x1b[0m", () => {
    client.attemptConnection();
    readline.close();
});