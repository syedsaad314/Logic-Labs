/*
 * Problem: A backend service might crash, but the TCP connection remains "open," 
 * causing the frontend to wait forever for data that will never come.
 * Logic: The Heartbeat. The client sends a tiny "ping" every 3 seconds. If the 
 * server doesn't "pong" back within a timeout window, the client marks the 
 * node as DEAD and switches to a backup server.
 */

class HeartbeatMonitor {
    constructor(nodeName) {
        this.node = nodeName;
        this.missedPings = 0;
    }

    start() {
        console.log(`\x1b[1m\n--- Heartbeat Monitor: ${this.node} ---\x1b[0m`);
        this.interval = setInterval(() => {
            if (this.missedPings >= 3) {
                console.log(`  \x1b[31m[CRITICAL]\x1b[0m Node ${this.node} is UNRESPONSIVE. Failover initiated.`);
                clearInterval(this.interval);
                return;
            }
            
            // Simulate random network failure
            const isAlive = Math.random() > 0.3;
            if (isAlive) {
                console.log(`  \x1b[32m[Ping OK]\x1b[0m ${this.node} responded.`);
                this.missedPings = 0;
            } else {
                this.missedPings++;
                console.log(`  \x1b[33m[Timeout]\x1b[0m No response from ${this.node}. (Missed: ${this.missedPings}/3)`);
            }
        }, 1000);
    }
}

const monitor = new HeartbeatMonitor("Primary_DB_Node");
monitor.start();