/**
 * REACTIVE CORE v1.0
 * Architected by: syedsaad314
 * Pattern: Observer/Proxy Pattern for State Management
 */

class ReactiveCore {
    constructor(initialState) {
        this.listeners = [];
        this.state = this._makeReactive(initialState);
    }

    // THE LOGIC: Automatically detects changes to data
    _makeReactive(obj) {
        const handler = {
            set: (target, property, value) => {
                target[property] = value;
                console.log(`[STATE CHANGE] ${property} -> ${value}`);
                this._notifyAll(); // Trigger the Dashboard update
                return true;
            }
        };
        return new Proxy(obj, handler);
    }

    // THE CONNECTION: Links the UI to the Logic
    onUpdate(callback) {
        this.listeners.push(callback);
    }

    _notifyAll() {
        this.listeners.forEach(callback => callback(this.state));
    }
}

// --- DASHBOARD LOGIC ---
const App = new ReactiveCore({
    username: "syedsaad314",
    balance: 5000,
    status: "Active",
    lastAction: "System Boot"
});

// Listener: Every time 'App.state' changes, this runs automatically
App.onUpdate((state) => {
    const display = document.getElementById('dashboard-view');
    if (display) {
        display.innerHTML = `
            <div class="card">
                <h2>User: ${state.username}</h2>
                <p><strong>Balance:</strong> $${state.balance}</p>
                <p><strong>Status:</strong> <span class="badge">${state.status}</span></p>
                <p class="footer">Last Action: ${state.lastAction}</p>
            </div>
        `;
    }
});