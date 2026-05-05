/*
 * Problem: Re-rendering an entire HTML table with 1,000 rows just because 1 row 
 * changed is incredibly slow.
 * Logic: Virtual Diffing. We compare the "Old State" with the "New State" in 
 * memory (JavaScript objects) and only touch the actual browser DOM for the 
 * specific element that changed.
 */

const oldState = { id: 1, status: "IDLE", color: "gray" };
const newState = { id: 1, status: "ACTIVE", color: "orange" };

function calculateDiff(oldObj, newObj) {
    console.log("\x1b[1m\n--- Virtual DOM Diffing Engine ---\x1b[0m");
    const patches = {};

    for (let key in newObj) {
        if (newObj[key] !== oldObj[key]) {
            patches[key] = newObj[key];
            console.log(`  \x1b[33m[Diff Found]\x1b[0m Key '${key}' changed: ${oldObj[key]} -> ${newObj[key]}`);
        }
    }

    if (Object.keys(patches).length > 0) {
        console.log("  \x1b[32m[DOM Patch]\x1b[0m Applying targeted updates to the UI...");
    } else {
        console.log("  \x1b[90m[No Change]\x1b[0m Skipping DOM render.");
    }
}

calculateDiff(oldState, newState);