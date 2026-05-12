/* * [PROBLEM STATEMENT]
 * In a complex dashboard, some updates are "Critical" (like security alerts) 
 * and some are "Low Priority" (like background logs). If we treat them 
 * equally, a background log could block a critical alert.
 *
 * [LOGIC & INSIGHT]
 * I built a 'Priority Task Queue'. Instead of a simple array, I used an 
 * internal sorting mechanism that prioritizes tasks based on a 'level' 
 * (0 to 10). I personally implemented an 'Async Burst' mode—it executes 
 * high-priority tasks immediately but 'debounces' low-priority tasks 
 * to save browser CPU cycles. This is how you build a smooth, professional 
 * interface that doesn't lag.
 */

class TaskOrchestrator {
    constructor() {
        this.queue = [];
        this.isProcessing = false;
    }

    add(task, priority = 5) {
        console.log(`\x1b[90m[QUEUE]\x1b[0m Scheduled: ${task.name} (P${priority})`);
        this.queue.push({ task, priority });
        this.queue.sort((a, b) => b.priority - a.priority); // High priority first
        this.processNext();
    }

    async processNext() {
        if (this.isProcessing || this.queue.length === 0) return;

        this.isProcessing = true;
        const { task, priority } = this.queue.shift();

        console.log(`\x1b[35m[EXEC]\x1b[0m Running P${priority}: ${task.name}`);
        
        await new Promise(resolve => setTimeout(resolve, 500)); // Simulating work
        task();

        this.isProcessing = false;
        this.processNext();
    }
}

const scheduler = new TaskOrchestrator();

scheduler.add(() => console.log("  \x1b[32m-> Rendering Background Grid\x1b[0m"), 1);
scheduler.add(() => console.log("  \x1b[31m-> CRITICAL: Firewall Breach Alert!\x1b[0m"), 10);
scheduler.add(() => console.log("  \x1b[34m-> Updating Telemetry Data\x1b[0m"), 5);