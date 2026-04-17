/*
 * Problem: When UI data changes, re-rendering the entire webpage is incredibly slow.
 * Logic: This is the core logic behind React.js. We take the "Old State" (JSON) and the 
 * "New State" (JSON), run a diffing algorithm, and output only the exact precise "patches" 
 * (what was Added, Removed, or Modified).
 */

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

function generateDiff(oldObj, newObj, path = "root") {
    let patches = [];

    const oldKeys = Object.keys(oldObj || {});
    const newKeys = Object.keys(newObj || {});

    // Check for modifications and deletions
    for (let key of oldKeys) {
        const currentPath = `${path}.${key}`;
        if (!(key in newObj)) {
            patches.push(`\x1b[31m[-] REMOVED:\x1b[0m ${currentPath} (was: ${oldObj[key]})`);
        } else if (typeof oldObj[key] === 'object' && typeof newObj[key] === 'object') {
            patches = patches.concat(generateDiff(oldObj[key], newObj[key], currentPath));
        } else if (oldObj[key] !== newObj[key]) {
            patches.push(`\x1b[33m[*] MODIFIED:\x1b[0m ${currentPath} (\x1b[90m${oldObj[key]}\x1b[0m -> \x1b[1m${newObj[key]}\x1b[0m)`);
        }
    }

    // Check for additions
    for (let key of newKeys) {
        if (!(key in oldObj)) {
            patches.push(`\x1b[32m[+] ADDED:\x1b[0m ${path}.${key} (value: ${newObj[key]})`);
        }
    }

    return patches;
}

console.log("\x1b[1m\n--- UI State Differ Engine (Virtual DOM) ---\x1b[0m");
console.log("\x1b[90mCompare two JSON UI states to generate render patches.\x1b[0m");

const runDiffer = () => {
    readline.question("\n\x1b[1mOld State JSON > \x1b[0m", (oldJson) => {
        if (oldJson.toLowerCase() === 'exit') return readline.close();
        
        readline.question("\x1b[1mNew State JSON > \x1b[0m", (newJson) => {
            try {
                const oldState = JSON.parse(oldJson);
                const newState = JSON.parse(newJson);
                
                const patches = generateDiff(oldState, newState);
                
                console.log("\n\x1b[1mGenerated Render Patches:\x1b[0m");
                if (patches.length === 0) {
                    console.log("  \x1b[90mNo changes detected. Skipping UI render.\x1b[0m");
                } else {
                    patches.forEach(p => console.log(`  ${p}`));
                }
            } catch (error) {
                console.log("  \x1b[31m[Error] Invalid JSON syntax.\x1b[0m");
            }
            runDiffer();
        });
    });
};

runDiffer();