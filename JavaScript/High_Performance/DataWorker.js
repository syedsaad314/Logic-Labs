/*
 * Problem: Parsing 50MB of JSON data for a dashboard graph on the main thread will 
 * completely freeze the browser. The user won't be able to click or scroll.
 * Logic: Web Workers. We offload heavy mathematical processing to a background CPU thread. 
 * The main UI remains flawlessly smooth, and the worker simply messages the UI when the data is ready.
 */

// NOTE: In a real browser, this would be split into main.js and worker.js. 
// This script simulates the asynchronous offloading logic for Node/Terminal execution.

console.log("\x1b[1m\n--- Async Data Worker Simulation ---\x1b[0m");
console.log("  \x1b[36m[Main UI]\x1b[0m Rendering dashboard components...");
console.log("  \x1b[36m[Main UI]\x1b[0m Dispatching massive payload to Background Worker.\n");

// Simulate Web Worker offloading
function backgroundDataProcessing(datasetSize) {
    return new Promise((resolve) => {
        console.log(`  \x1b[90m[Worker]\x1b[0m Thread isolated. Beginning heavy parse of ${datasetSize} records...`);
        
        // Simulating heavy CPU lock-up in the background thread
        setTimeout(() => {
            const processedData = "Aggregated_Metrics_Ready";
            resolve(processedData);
        }, 2500); 
    });
}

// Main thread continues to be responsive
const interval = setInterval(() => {
    console.log("  \x1b[32m[Main UI]\x1b[0m Animations running smoothly at 60fps...");
}, 800);

// Receive data from worker
backgroundDataProcessing(500000).then((result) => {
    clearInterval(interval);
    console.log(`\n  \x1b[35m[Worker Event]\x1b[0m Message received on main thread: ${result}`);
    console.log("  \x1b[36m[Main UI]\x1b[0m Injecting data into charts.");
});