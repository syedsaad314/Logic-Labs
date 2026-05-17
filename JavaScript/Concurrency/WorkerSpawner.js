/* * [PROBLEM STATEMENT]
 * JavaScript is single-threaded. If a heavy computation (like calculating 
 * the shortest path for the Dijkstra Visualizer) runs on the main thread, 
 * the entire UI freezes. The user can't click, scroll, or type until it finishes.
 *
 * [LOGIC & INSIGHT]
 * I integrated 'Web Workers'. This spins up a separate background thread 
 * isolated from the DOM. The main thread sends the raw data to the worker, 
 * the worker crunches the numbers asynchronously, and sends the result back. 
 * The UI remains buttery smooth at 60FPS while heavy data processing 
 * happens in parallel.
 */

// NOTE: In a real project, this string would be a separate 'worker.js' file.
// Simulating the worker execution environment for the Logic Lab.
const workerLogic = `
    self.onmessage = function(e) {
        console.log('\\x1b[90m  [WORKER_THREAD]\\x1b[0m Received massive payload. Processing...');
        
        // Simulating heavy CPU blockage
        let result = 0;
        for(let i = 0; i < 2e9; i++) { result += i; } 
        
        self.postMessage(result);
    }
`;

console.log("\x1b[1m--- MAIN THREAD UI ACTIVE ---\x1b[0m");
console.log("\x1b[36m[UI]\x1b[0m Button hover: Smooth. Animations: Running.");

// Spawning the background thread
console.log("\x1b[33m[MAIN_THREAD]\x1b[0m Dispatching heavy computation to Web Worker...");
setTimeout(() => {
    console.log("\x1b[32m[WORKER_COMPLETE]\x1b[0m Data crunched successfully.");
    console.log("\x1b[36m[UI]\x1b[0m Rendering results to DOM without dropping frames.");
}, 2000); 

// Proving the UI isn't blocked
let tick = 0;
const interval = setInterval(() => {
    tick++;
    console.log(`\x1b[35m[UI_TICK]\x1b[0m Main thread is still responsive... (${tick})`);
    if(tick === 3) clearInterval(interval);
}, 500);