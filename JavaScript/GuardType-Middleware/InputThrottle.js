/*
 * Problem (The Commons): When a user types in a live search bar, it sends a database request 
 * for every single keystroke. "H", "He", "Hel", "Hell", "Hello". This crashes servers.
 * Logic: The Debounce Engine. We intercept the input and start a timer. If the user hits 
 * another key before the timer runs out, we cancel the old timer and start a new one. The database 
 * is only queried once the user *stops* typing.
 */

const readline = require('readline');

readline.emitKeypressEvents(process.stdin);
if (process.stdin.isTTY) process.stdin.setRawMode(true);

console.log("\x1b[1m\n--- GuardType Middleware (Debounce Controller) ---\x1b[0m");
console.log("\x1b[90mStart typing a search query. Notice how the 'Database Query' only triggers\x1b[0m");
console.log("\x1b[90mwhen you pause for half a second. Press 'ESC' to exit.\x1b[0m\n");

let typingBuffer = "";
let debounceTimer = null;
const DELAY_MS = 500; // Wait 500ms after the last keystroke

// Simulated heavy database operation
function executeSearch(query) {
    if (query.trim() === "") return;
    console.log(`\n  \x1b[32m[Database]\x1b[0m Querying records for: \x1b[1m"${query}"\x1b[0m`);
    process.stdout.write("\x1b[1mSearch > \x1b[0m"); 
    typingBuffer = ""; // Reset for next search
}

process.stdout.write("\x1b[1mSearch > \x1b[0m");

process.stdin.on('keypress', (str, key) => {
    if (key.name === 'escape' || (key.ctrl && key.name === 'c')) {
        process.exit();
    }

    if (key.name === 'return') {
        // Force search immediately on Enter
        clearTimeout(debounceTimer);
        executeSearch(typingBuffer);
        return;
    }

    if (key.name === 'backspace') {
        typingBuffer = typingBuffer.slice(0, -1);
        process.stdout.write('\b \b'); // Handle backspace in terminal
    } else if (str) {
        typingBuffer += str;
        process.stdout.write(str);
    }

    // --- Core Debounce Logic ---
    clearTimeout(debounceTimer); // Cancel the previous countdown
    
    debounceTimer = setTimeout(() => {
        executeSearch(typingBuffer);
    }, DELAY_MS);
});