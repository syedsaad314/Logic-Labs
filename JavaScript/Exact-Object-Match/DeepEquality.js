/*
 * Problem: In Javascript, `==` or `===` on two objects just checks if they occupy the same memory.
 * We need an algorithm to verify if the actual data inside two nested objects is identical, 
 * regardless of key order.
 * Logic: Recursive Deep Equality check. It traverses every key, checking arrays, objects, 
 * and primitive types to ensure total data parity.
 */

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

function isDeepEqual(obj1, obj2) {
    if (obj1 === obj2) return true;

    if (typeof obj1 !== 'object' || obj1 === null || typeof obj2 !== 'object' || obj2 === null) {
        return false;
    }

    const keys1 = Object.keys(obj1);
    const keys2 = Object.keys(obj2);

    if (keys1.length !== keys2.length) return false;

    for (let key of keys1) {
        if (!keys2.includes(key) || !isDeepEqual(obj1[key], obj2[key])) {
            return false;
        }
    }
    return true;
}

console.log("\x1b[1m\n--- Deep Object Equality Engine ---\x1b[0m");
console.log("\x1b[90mPaste two JSON strings to see if their data perfectly matches.\x1b[0m");

const promptObjects = () => {
    readline.question("\nEnter first JSON object (or 'quit'): ", (json1) => {
        if (json1.toLowerCase() === 'quit') return readline.close();
        
        readline.question("Enter second JSON object: ", (json2) => {
            try {
                const parsed1 = JSON.parse(json1);
                const parsed2 = JSON.parse(json2);
                
                const match = isDeepEqual(parsed1, parsed2);
                if (match) {
                    console.log("  \x1b[32m✓ EXACT MATCH: Objects contain identical data structures.\x1b[0m");
                } else {
                    console.log("  \x1b[31m✗ MISMATCH: The objects are fundamentally different.\x1b[0m");
                }
            } catch (error) {
                console.log("  \x1b[90m[Error] Invalid JSON syntax. Please try again.\x1b[0m");
            }
            promptObjects();
        });
    });
};

promptObjects();