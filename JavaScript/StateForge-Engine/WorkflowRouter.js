/*
 * Problem: E-commerce checkouts often break if a user hits the "Back" button or tries 
 * to skip the payment step.
 * Logic: Finite State Machine (FSM). We explicitly define valid "States" and strict 
 * rules for "Transitions". The system completely ignores unauthorized attempts to change 
 * state, ensuring the workflow is mathematically unbreakable.
 */

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

const WORKFLOW = {
    "CART": { next: "SHIPPING", prev: null },
    "SHIPPING": { next: "PAYMENT", prev: "CART" },
    "PAYMENT": { next: "CONFIRMED", prev: "SHIPPING" },
    "CONFIRMED": { next: null, prev: null } // Terminal state
};

let currentState = "CART";

function displayUI() {
    console.log(`\n  \x1b[1mCurrent State:\x1b[0m \x1b[36m[ ${currentState} ]\x1b[0m`);
    
    let options = [];
    if (WORKFLOW[currentState].next) options.push("next");
    if (WORKFLOW[currentState].prev) options.push("prev");
    
    if (options.length === 0) {
        console.log("  \x1b[32mWorkflow Complete. Order is finalized.\x1b[0m\n");
        return readline.close();
    }

    console.log(`  \x1b[90mValid actions: ${options.join(', ')} (or 'exit')\x1b[0m`);
    
    readline.question("\x1b[1mAction > \x1b[0m", (action) => {
        action = action.toLowerCase().trim();
        
        if (action === "exit") return readline.close();

        if (action === "next" && WORKFLOW[currentState].next) {
            currentState = WORKFLOW[currentState].next;
            console.log(`  \x1b[32m✓ Advancing to ${currentState}...\x1b[0m`);
        } else if (action === "prev" && WORKFLOW[currentState].prev) {
            currentState = WORKFLOW[currentState].prev;
            console.log(`  \x1b[33m← Returning to ${currentState}...\x1b[0m`);
        } else {
            console.log(`  \x1b[31m[!] Invalid action. Transition denied.\x1b[0m`);
        }
        
        displayUI();
    });
}

console.log("\x1b[1m\n--- StateForge Engine (FSM) ---\x1b[0m");
console.log("\x1b[90mWe are enforcing a strict checkout pipeline. Try to break it.\x1b[0m");
displayUI();