/*
 * Topic: Asynchronous Programming & Promise Queues
 * Problem: In Node.js or browser environments, we often have background tasks (like API calls)
 * that take time. We need a way to schedule them dynamically so they execute cleanly without 
 * locking up the main thread.
 * Approach: We wrap setTimeout inside a Promise to simulate an asynchronous network request. 
 * We then use the native async/await syntax to execute an array of these tasks sequentially 
 * while keeping the console interactive.
 */

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

const executeTask = (taskName, delayMs) => {
    return new Promise((resolve) => {
        setTimeout(() => {
            console.log(`\x1b[32m  ✓ Processed:\x1b[0m ${taskName} (after ${delayMs}ms)`);
            resolve();
        }, delayMs);
    });
};

async function runQueue(tasks) {
    console.log("\x1b[33m\nInitiating asynchronous execution pipeline...\x1b[0m");
    for (const task of tasks) {
        console.log(`\x1b[36m  > Queueing:\x1b[0m ${task.name}...`);
        await executeTask(task.name, task.delay);
    }
    console.log("\x1b[1m\nPipeline execution complete.\x1b[0m");
    readline.close();
}

console.log("\x1b[1m\n--- Async Task Scheduler ---\x1b[0m");
let tasks = [];

const promptUser = () => {
    readline.question("Enter task name and delay in ms (e.g., 'API_Fetch 1500') or type 'run': ", (input) => {
        if (input.toLowerCase() === 'run') {
            if (tasks.length === 0) {
                console.log("Queue is empty. Exiting.");
                readline.close();
            } else {
                runQueue(tasks);
            }
            return;
        }

        const [name, delayStr] = input.split(' ');
        const delay = parseInt(delayStr, 10);

        if (name && !isNaN(delay)) {
            tasks.push({ name, delay });
            console.log(`\x1b[90m  Task '${name}' added to queue.\x1b[0m`);
        } else {
            console.log("\x1b[31m  Invalid format. Try again.\x1b[0m");
        }
        promptUser();
    });
};

promptUser();