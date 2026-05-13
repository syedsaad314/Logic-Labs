/* * [PROBLEM STATEMENT]
 * In real-time apps, we often have 50+ components that need to update 
 * when a single "Global Event" happens (like a system error). Manually 
 * calling every component is inefficient.
 *
 * [LOGIC & INSIGHT]
 * I built a custom 'SyncPulse' class using the Observer pattern. I 
 * personally designed it to handle 'Scoped Events'—you can subscribe 
 * to a specific 'channel' (e.g., 'network', 'ui', 'auth'). This prevents 
 * "Event Pollution" where components receive messages they don't need. 
 * It’s a clean, decoupled way to manage state across a large JS project.
 */

class SyncPulse {
    constructor() {
        this.channels = {};
    }

    on(channel, callback) {
        if (!this.channels[channel]) this.channels[channel] = [];
        this.channels[channel].push(callback);
    }

    emit(channel, payload) {
        console.log(`\x1b[36m[EMIT]\x1b[0m Channel: ${channel} | Data:`, payload);
        if (!this.channels[channel]) return;
        this.channels[channel].forEach(cb => cb(payload));
    }
}

const pulse = new SyncPulse();

// Security Subsystem
pulse.on('security', (data) => {
    console.log(`  \x1b[31m[SecurityAlert]\x1b[0m Firewall blocked IP: ${data.ip}`);
});

// UI Subsystem
pulse.on('ui', (data) => {
    console.log(`  \x1b[32m[UIUpdate]\x1b[0m Theme changed to: ${data.theme}`);
});

pulse.emit('security', { ip: '192.168.1.1' });
pulse.emit('ui', { theme: 'Cyber-Dark' });