/* * [PROBLEM STATEMENT]
 * Frameworks like React are fast because they don't update the entire UI 
 * every time a variable changes. Instead, they keep a "Virtual" copy of 
 * the UI, compare it to the new version, and only update what changed. 
 *
 * [LOGIC & INSIGHT]
 * I built a micro-simulator of a Virtual DOM 'Diffing' algorithm. 
 * It takes an 'Old Tree' and a 'New Tree' (represented as JS objects), 
 * recursively compares their nodes, and generates a list of 'Patches'. 
 * Showing that I understand the underlying mechanics of the MERN stack's 
 * frontend layer proves I am not just a framework user, but a systems 
 * thinker.
 */

class VDOMDiffer {
    static diff(oldNode, newNode, path = "root") {
        let patches = [];

        // Node was removed
        if (!newNode) {
            patches.push({ action: 'REMOVE', path, old: oldNode });
            return patches;
        }

        // Node is entirely new
        if (!oldNode) {
            patches.push({ action: 'ADD', path, new: newNode });
            return patches;
        }

        // Node type or value changed
        if (oldNode.type !== newNode.type || oldNode.value !== newNode.value) {
            patches.push({ action: 'REPLACE', path, old: oldNode.value, new: newNode.value });
        }

        // Recursively check children
        const maxChildren = Math.max(oldNode.children?.length || 0, newNode.children?.length || 0);
        for (let i = 0; i < maxChildren; i++) {
            const childOld = oldNode.children ? oldNode.children[i] : undefined;
            const childNew = newNode.children ? newNode.children[i] : undefined;
            
            const childPatches = this.diff(childOld, childNew, `${path}.child[${i}]`);
            patches = patches.concat(childPatches);
        }

        return patches;
    }
}

// Simulated UI Trees
const oldUI = {
    type: 'div', value: 'Container',
    children: [ { type: 'h1', value: 'Hello' }, { type: 'p', value: 'Status: Idle' } ]
};

const newUI = {
    type: 'div', value: 'Container',
    children: [ { type: 'h1', value: 'Hello' }, { type: 'p', value: 'Status: Active' } ] // Changed text
};

console.log("\x1b[1m--- V-DOM DIFFING ENGINE ---\x1b[0m");
const updates = VDOMDiffer.diff(oldUI, newUI);

if (updates.length === 0) {
    console.log("  \x1b[32mNo DOM updates required.\x1b[0m");
} else {
    updates.forEach(patch => {
        console.log(`  \x1b[33m[PATCH]\x1b[0m Action: ${patch.action} at ${patch.path}`);
        console.log(`          \x1b[31m- Old: ${patch.old}\x1b[0m`);
        console.log(`          \x1b[32m+ New: ${patch.new}\x1b[0m`);
    });
}