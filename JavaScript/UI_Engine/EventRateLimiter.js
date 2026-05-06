/*
 * Problem: If a user resizes the window or scrolls, the browser can fire 100 events 
 * per second, crashing the dashboard's rendering engine.
 * Logic: Throttling. No matter how many times the event fires, we only allow 
 * the function to execute once every 200ms, keeping the UI "Solar-Flare" smooth.
 */

function throttle(func, limit) {
    let inThrottle;
    return function() {
        if (!inThrottle) {
            func.apply(this, arguments);
            inThrottle = true;
            setTimeout(() => inThrottle = false, limit);
        }
    }
}

const updateUI = throttle(() => {
    console.log("  \x1b[33m[UI Render]\x1b[0m Throttled update executed at:", new Date().toLocaleTimeString());
}, 1000);

console.log("\x1b[1m\n--- UI Event Throttle Engine ---\x1b[0m");
console.log("  \x1b[90mSimulating 10 rapid events...\x1b[0m");
for(let i=0; i<10; i++) updateUI();