/*
 * Problem: WebSockets provide live, two-way data, but networks are unstable. If 
 * the user drops WiFi for 2 seconds, the socket dies and the dashboard freezes forever.
 * Logic: Auto-Reconnection Strategy with Exponential Backoff. If the socket closes, 
 * we try to reconnect immediately. If that fails, we wait 2s, then 4s, then 8s, 
 * preventing server spam while ensuring UI recovery.
 */

class SocketManager {
    constructor(endpoint) {
        this.endpoint = endpoint;
        this.reconnectAttempts = 0;
    }

    connect() {
        console.log(`\x1b[1m\n--- Resilient WebSocket Manager ---\x1b[0m`);
        console.log(`  \x1b[36m[Connecting]\x1b[0m Attempting connection to ${this.endpoint}...`);
        
        // Simulating a connection failure
        setTimeout(() => this.handleDisconnect(), 1000);
    }

    handleDisconnect() {
        console.log(`  \x1b[31m[DISCONNECTED]\x1b[0m Connection lost.`);
        this.reconnectAttempts++;
        
        // Exponential backoff: 2s, 4s, 8s...
        const delay = Math.pow(2, this.reconnectAttempts) * 1000; 
        console.log(`  \x1b[33m[Reconnecting]\x1b[0m Retrying in ${delay / 1000}s (Attempt ${this.reconnectAttempts})...`);
    }
}

const telemetrySocket = new SocketManager("wss://api.logic-labs.io/telemetry");
telemetrySocket.connect();