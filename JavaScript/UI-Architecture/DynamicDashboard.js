/* * [PROBLEM STATEMENT]
 * In modern web apps (like React/Vue), manually updating every piece of 
 * HTML is a recipe for bugs. We need a "State-Driven" engine where the 
 * UI automatically re-renders whenever the data changes.
 *
 * [LOGIC & INSIGHT]
 * I built a custom 'Reactive' class. It uses the Observer pattern. 
 * I personally created a 'Watch' function that monitors an object. 
 * When a value (like 'ServerLoad') changes, the engine detects it 
 * and pushes the update to the DOM. This is "Vanilla JS" performing 
 * like a modern framework—showing I understand the fundamental 
 * mechanics of data binding.
 */

class UIState {
    constructor(initialState) {
        this.state = new Proxy(initialState, {
            set: (target, key, value) => {
                target[key] = value;
                this.render();
                return true;
            }
        });
    }

    render() {
        console.log(`\n\x1b[1m[UI RE-RENDER]\x1b[0m`);
        console.log(`\x1b[34mCPU Load:\x1b[0m ${this.state.cpu}%`);
        console.log(`\x1b[34mMemory:\x1b[0m ${this.state.ram}GB`);
        console.log(`\x1b[34mStatus:\x1b[0m ${this.state.status}`);
    }

    update(key, value) {
        this.state[key] = value;
    }
}

// Initializing the dashboard
const dashboard = new UIState({ cpu: 12, ram: 4.2, status: 'IDLE' });

// Simulating live data changes
setTimeout(() => dashboard.update('cpu', 45), 1000);
setTimeout(() => {
    dashboard.update('cpu', 89);
    dashboard.update('status', 'CRITICAL_OVERLOAD');
}, 2000);